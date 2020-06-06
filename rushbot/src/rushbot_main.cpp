#include <ros/ros.h>
#include <std_msgs/String.h> 
#include <geometry_msgs/Twist.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <waterplus_map_tools/Waypoint.h>
#include <waterplus_map_tools/GetWaypointByName.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>

using namespace std;

#define STATE_WAITING	0
#define STATE_NAV_TO	1
#define STATE_DETECT	2
#define STATE_GRAB		3
#define STATE_NAV_BACK	4
#define STATE_STOP		5
#define STATE_ERROR		6

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
static string strGoto;
static ros::Publisher vel_pub;
static ros::ServiceClient cliGetWPName;
static waterplus_map_tools::GetWaypointByName srvName;
static ros::Publisher add_waypoint_pub;
static ros::Publisher behaviors_pub;
static std_msgs::String behavior_msg;

static ros::Subscriber grab_result_sub;
static bool bGrabDone;

static int nState = STATE_WAITING;
static int nDelay = 0;

static vector<string> arKeyword;

// 将机器人当前位置保存为新航点
void AddNewWaypoint(string inStr)
{
	tf::TransformListener listener;
	tf::StampedTransform transform;
	try
	{
		listener.waitForTransform("/map","/base_footprint",  ros::Time(0), ros::Duration(10.0) );
		listener.lookupTransform("/map","/base_footprint", ros::Time(0), transform);
	}
	catch (tf::TransformException &ex) 
	{
		ROS_ERROR("[lookupTransform] %s",ex.what());
		return;
	}

	float tx = transform.getOrigin().x();
	float ty = transform.getOrigin().y();
	tf::Stamped<tf::Pose> p = tf::Stamped<tf::Pose>(tf::Pose(transform.getRotation() , tf::Point(tx, ty, 0.0)), ros::Time::now(), "map");
	geometry_msgs::PoseStamped new_pos;
	tf::poseStampedTFToMsg(p, new_pos);

	waterplus_map_tools::Waypoint new_waypoint;
	new_waypoint.name = inStr;
	new_waypoint.pose = new_pos.pose;
	add_waypoint_pub.publish(new_waypoint);

	ROS_WARN("[New Waypoint] %s ( %.2f , %.2f )" , new_waypoint.name.c_str(), tx, ty);
}

// 物品抓取模式开关
static void GrabSwitch(bool inActive)
{
	if(inActive == true)
	{
		behavior_msg.data = "grab start";
		behaviors_pub.publish(behavior_msg);
	}
}



// 物品抓取状态
void GrabResultCallback(const std_msgs::String::ConstPtr& res)
{
	int nFindIndex = 0;
	nFindIndex = res->data.find("done");
	if( nFindIndex >= 0 )
	{
		bGrabDone = true;
	}
}

// 物品递给状态
void PassResultCallback(const std_msgs::String::ConstPtr& res)
{
	int nFindIndex = 0;
	nFindIndex = res->data.find("done");
	if( nFindIndex >= 0 )
	{
	}
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "rushbot_main");

	ros::NodeHandle n;
	cliGetWPName = n.serviceClient<waterplus_map_tools::GetWaypointByName>("/waterplus/get_waypoint_name");
	add_waypoint_pub = n.advertise<waterplus_map_tools::Waypoint>( "/waterplus/add_waypoint", 1);
	vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	grab_result_sub = n.subscribe<std_msgs::String>("/rushbot/grab_result",30,&GrabResultCallback);
	behaviors_pub = n.advertise<std_msgs::String>("/rushbot/behaviors", 30);

	ROS_WARN("[main] rushbot_main");
	ros::Rate r(30);
	while(ros::ok())
	{
		// waiting for command
		if(nState == STATE_WAITING)
		{
			nDelay++;
			if (nDelay > 100) {
				nState = STATE_NAV_TO;
				ROS_INFO("main change state : STATE_NAV_TO");
			}
		}
		// navigate to desk
		if(nState == STATE_NAV_TO)
		{
			strGoto = "Desk";
			srvName.request.name = strGoto;
			if (cliGetWPName.call(srvName))
			{
				std::string name = srvName.response.name;
				float x = srvName.response.pose.position.x;
				float y = srvName.response.pose.position.y;
				ROS_INFO("[STATE_GOTO] Get_wp_name = %s (%.2f,%.2f)", strGoto.c_str(),x,y);

				MoveBaseClient ac("move_base", true);
				if(!ac.waitForServer(ros::Duration(5.0)))
				{
					ROS_INFO("The move_base action server is no running. action abort...");
				}
				else
				{
					move_base_msgs::MoveBaseGoal goal;
					goal.target_pose.header.frame_id = "map";
					goal.target_pose.header.stamp = ros::Time::now();
					goal.target_pose.pose = srvName.response.pose;
					ac.sendGoal(goal);
					ac.waitForResult();
					if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
						ROS_INFO("Arrived at %s!",strGoto.c_str());
						nState = STATE_DETECT;
						ROS_INFO("main change state : STATE_DETECT");
						nDelay = 0;
					}
					else
					{
						ROS_INFO("Failed to get to %s ...",strGoto.c_str() );
						nState = STATE_ERROR;
					}
				}

			}
			else
			{
				ROS_ERROR("Failed to call service GetWaypointByName");
			}
		}

		// detect state
		if(nState == STATE_DETECT)
		{
			if(nDelay == 0)
			{
				bGrabDone = false;
				GrabSwitch(true);
			}
			nDelay ++;
			if(bGrabDone == true)
			{
				nState = STATE_NAV_BACK;
				ROS_INFO("main change state : STATE_NAV_BACK");
			}
		}

		// navigate back
		if(nState == STATE_NAV_BACK)
		{
			strGoto = "Start";
			srvName.request.name = strGoto;
			if (cliGetWPName.call(srvName))
			{
				std::string name = srvName.response.name;
				float x = srvName.response.pose.position.x;
				float y = srvName.response.pose.position.y;
				ROS_INFO("[STATE_COMEBACK] Get_wp_name = %s (%.2f,%.2f)", strGoto.c_str(),x,y);

				MoveBaseClient ac("move_base", true);
				if(!ac.waitForServer(ros::Duration(5.0)))
				{
					ROS_INFO("The move_base action server is no running. action abort...");
				}
				else
				{
					move_base_msgs::MoveBaseGoal goal;
					goal.target_pose.header.frame_id = "map";
					goal.target_pose.header.stamp = ros::Time::now();
					goal.target_pose.pose = srvName.response.pose;
					ac.sendGoal(goal);
					ac.waitForResult();
					if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
						ROS_INFO("Arrived at %s!",strGoto.c_str());
						ROS_INFO("main change state : STATE_WAITING");
						nState = STATE_WAITING;
						nDelay = 0;
					}
					else
					{
						ROS_INFO("Failed to get to %s ...",strGoto.c_str() );
						nState = STATE_ERROR;
					}
				}

			}
			else
			{
				ROS_ERROR("Failed to call service GetWaypointByName");
				nState = STATE_ERROR;
			}
		}

		ros::spinOnce();
		r.sleep();
	}

	return 0;
}
