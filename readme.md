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