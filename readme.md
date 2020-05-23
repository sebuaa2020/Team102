# Team102 rushbot

小组项目：物品检测与抓取机器人



### 使用说明

1. 安装依赖

   ``` sh
   sudo apt-get install ros-kinetic-joint-state-publisher-gui
   sudo apt-get install ros-kinetic-joy
   sudo apt-get install ros-kinetic-hector-mapping
   sudo apt-get install ros-kinetic-gmapping
   sudo apt-get install ros-kinetic-map-server
   sudo apt-get install ros-kinetic-navigation
   sudo apt-get install ros-kinetic-move-base
   sudo apt-get install ros-kinetic-amcl
   sudo apt-get install ros-kinetic-cv-bridge
   sudo apt-get install ros-kinetic-audio-common
   sudo apt-get install libasound2
   sudo apt-get install ros-kinetic-sound-play
   ```

   [安装 iai-kinect2](https://zhuanlan.zhihu.com/p/134058262)

2. 放置 package `rushbot`、`wpb_home_bringup`、`iai_kinect2`、`waterplus_map_tools`、`xfyun_waterplus` 

3. 编译

   ``` sh
   rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y
   catkin_make
   source ./devel/setup.bash
   ```

