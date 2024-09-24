#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <sstream>

class OdometryToPose
{
public:
    OdometryToPose()
    {
        // Suscribirse al tópico /Odometry
        odom_sub_ = nh_.subscribe("/Odometry", 10, &OdometryToPose::odomCallback, this);
        
        // Publicar en el tópico /mavros/vision_pose/pose
        pose_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/vision_pose/pose", 10);
    }

    void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
    {
        geometry_msgs::PoseStamped pose_msg;
	pose_msg.header = msg->header;
        pose_msg.pose = msg->pose.pose; // Extraer la pose del mensaje de odometría

        pose_pub_.publish(pose_msg); // Publicar el mensaje de pose
    }

private:
    ros::NodeHandle nh_;
    ros::Subscriber odom_sub_;
    ros::Publisher pose_pub_;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pose_publisher");
    //ros::Rate loop_rate(30);
    OdometryToPose odometry_to_pose;

    ros::spin();

    return 0;
}

