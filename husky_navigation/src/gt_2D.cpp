#include <ros/ros.h>
#include <nav_msgs/Odometry.h>

ros::Publisher base_gt_2D_pub;

void gt_3D_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
    nav_msgs::Odometry gt_2D;
    gt_2D = *msg;
    gt_2D.pose.pose.position.z = 0.0;
    base_gt_2D_pub.publish(gt_2D);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv,"gt_2D");
    ros::NodeHandle nh;

    ros::Subscriber base_gt_3D_sub = nh.subscribe("/ground_truth/state", 10, gt_3D_callback);
    base_gt_2D_pub = nh.advertise<nav_msgs::Odometry>("/base_gt",10);

    ros::spin();
    return 0;
}