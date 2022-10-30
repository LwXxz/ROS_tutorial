#include "ros/ros.h"
#include "topicCommunication/Person.h"

int main(int argv, char **argc){
    setlocale(LC_ALL, "");

    ros::init(argv, argc, "person_publisher");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<topicCommunication::Person>("chatter", 100);
    
    topicCommunication::Person p;
    p.name = "john";
    p.age = 34;
    p.height = 123;

    ros::Rate r(1);
    while (ros::ok())
    {
        pub.publish(p);
        p.age += 1;
        ROS_INFO("i am %s, %d, %f", p.name, p.age, p.height);
        r.sleep();
        ros::spinOnce();
    }
}
