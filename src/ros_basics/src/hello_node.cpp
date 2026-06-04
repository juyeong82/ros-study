#include <ros/ros.h>

int main(int argc, char** argv)
{
    // ros::init은 이 프로세스를 ROS node로 등록할 준비를 합니다.
    // argc/argv를 넘기는 이유는 ROS가 remap argument 같은 ROS 전용 인자를 읽을 수 있기 때문입니다.
    ros::init(argc, argv, "hello_node");

    // NodeHandle은 ROS topic, service, parameter 등을 다룰 때 쓰는 손잡이 같은 객체입니다.
    ros::NodeHandle nh;

    // Rate는 loop 주기를 맞춰주는 도구입니다. 여기서는 1Hz, 즉 1초에 한 번입니다.
    ros::Rate rate(1.0);

    int count = 0;

    // ros::ok()는 ROS가 종료되지 않았으면 true입니다.
    // Ctrl+C를 누르거나 ros::shutdown()이 호출되면 false가 됩니다.
    while (ros::ok())
    {
        ROS_INFO("hello_node is alive. count=%d", count);
        count++;

        // callback이 있다면 처리합니다. 이 예제에는 subscriber가 없지만 습관적으로 넣어둡니다.
        ros::spinOnce();

        // 위에서 만든 1Hz 주기에 맞춰 남은 시간을 sleep합니다.
        rate.sleep();
    }

    return 0;
}

