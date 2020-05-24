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

2. 拉取仓库
为了开发方便，直接将整个src上传了，开发结束后再进行整理。
备份原有 catkin_ws 下 src 目录
进入该目录后，清空该目录下所有内容（如有必要）

``` sh
git init
git remote add origin https://github.com/sebuaa2020/Team102.git
git pull origin master
```


3. 编译

   ``` sh
   rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y
   catkin_make
   source ./devel/setup.bash
   ```

