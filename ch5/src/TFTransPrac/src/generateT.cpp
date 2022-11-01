#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "turtlesim/Spawn.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "generateT");
    ros::NodeHandle nh;
    // 客户端为接受turtlesim::Pose的数据类型 服务器为/spawn
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");

    ros::service::waitForService("/spawn");
    // Args: x y theta name
    turtlesim::Spawn spawn;
    spawn.request.name = "turtle2";
    spawn.request.x = 1.0;
    spawn.request.y = 2.0;
    spawn.request.theta = 3.12;

    // 使用标记  是否成功找到服务或是否成功发送数据
    bool flag = client.call(spawn);
    if (flag)
    {
        ROS_INFO("乌龟%s创建成功!", spawn.response.name.c_str());
    }
    else
    {
        ROS_INFO("乌龟2创建失败!");
    }
    ros::spin();
}