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

2. 拉取仓库
为了开发方便，直接将整个src上传了，开发结束后再进行整理。
  备份原有 `catkin_ws` 下 `src` 目录（如有必要）
进入该目录后，清空该目录下所有内容
  
``` sh
  git init
git remote add origin https://github.com/sebuaa2020/Team102.git
  git pull origin master
```

  不知道什么原因，iai-kinect2 包传不上来，可能需要[安装 iai-kinect2](https://zhuanlan.zhihu.com/p/134058262)


3. 编译

   ``` sh
   rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y
   catkin_make
   source ./devel/setup.bash
   ```

-------------------------------------

### 测试说明

​	测试代码位于 `rushbot/launch/test` 和 `rushbot/src` 目录下。

##### Gmapping 测试方法

1. `roslaunch wpr_simulation wpb_simple.launch`
   Gazebo 运行环境
2. `roslaunch rushbot gmapping_test.launch`
   rviz 调试环境，启动 gmapping 节点
3. 在 gmapp_test.launch 终端中进行键盘控制，绕场一周
4. `rosrun map_server map_saver -f $(roscd rushbot ; pwd)/data/map`
   保存地图于 `$work_dir/rushbot/data` 目录下，命名为 map，共两个文件

##### Waypoint 测试方法

1. `roslaunch wpr_simulation wpb_simple.launch`
   Gazebo 运行环境

2. 保证 `$work_dir/rushbot/data` 目录下，拥有命名为 map 的两个地图文件

3. `roslaunch waterplus_map_tools add_waypoint.launch`
   rviz 调试环境，启动航点添加功能

4. 在 Rviz 工具栏中点击 `Add Waypoint` 工具

5. 在显示的地图中选取指定位置以添加航点

6. ` rosrun waterplus_map_tools wp_saver -f $(roscd rushbot ; pwd)/data/waypoints.xml`
   保存航点文件 waypoints.xml 于指定目录下（ `$work_dir/rushbot/data`）

7. 可对航点文件 waypoints.xml 修改

8. `roslaunch rushbot waypoint_test.launch`

   重新加载已保存航点查看结果

##### Navigation 测试

##### 方法1：图形化界面测试

1. `roslaunch wpr_simulation wpb_simple.launch`
   Gazebo 运行环境
2. `roslaunch rushbot nav_test.launch`
   开启 AMCL 和 move_base，完成导航相关节点加载
3. 若 Gazebo 和 Rviz 中机器人位置不一致，需要对机器人初始位置微调
   （详情见开发手册 37 页）
4. 点击 Rviz `2D Nav Goal` 工具设定导航目标点
5. 机器人规划出紫色路径并移动

##### 方法2：输入目标点测试

1. `roslaunch wpr_simulation wpb_simple.launch`
   Gazebo 运行环境
2. `roslaunch rushbot nav_test.launch`
   开启 AMCL 和 move_base，完成导航相关节点加载
3. 若 Gazebo 和 Rviz 中机器人位置不一致，需要对机器人初始位置微调
   （详情见开发手册 37 页）
4. `rosrun rushbot rushbot_nav_goal`
   启动测试节点并输入 **以地图为坐标系** 的终点目标
5. 机器人规划并移动

##### 方法3：路点巡航测试

1. `roslaunch wpr_simulation wpb_simple.launch`
   Gazebo 运行环境
2. `roslaunch rushbot nav_test.launch`
   开启 AMCL 和 move_base，完成导航相关节点加载
3. 若 Gazebo 和 Rviz 中机器人位置不一致，需要对机器人初始位置微调
   （详情见开发手册 37 页）
4. `rosrun waterplus_map_tools wp_nav_test`
5. 机器人巡航移动