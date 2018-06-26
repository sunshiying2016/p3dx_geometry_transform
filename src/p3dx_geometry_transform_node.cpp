#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>

class p3dx_odom_transformer
{
private:
  ros::NodeHandle n_;
  ros::Subscriber sub_;
  ros::Publisher pub_posestamped_;
  ros::Publisher pub_twist_;
  
public:
  p3dx_odom_transformer()
  {}
  
  ~p3dx_odom_transformer()
  {}
  
  void init()
  {
    sub_ = n_.subscribe("/odom", 1000, &p3dx_odom_transformer::callback, this);
    pub_posestamped_ = n_.advertise<geometry_msgs::PoseStamped>("/robot",1000);
    pub_twist_ = n_.advertise<geometry_msgs::Twist>("/vel",1000);
  }
  
  void callback(const nav_msgs::Odometry::ConstPtr & msg)
  {
    geometry_msgs::PoseStamped pose_stamped;
    geometry_msgs::Twist vel;
    pose_stamped.header = msg->header;
    pose_stamped.pose = msg->pose.pose;
    vel = msg->twist.twist;
    
    pub_posestamped_.publish(pose_stamped);
    pub_twist_.publish(vel);
    
  }
  
  
  
};


int main(int argc, char ** argv)
{
  ros::init(argc, argv, "p3dx_geometry_transform");
  p3dx_odom_transformer trans;
  trans.init();
  
  ros::spin();
  
  return 0;
}
