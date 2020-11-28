#include "ros/ros.h"
#include "std_srvs/SetBool.h"

bool licht_callback(std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res){
  if(req.data == true){
    res.success = true;
    res.message = "Licht An!";
    return true;
  }else if(req.data == false){
    res.success = true;
    res.message = "Licht Aus!";
    return true;
  }
  return false;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_server");
  ros::NodeHandle nh;

  ros::ServiceServer mein_server = nh.advertiseService("service_server", licht_callback);

  ROS_INFO("Lichtschalter bereit...");
  ros::spin();

  return 0;
}
