#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
	ros::init(argc, argv, "rushbot_nav_goal");

	MoveBaseClient ac("move_base", true);

	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	move_base_msgs::MoveBaseGoal goal;

	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	double x, y;
	ROS_INFO("Please input x y as destination. (x, y) in map frame");
	ROS_INFO("FORMAT: x y");
	scanf("%lf%lf", &x, &y) != 2;
	goal.target_pose.pose.position.x = x;
	goal.target_pose.pose.position.y = y;
	goal.target_pose.pose.orientation.w = 1.0;

	ROS_INFO("Sending goal");
	ac.sendGoal(goal);
	ac.waitForResult();

	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO("Hooray, move successfully");
	else
		ROS_INFO("The base failed to move for some reason"); return 0;
}
