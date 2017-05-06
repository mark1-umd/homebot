/**
 * @copyright (c) 2017 Mark R. Jenkins.  All rights reserved.
 * @file HAHvacActionServer_test.cpp
 *
 * @author MJenkins, ENPM 808X Spring 2017
 * @date May 2, 2017 - Creation
 *
 * @brief ROS test node for the Home Automation HVAC Action Server
 *
 * This ROS node is executed under the rostest environment to test the Home Automation HVAC Action Server.
 *
 * *
 * * BSD 3-Clause License
 *
 * Copyright (c) 2017, Mark Jenkins
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string>
#include "gtest/gtest.h"
#include "ros/ros.h"

#include "homebot/HBSysOpr.hpp"
#include "homebot/BotMoveBaseOpr.hpp"
#include "homebot/HADoorAffectOpr.hpp"

//#include "homebot/src/HASceneAffectOpr.hpp"
//#include "homebot/src/HAShadeAffectOpr.hpp"


/*******************************************************************************/
// Set up the HAHvacActionServer  action test using the GoogleTest macros
TEST (HomeBotOperations, Constructors) {

  // Create a node handle since we are running as a ROS node
  ros::NodeHandle nh;

  std::string oprCode("BotMoveBase");
  std::string frame_id("map");
  int xPos(23);
  int yPos(17);
  int zPos(11);
  int xOrient(2);
  int yOrient(3);
  int zOrient(5);
  int wOrient(1);

  BotMoveBaseOpr mbOpr(oprCode, frame_id, xPos, yPos, zPos, xOrient, yOrient,
                       zOrient, wOrient);
  EXPECT_EQ(oprCode, mbOpr.getCode());
  move_base_msgs::MoveBaseGoal goal = mbOpr.details();
  EXPECT_EQ(frame_id, goal.target_pose.header.frame_id);
  EXPECT_EQ(xPos, goal.target_pose.pose.position.x);
  EXPECT_EQ(yPos, goal.target_pose.pose.position.y);
  EXPECT_EQ(zPos, goal.target_pose.pose.position.z);
  EXPECT_EQ(xOrient, goal.target_pose.pose.orientation.x);
  EXPECT_EQ(yOrient, goal.target_pose.pose.orientation.y);
  EXPECT_EQ(zOrient, goal.target_pose.pose.orientation.z);
  EXPECT_EQ(wOrient, goal.target_pose.pose.orientation.w);

  oprCode = "HADoor";
  int doorNumber(1);
  int action(0);

  HADoorAffectOpr doorOpr(oprCode, doorNumber, action);
  EXPECT_EQ(oprCode, doorOpr.getCode());
  homebot::HADoorRequest doorReq = doorOpr.details();
  EXPECT_EQ(doorNumber, doorReq.doorNumber);
  EXPECT_EQ(action, doorReq.action);

}

/*******************************************************************************/

/*
 * @brief Initialize ROS and run all of the tests defined in the test macros
 */
int main(int argc, char **argv) {
  // Initialize ROS
  ros::init(argc, argv, "HAHvacActionServer_test");

  // Run all of the Google Test defined tests
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}