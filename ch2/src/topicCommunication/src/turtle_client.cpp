#include "ros/ros.h"
#include "turtlesim/Spawn.h"

int main(int argc, char **argv){
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "turtle_client");
    ros::NodeHandle nh;
    // turtlesim::Spawn 对应的类型  对应的服务
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
    
    // 等待服务器启动
    // 方式一
    ros::service::waitForService("spawn");
    turtlesim::Spawn arg;

    // 这里没有使用动态的方式
    // arg.request.name = "CC";
    // arg.request.x = 23;
    // arg.request.y = 32;
    // arg.request.theta = 90;

    // 动态 arg是从1开始的
    arg.request.name = atoi(argv[1]);
    arg.request.x = atoi(argv[2]);
    arg.request.y = atoi(argv[3]);
    arg.request.theta = atoi(argv[4]);

    // 6.发送请求,返回 bool 值，标记是否成功
    bool flag = client.call(arg);
    // 7.处理响应
    if (flag)
    {
        ROS_INFO("request success: %s", arg.response.name);
    }
    else
    {
        ROS_ERROR("request fail ....");
        return 1;
    }
    return 0;
}