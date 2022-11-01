#include "ros/ros.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/PointStamped.h"

#include "tf2_ros/transform_listener.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

int main(int argc, char **argv){
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "sub_frames");
    // 创建句柄
    ros::NodeHandle nh;
    // 创建订阅节点
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);
    // 5.解析订阅信息中获取 son1 坐标系原点在 son2 中的坐标
    ros::Rate r(1);

    while(ros::ok()){
        try
        {
            // 值能容纳两个 定义son2味父坐标 son1为子坐标
            geometry_msgs::TransformStamped tfs = buffer.lookupTransform("son1", "son2", ros::Time(0));
            // header也称之为父坐标轴
            ROS_INFO("Son1 相对于 Son2 的坐标关系:父坐标系ID=%s",tfs.header.frame_id.c_str());
            ROS_INFO("Son1 相对于 Son2 的坐标关系:子坐标系ID=%s",tfs.child_frame_id.c_str());
            ROS_INFO("Son1 相对于 Son2 的坐标关系:x=%.2f,y=%.2f,z=%.2f",
                    tfs.transform.translation.x,
                    tfs.transform.translation.y,
                    tfs.transform.translation.z);

            // 坐标点解析 先生成一个座标点ps
            geometry_msgs::PointStamped ps;
            ps.header.frame_id = "son1";
            ps.header.stamp = ros::Time::now();
            ps.point.x = 1.0;
            ps.point.y = 4.0;
            ps.point.z = 8.0;

            geometry_msgs::PointStamped psAtSon2;
            psAtSon2 = buffer.transform(ps, "son2");
            ROS_INFO("设立在son1坐标系下的ps点 在Son2 中的坐标变为:x=%.2f,y=%.2f,z=%.2f",
                    psAtSon2.point.x,
                    psAtSon2.point.y,
                    psAtSon2.point.z
                    );
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        r.sleep();
        ros::spinOnce();
    }
}

 