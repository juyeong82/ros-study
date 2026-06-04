# ROS1 Study Workspace

ROS1 Noetic / catkin 기본기를 연습하기 위한 공부용 워크스페이스입니다.

## 구조

```text
ros_study_ws/
├── src/
│   └── ros_basics/
│       ├── src/
│       │   ├── hello_node.cpp
│       │   ├── talker.cpp
│       │   └── listener.cpp
│       ├── launch/
│       │   └── talker_listener.launch
│       ├── CMakeLists.txt
│       └── package.xml
└── README.md
```

## 빌드

```bash
cd ~/ros_study_ws
catkin_make
source devel/setup.bash
```

## 실행 1: hello node

터미널 1:

```bash
roscore
```

터미널 2:

```bash
cd ~/ros_study_ws
source devel/setup.bash
rosrun ros_basics hello_node
```

## 실행 2: publisher / subscriber

터미널 1:

```bash
roscore
```

터미널 2:

```bash
cd ~/ros_study_ws
source devel/setup.bash
rosrun ros_basics talker
```

터미널 3:

```bash
cd ~/ros_study_ws
source devel/setup.bash
rosrun ros_basics listener
```

## 실행 3: launch 파일로 한 번에 실행

```bash
cd ~/ros_study_ws
source devel/setup.bash
roslaunch ros_basics talker_listener.launch
```
