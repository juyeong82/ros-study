#include <ros/ros.h>
#include <std_msgs/String.h>

// callback 함수입니다.
//
// subscriber가 연결된 topic에 message가 들어올 때마다 ROS가 이 함수를 호출합니다.
// docking_app/sp2_docking_manager에서 robot_stateCallback 같은 함수가 자동으로 불리는 것도
// 이 callback 구조와 같은 원리입니다.
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("subscribe: %s", msg->data.c_str());
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;

    // subscribe는 "나는 이 topic을 받고 싶다"고 ROS master에 등록합니다.
    //
    // topic 이름: chatter
    // queue size: 10
    // callback: chatterCallback
    ros::Subscriber chatter_sub = nh.subscribe("chatter", 10, chatterCallback);

    // spin은 callback loop입니다.
    // message가 들어오면 callback을 실행하고, 종료 신호가 올 때까지 계속 대기합니다.
    ros::spin();

    return 0;
}

