#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <hallowelt/PrimeAction.h>

class PrimeAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<hallowelt::PrimeAction> as_;
  std::string action_name_;
  hallowelt::PrimeFeedback feedback_;
  hallowelt::PrimeResult result_;

public:

  PrimeAction(std::string name) : as_(nh_, name, boost::bind(&PrimeAction::executeCB, this, _1), false), action_name_(name)
  {
    as_.start();
  }

  ~PrimeAction(void)
  {
  }

  void executeCB(const hallowelt::PrimeGoalConstPtr &goal)
  {
    ros::Rate r(1);
    bool success = true;

    feedback_.prime = 0;

    ROS_INFO("%s: Calculating prime values between %lu and %lu", action_name_.c_str(), goal->start, goal->stop);

    for(uint64_t i=goal->start; i<=goal->stop; i++)
    {
      if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        as_.setPreempted();
        success = false;
        break;
      }

      uint64_t j;
      for(j=2; j<=i; j++)
      {
          if(i%j == 0) break;
      }

      if(j==i && j != 2)
      {
        //std::cout<<i<<std::endl;
        feedback_.prime = i;
        as_.publishFeedback(feedback_);
        //r.sleep();
      }
    }

    if(success)
    {
      result_.success = true;
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      as_.setSucceeded(result_);
    }
  }
};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "prime_server");
  PrimeAction prime("prime");
  ros::spin();
  return 0;
}
