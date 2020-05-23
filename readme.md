# Team102 rushbot

小组项目：物品检测与抓取机器人



### 使用说明

1. 在 `catkin工作目录/src` 下放置 `rushbot`、`waterplus_map_tools`、`xfyun_waterplus` 三个 package

   其中 `rushbot` 为小组机器人主要功能包，`waterplus_map_tools`、`xfyun_waterplus`为外部依赖包

2. 编译

   ```
   rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y
   catkin_make
   source ./devel/setup.bash
   ```



### 文件说明

#### Package: wpb_home_bringup

##### code: wpb_home_core.cpp

可提供功能：设置机器人相连的串口、发布 tf 变换

订阅的主题：

- `/cmd_vel` 控制线速度和角速度
- `/wpb_home/mani_ctrl` 控制高度升降和手爪123
- `/wpb_home/ctrl` 识别消息中的 'pose_diff reset' 命令，并将 pose_diff_msg 归零

发布的主题：

- `/imu/data_raw` 惯性测量单元数据发布：自身位姿（位姿包含位置和姿态）
- `/joint_states` 控制机器人关节位置、速度和力
- `/odom` 机器人在自由空间中的位置和速度估算值
- `/wpb_home/pose_diff` 两次处理 pose 的变化（应该是指姿态）