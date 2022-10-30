#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv){
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "turtle_publish");
    ros::NodeHandle nh;
    // 键盘是通过这个接口来给topic传递信息的
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    // 4.循环发布运动控制消息
    //4-1.组织消息
    geometry_msgs::Twist msg;
    msg.linear.x = 1.0;
    msg.linear.y = 0.0;
    msg.linear.z = 0.0;

    msg.angular.x = 0.0;
    msg.angular.y = 0.0;
    msg.angular.z = 2.0;

    //4-2.设置发送频率
    ros::Rate r(10);
    //4-3.循环发送
    while (ros::ok())
    {
        pub.publish(msg);

        ros::spinOnce();
    }
}