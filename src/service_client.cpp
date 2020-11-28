#include "ros/ros.h"
#include "std_srvs/SetBool.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_client");
  ros::NodeHandle nh;

  ros::ServiceClient mein_client = nh.serviceClient<std_srvs::SetBool>("service_server");

  std_srvs::SetBool srv;
  srv.request.data = atol(argv[1]);

  if (mein_client.call(srv))
  {
    ROS_INFO("Antwort: %d", srv.response.success);
    ROS_INFO("Antwort: %s", srv.response.message.c_str());
  }

  return 0;
}
