#include "navigation.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

double get_goal_x(move_base_msgs::MoveBaseGoal goal) {
    // TODO
    return 0.0;
}

double get_goal_y(move_base_msgs::MoveBaseGoal goal) {
    // TODO
    return 0.0;
}

void set_goal() {
    // TODO
}

// void get_path_plan() {}

int go_to_goal(int argc, char **argv) {
    ros::init(argc, argv, "goal");
   
    set_goal(argc, argv);

    MoveBaseClient move_base_client("move_base", true);
    while (!move_base_client.waitForServer(ros::Duration(5.0))) {
        ROS_INFO("Waiting for the move_base action server to come up...");
    }

    move_base_msgs::MoveBaseGoal goal = get_goal();

    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = get_goal_x(goal);
    goal.target_pose.pose.orientation.w = get_goal_y(goal);

    // ROS_INFO("Sending goal");
    move_base_client.sendGoal(goal);
    move_base_client.waitForResult();
    if (move_base_client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        ROS_INFO("到达目标: ", goal);
        return 0;
    } else {
        ROS_INFO("无法到达目标: ", goal);
        handle_exception(CANNOT_GO_TO_GOAL);
        return -1;
    }
}