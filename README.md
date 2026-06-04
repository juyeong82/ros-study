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

## 공부 순서

1. `hello_node.cpp`: ROS node가 무엇인지 보기
2. `talker.cpp`: topic publish 연습
3. `listener.cpp`: topic subscribe와 callback 연습
4. `talker_listener.launch`: 여러 node를 launch로 같이 실행하기

## 이 예제가 현재 SR-AMR 코드 읽기에 도움이 되는 이유

`sp2_docking`의 `Sp2DockingManager`도 결국 같은 기본기를 씁니다.

- `subscribe`: `robot_state`, `reflected`, `charge_contact` 등을 받음
- `publish`: `cmd_vel`, `docking/status`, `detection/status` 등을 보냄
- `callback`: topic이 들어오면 함수가 자동 실행됨
- `launch/run`: ROS node를 실행해서 callback loop를 유지함

