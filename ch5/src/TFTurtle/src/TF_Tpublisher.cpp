/*  
    动态的坐标系相对姿态发布(一个坐标系相对于另一个坐标系的相对姿态是不断变动的)

    需求: 启动 turtlesim_node,该节点中窗体有一个世界坐标系(左下角为坐标系原点)，乌龟是另一个坐标系，键盘
    控制乌龟运动，将两个坐标系的相对位置动态发布

    实现分析:
        1.乌龟本身不但可以看作坐标系，也是世界坐标系中的一个坐标点
        2.订阅 turtle1/pose,可以获取乌龟在世界坐标系的 x坐标、y坐标、偏移量以及线速度和角速度
        3.将 pose 信息转换成 坐标系相对信息并发布

    实现流程:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建 ROS 句柄
        4.创建订阅对象
        5.回调函数处理订阅到的数据(实现TF广播)
            5-1.创建 TF 广播器
            5-2.创建 广播的数据(通过 pose 设置)
            5-3.广播器发布数据
        6.spin
*/
#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"

// 把乌龟的位置转换为世界坐标的位置
void doMsg(const turtlesim::Pose::ConstPtr &pose){
    //  5-1.创建 TF 广播器
    static tf2_ros::TransformBroadcaster broadcaster;
    // geometry_msgs/TransformStamped 的数据
    geometry_msgs::TransformStamped tfs;
    
    // head 
    tfs.header.frame_id = "world";
    tfs.header.stamp = ros::Time::now();

    // TF ID
    tfs.child_frame_id = "turtle1";

    // 设置子级相对于父级的偏移量
    tfs.transform.translation.x = pose->x;
    tfs.transform.translation.y = pose->y;
    tfs.transform.translation.z = 0.0; // 二维实现，pose 中没有z，z 是 0

    // 四元数设置
    tf2::Quaternion qtn;
    // 初始化R：滚动角 P：俯仰角  Y：偏航角
    qtn.setRPY(0, 0, pose->theta);
    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();
    
    //  5-3.广播器发布数据
    broadcaster.sendTransform(tfs);
}

int main(int argc, char **argv){
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "TF_Tpublisher");
    ros::NodeHandle nh;
    // 4.创建订阅对象 /turtle1/pose 是对应话题 
    // 订阅之后发布出去
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>("/turtle1/pose", 1000, doMsg);
    ros::spin();
    return 0;
}