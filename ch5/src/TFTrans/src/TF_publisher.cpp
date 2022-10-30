/* 
    静态坐标变换发布方:
        发布关于 laser 坐标系的位置信息  似乎是通过广播来发布的

    实现流程:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建静态坐标转换广播器
        4.创建坐标系信息
        5.广播器发布坐标系信息
        6.spin()
*/
#include "ros/ros.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/TransformStamped.h"

int main(int argc, char **argv){
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "TF_publisher");
    // 3.创建静态坐标转换广播器
    tf2_ros::StaticTransformBroadcaster broadcaster;
    // 4.创建坐标系信息 编辑的信息完全安装 rosmsg info geometry_msgs/TransformStamped来
    geometry_msgs::TransformStamped ts;
    // head info
    ts.header.seq = 100;
    ts.header.stamp = ros::Time::now();
    ts.header.frame_id = "base_link";
    // 设置子级坐标系 称为激光
    ts.child_frame_id = "laser";
    // 设置子级相对于父级的偏移量
    ts.transform.translation.x = 0.2;
    ts.transform.translation.y = 0.2;
    ts.transform.translation.z = 0.5;
    // 设置四元数:将 欧拉角数据转换成四元数
    tf2::Quaternion qtn;
    // 设置角度(x, y, z) 然后将角度复制给ts中
    qtn.setRPY(0, 0, 0);
    ts.transform.rotation.x = qtn.getX();
    ts.transform.rotation.y = qtn.getY();
    ts.transform.rotation.z = qtn.getZ();
    ts.transform.rotation.w = qtn.getW();
    // 广播发布
    broadcaster.sendTransform(ts);
    ros::spin();
}