#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <termios.h>
#include <ros/rate.h>

static float linear_vel = 1;
static float angular_vel = 1;
static int k_vel = 6;

int GetCh()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON);
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  int c = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  return c;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "keyboard_vel_cmd");

  ROS_INFO_STREAM("Keyboard Control");
  ROS_INFO_STREAM("USE wsadqe to control");
  ROS_INFO_STREAM("USE x to break");

  ros::NodeHandle n;
  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

  geometry_msgs::Twist base_cmd;
  base_cmd.linear.x = 0;
  base_cmd.linear.y = 0;
  base_cmd.angular.z = 0;

  ros::Rate frame(30);

  while(n.ok())
  {
    int cKey = GetCh();
    if(cKey=='w')
    {
      base_cmd.linear.x += linear_vel;
      if(base_cmd.linear.x > linear_vel*k_vel)
        base_cmd.linear.x = linear_vel*k_vel;
      cmd_vel_pub.publish(base_cmd);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
    else if(cKey=='s')
    {
      base_cmd.linear.x += -linear_vel;

      if(base_cmd.linear.x < -linear_vel*k_vel)
        base_cmd.linear.x = -linear_vel*k_vel;
      cmd_vel_pub.publish(base_cmd);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
    else if(cKey=='a')
    {
      base_cmd.linear.y += linear_vel;
      if(base_cmd.linear.y > linear_vel*k_vel)
        base_cmd.linear.y = linear_vel*k_vel;
      cmd_vel_pub.publish(base_cmd);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    }
    else if(cKey=='d')
    {
      base_cmd.linear.y += -linear_vel;
      if(base_cmd.linear.y < -linear_vel*k_vel)
        base_cmd.linear.y = -linear_vel*k_vel;
      cmd_vel_pub.publish(base_cmd);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
    else if(cKey=='q')
    {
      base_cmd.angular.z += angular_vel;
      if(base_cmd.angular.z > angular_vel*k_vel)
        base_cmd.angular.z = angular_vel*k_vel;
      cmd_vel_pub.publish(base_cmd);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
    else if(cKey=='e')
    {
      base_cmd.angular.z += -angular_vel;
      if(base_cmd.angular.z < -angular_vel*k_vel)
        base_cmd.angular.z = -angular_vel*k_vel;
      cmd_vel_pub.publish(base_cmd);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
	else if (cKey=='x')
	{
		break;
	}

	frame.sleep();

	base_cmd.linear.x = 0;
	base_cmd.linear.y = 0;
	base_cmd.angular.z = 0;
	cmd_vel_pub.publish(base_cmd);
	printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);

  }
  return 0;
}
