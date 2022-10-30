#include "ros/ros.h"
#include "turtlesim/Pose.h"

void doMsg(const turtlesim::Pose::ConstPtr &turtlePose){
    ROS_INFO("turtle position is (%f, %f), theta is %f, linear_velocity is %f, angular_velocity is %f", 
            turtlePose->x, turtlePose->y, turtlePose->theta, turtlePose->linear_velocity, turtlePose->angular_velocity);
}

int main(int argc, char **argv){
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "turtlesim_sub");
    ros::NodeHandle nh;
    // turtlesim::Pose 是对应类型  /turtle1/pose 是对应话题
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>("/turtle1/pose", 100, doMsg);
    ros::spin();
}