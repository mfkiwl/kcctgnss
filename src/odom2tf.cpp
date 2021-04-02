#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

double offset_x=0.0;
double offset_y=0.0;
double offset_z=0.0;


void odom_callback(const nav_msgs::Odometry& odom){ 
     static tf::TransformBroadcaster br;
     tf::Transform transform;
          //3D
          //transform.setOrigin( tf::Vector3(float_sensor_data[1], float_sensor_data[0], float_sensor_data[2]) );
          //2D
          transform.setOrigin( tf::Vector3(odom.pose.pose.position.x-offset_x, odom.pose.pose.position.y-offset_y,odom.pose.pose.position.z-offset_z) );
          tf::Quaternion q;
          //q.setRPY(0, 0, float_sensor_data[14]);
          q.setX(odom.pose.pose.orientation.x);
          q.setY(odom.pose.pose.orientation.y);
          q.setZ(odom.pose.pose.orientation.z);
          q.setW(odom.pose.pose.orientation.w);
          transform.setRotation(q);
          br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map","gps_link"));
}

int main(int argc, char **argv){
    
     ros::init(argc, argv, "odom2tf");
     ros::NodeHandle n;

     //param setting
     ros::NodeHandle pn("~");
     //offset xyz
     pn.param<double>("offset_x",offset_x,0.0);
     pn.param<double>("offset_y",offset_y,0.0);
     pn.param<double>("offset_z",offset_z,0.0);

     ros::NodeHandle lSubscriber("");
     ros::Subscriber odom_sub = lSubscriber.subscribe("odom", 50, odom_callback);

     ros::spin();
     
}
