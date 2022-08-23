#include "MonoNode.h"
#include "Converter.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "Mono");
    ros::start();

    if (argc > 1) {
        ROS_WARN("Arguments supplied via command line are neglected.");
    }

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ros::NodeHandle node_handle;
    image_transport::ImageTransport image_transport(node_handle);

    MonoNode node(ORB_SLAM2::System::MONOCULAR, node_handle, image_transport);

    node.Init();

    ros::spin();

    ros::shutdown();

    return 0;
}

MonoNode::MonoNode(
    ORB_SLAM2::System::eSensor sensor,
    ros::NodeHandle& node_handle,
    image_transport::ImageTransport& image_transport)
    : Node(sensor, node_handle, image_transport)
{
    image_subscriber = image_transport.subscribe("/camera/image_raw", 1, &MonoNode::ImageCallback, this);
    camera_info_topic_ = "/camera/camera_info";
    switcher_subscriber = node_handle.subscribe("/switcher/pose", 1, &MonoNode::SwitcherCallback, this);
}

MonoNode::~MonoNode()
{
}

void MonoNode::ImageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImageConstPtr cv_in_ptr;
    try {
        cv_in_ptr = cv_bridge::toCvShare(msg);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    current_frame_time_ = msg->header.stamp;

    orb_slam_->TrackMonocular(cv_in_ptr->image, cv_in_ptr->header.stamp.toSec());

    Update();
}

void MonoNode::SwitcherCallback(const geometry_msgs::Pose& msg)
{
    geometry_msgs::Quaternion q = msg.orientation;

    if (q.w > 1.0) {
        // if w>1 acos and sqrt will produce errors, this cant happen if quaternion is normalised
        q.x /= q.w;
        q.y /= q.w;
        q.z /= q.w;
        q.w = 1.0;
    }

    auto xx = q.x * q.x, xy = q.x * q.y, xz = q.x * q.z, xw = q.x * q.w;
    auto yy = q.y * q.y, yz = q.y * q.z, yw = q.y * q.w;
    auto zz = q.z * q.z, zw = q.z * q.w;

    auto m00 = 1 - 2 * (yy + zz);
    auto m01 = 2 * (xy - zw);
    auto m02 = 2 * (xz + yw);

    auto m10 = 2 * (xy + zw);
    auto m11 = 1 - 2 * (xx + zz);
    auto m12 = 2 * (yz - xw);

    auto m20 = 2 * (xz - yw);
    auto m21 = 2 * (yz + xw);
    auto m22 = 1 - 2 * (xx + yy);

    double pose_data[16] = { m00, m01, m02, msg.position.x,
        m10, m11, m12, msg.position.y,
        m20, m21, m22, msg.position.z,
        0, 0, 0, 1 };
    cv::Mat pose = cv::Mat(4, 4, CV_32F, pose_data);

    ROS_INFO_STREAM("Got a new pose for ORB SLAM2: " << pose);

    orb_slam_->SwitchPose(pose);
}
