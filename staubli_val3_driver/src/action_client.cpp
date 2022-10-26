#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <industrial_robot_client/joint_trajectory_action.h>
#include <control_msgs/FollowJointTrajectoryGoal.h>
#include <trajectory_msgs/JointTrajectoryPoint.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "test_staubli");

  // create the action client
  // true causes the client to spin its own thread
  actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> ac("joint_trajectory", true);

  ROS_INFO("Waiting for action server to start.");
  // wait for the action server to start
  ac.waitForServer(); //will wait for infinite time

  ROS_INFO("Action server started, sending goal.");
  // send a goal to the action
  control_msgs::FollowJointTrajectoryGoal goal;
  goal.trajectory.joint_names = std::vector<std::string>{"joint_1", "joint_2", "joint_3", "joint_4", "joint_5", "joint_6"};
  trajectory_msgs::JointTrajectoryPoint point;
  point.positions = std::vector<double>{0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
  goal.trajectory.points.push_back(point);
  ROS_INFO_STREAM(goal);
  ac.sendGoal(goal);

  //wait for the action to return
  bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

  if (finished_before_timeout) {
    actionlib::SimpleClientGoalState state = ac.getState();
    ROS_INFO("Action finished: %s", state.toString().c_str());
  } else {
    ROS_INFO("Action did not finish before the time out.");
  }

  //exit
  return 0;
}