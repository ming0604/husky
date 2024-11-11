#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>

ros::Publisher base_gt_2D_odom_pub;
ros::Publisher base_gt_2D_pose_pub;
bool use_carto_map;

void gt_3D_callback(const nav_msgs::Odometry::ConstPtr& msg)
{   
    //process the odometry message and publish it
    nav_msgs::Odometry gt_2D;
    if(use_carto_map)
    {   
        gt_2D = *msg;
        gt_2D.pose.pose.position.x = msg->pose.pose.position.x-0.302;
    }
    else
    {
        gt_2D = *msg;
    }
    
    gt_2D.pose.pose.position.z = 0.0;
    base_gt_2D_odom_pub.publish(gt_2D);

    //publish PoseStamped msg
    geometry_msgs::PoseStamped pose_msg;
    pose_msg.header = msg->header;  // 複製時間戳和坐標系
    pose_msg.pose = gt_2D.pose.pose;  // 複製已經處理過的位姿資訊
    base_gt_2D_pose_pub.publish(pose_msg);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv,"gt_2D");
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");

    // Get the parameter whether to use the map constructed by Cartographer
    private_nh.param("use_carto_map", use_carto_map, false);
    if(use_carto_map)
    {
        ROS_WARN("Using carto map oringin calibration");
    }
    ros::Subscriber base_gt_3D_sub = nh.subscribe("/ground_truth/state", 10, gt_3D_callback);
    base_gt_2D_odom_pub = nh.advertise<nav_msgs::Odometry>("/base_gt_odom",10);
    base_gt_2D_pose_pub = nh.advertise<geometry_msgs::PoseStamped>("/base_gt",10);

    ros::spin();
    return 0;
}