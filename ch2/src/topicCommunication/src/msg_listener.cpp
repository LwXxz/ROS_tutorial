#include "ros/ros.h"
#include "topicCommunication/Person.h"

void doPerson(const topicCommunication::Person::ConstPtr &person_p)
{
    ROS_INFO("info about sub %s %d %f", person_p->name, person_p->age, person_p->height);
}
int main(int argv, char **argc)
{
    setlocale(LC_ALL, "");
    // 唯一的
    ros::init(argv, argc, "person_listener");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<topicCommunication::Person>("chatter", 100, doPerson);

    // 4.回调函数中处理 person

    // 5.ros::spin();
    ros::spin();
    return 0;
}