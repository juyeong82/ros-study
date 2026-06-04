#include <ros/ros.h>
#include <std_msgs/String.h>

#include <sstream>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;

    // advertise는 "내가 이 topic에 message를 publish하겠다"고 ROS master에 등록합니다.
    //
    // topic 이름: chatter
    // message 타입: std_msgs::String
    // queue size: 10
    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 10);

    ros::Rate rate(1.0);
    int count = 0;

    while (ros::ok())
    {
        std_msgs::String msg;

        std::stringstream ss;
        ss << "hello ROS topic. count=" << count;
        msg.data = ss.str();

        ROS_INFO("publish: %s", msg.data.c_str());

        // 실제 topic 송신은 publish에서 일어납니다.
        chatter_pub.publish(msg);

        ros::spinOnce();
        rate.sleep();
        count++;
    }

    return 0;
}

