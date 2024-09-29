#include <ros/ros.h>
#include <nav_msgs/Odometry.h>

ros::Publisher base_gt_2D_pub;
bool use_carto_map;

void gt_3D_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
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
    base_gt_2D_pub.publish(gt_2D);
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
    base_gt_2D_pub = nh.advertise<nav_msgs::Odometry>("/base_gt",10);


    ros::spin();
    return 0;
}