# Team102 rushbot

小组项目：物品检测与抓取机器人

视频展示: [https://bhpan.buaa.edu.cn:443/link/7C01871149BC37768A6659E62565AA47](https://bhpan.buaa.edu.cn/link/7C01871149BC37768A6659E62565AA47) Valid Until: 2020-09-30 23:59

### 使用说明

1. 安装依赖

   ```
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
   git clone https://github.com/sebuaa2020/Team102.git
```

   不知道什么原因，iai-kinect2 包传不上来，可能需要[安装 iai-kinect2](https://zhuanlan.zhihu.com/p/134058262)

3. 编译

   ```
   rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y
   catkin_make
   source ./devel/setup.bash
   ```

------

### 测试说明

##### 可靠性测试与模块测试

```
=======
	测试代码位于 `test/code`, `rushbot/launch/test` 和 `rushbot/src` 目录下。

##### 可靠性测试与模块测试

​```sh
>>>>>>> origin/master
python test/code/test_modules.py
```

##### 语音控制测试方法

1. `roslaunch wpr_simulation wpb_simple.launch`

   Gazebo运行环境

2. `roslaunch xfyun_waterplus my_voice_cmd_test.launch`

   开始语音控制机器人运动测试

3. 给机器人发出类似“前”、“后”、“左”、“右”、“停止”的语音指令，观察机器人的运动情况

##### Gmapping 测试方法

1. `roslaunch wpr_simulation wpb_simple.launch` Gazebo 运行环境
2. `roslaunch rushbot gmapping_test.launch` rviz 调试环境，启动 gmapping 节点
3. 在 gmapp_test.launch 终端中进行键盘控制，绕场一周
4. `rosrun map_server map_saver -f $(roscd rushbot ; pwd)/data/map` 保存地图于 `$work_dir/rushbot/data` 目录下，命名为 map，共两个文件

##### Waypoint 测试方法

1. `roslaunch wpr_simulation wpb_simple.launch` Gazebo 运行环境

2. 保证 `$work_dir/rushbot/data` 目录下，拥有命名为 map 的两个地图文件

3. `roslaunch waterplus_map_tools add_waypoint.launch` rviz 调试环境，启动航点添加功能

4. 在 Rviz 工具栏中点击 `Add Waypoint` 工具

5. 在显示的地图中选取指定位置以添加航点

6. `rosrun waterplus_map_tools wp_saver -f $(roscd rushbot ; pwd)/data/waypoints.xml` 保存航点文件 waypoints.xml 于指定目录下（ `$work_dir/rushbot/data`）

7. 可对航点文件 waypoints.xml 修改

8. `roslaunch rushbot waypoint_test.launch`

   重新加载已保存航点查看结果

##### Navigation 测试

##### 方法1：图形化界面测试

1. `roslaunch wpr_simulation wpb_simple.launch` Gazebo 运行环境
2. `roslaunch rushbot nav_test.launch` 开启 AMCL 和 move_base，完成导航相关节点加载
3. 若 Gazebo 和 Rviz 中机器人位置不一致，需要对机器人初始位置微调 （详情见开发手册 37 页）
4. 点击 Rviz `2D Nav Goal` 工具设定导航目标点
5. 机器人规划出紫色路径并移动

##### 方法2：输入目标点测试

1. `roslaunch wpr_simulation wpb_simple.launch` Gazebo 运行环境
2. `roslaunch rushbot nav_test.launch` 开启 AMCL 和 move_base，完成导航相关节点加载
3. 若 Gazebo 和 Rviz 中机器人位置不一致，需要对机器人初始位置微调 （详情见开发手册 37 页）
4. `rosrun rushbot rushbot_nav_goal` 启动测试节点并输入 **以地图为坐标系** 的终点目标
5. 机器人规划并移动

##### 方法3：路点巡航测试

1. `roslaunch wpr_simulation wpb_simple.launch` Gazebo 运行环境
2. `roslaunch rushbot nav_test.launch` 开启 AMCL 和 move_base，完成导航相关节点加载
3. 若 Gazebo 和 Rviz 中机器人位置不一致，需要对机器人初始位置微调 （详情见开发手册 37 页）
4. `rosrun waterplus_map_tools wp_nav_test`
5. 机器人巡航移动

##### Detection 测试

前置依赖：项目仓库下 models 目录下所有文件夹应放置于本机 `~/.gazebo/models` 目录下

1. `roslaunch wpr_simulation wpb_simple.launch` Gazebo 运行环境
2. `roslaunch rushbot obj_detect.launch` 开启 Rviz 并进行相关配置 这里没有开启 AMCL 和 move_base，不能进行导航
3. 在 Gazebo 机器人前方 **2米** 以内摆放一张 **cafe_table**，在上方放置一个 **coke_can**，并将 coke_can Property 中 pose 的 y 值调整为桌面高度：0.77
4. 将 Rviz 边栏中 Kinect 订阅主题改为 `/kinect2/sd/points` 改动之后，Rviz 中机器人面前应有图像出现
5. `roslaunch rushbot all_servers.launch` 启动检测抓取节点
6. 机器人寻找平面后靠近平面检测物体

### 运行说明

1. `roslaunch wpr_simulation wpb_simple.launch`
   Gazebo 运行环境
2. `roslaunch rushbot rushbot_main.launch`
   开启 Rviz 并进行相关配置
