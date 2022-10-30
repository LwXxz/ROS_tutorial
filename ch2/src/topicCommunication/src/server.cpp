/*
    需求:
        编写两个节点实现服务通信，客户端节点需要提交两个整数到服务器
        服务器需要解析客户端提交的数据，相加后，将结果响应回客户端，
        客户端再解析

    服务器实现:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建 ROS 句柄
        4.创建 服务 对象
        5.回调函数处理请求并产生响应
        6.由于请求有多个，需要调用 ros::spin()

*/
#include "ros/ros.h"
#include "topicCommunication/sum.h"

bool doReq(topicCommunication::sum::Request &req,
           topicCommunication::sum::Response &resp)
{
    int num1 = req.num1;
    int num2 = req.num2;
    ROS_INFO("服务器接收到的请求数据为:num1 = %d, num2 = %d", num1, num2);

    if (num1 < 0 || num2 < 0)
    {
        ROS_ERROR("data abnormal");
        return false;
    }
    resp.sum = num1 + num2;
    return true;
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "server");
    ros::NodeHandle nh;
    ros::ServiceServer server = nh.advertiseService("sum", doReq);
    ROS_INFO("server is working");

    ros::spin();
    return 0;
}