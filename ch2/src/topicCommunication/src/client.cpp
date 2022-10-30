#include "ros/ros.h"
#include "topicCommunication/sum.h"

int main(int argc, char **argv){
    setlocale(LC_ALL, "");

    // 调用时动态传值,如果通过 launch 的 args 传参，需要传递的参数个数 +3
    if (argc != 3)
    // if (argc != 5)//launch 传参(0-文件路径 1传入的参数 2传入的参数 3节点名称 4日志路径)
    {
        ROS_ERROR("please update two paramas");
        return 1;
    }
    // 初始化ros节点 唯一
    ros::init(argc, argv, "client");
    // 创建句柄
    ros::NodeHandle nh;
    // 创建客户端
    ros::ServiceClient client = nh.serviceClient<topicCommunication::sum>("sum");
    // 等待服务器启动
    // 方式一
    ros::service::waitForService("sum");
    // 方式二
    // client::service::waitForService("sum");

    // 请求数据
    topicCommunication::sum arg;
    arg.request.num1 = atoi(argv[1]);
    arg.request.num2 = atoi(argv[2]);
    // 6.发送请求,返回 bool 值，标记是否成功
    bool flag = client.call(arg);
    // 7.处理响应
    if (flag)
    {
        ROS_INFO("request success: %d", arg.response.sum);
    }
    else
    {
        ROS_ERROR("request fail ....");
        return 1;
    }

    return 0;

}