/*
 * Copyright 2015-2019 Autoware Foundation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __MOTION_DATASET_H__
#define __MOTION_DATASET_H__

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include <autoware_msgs/Lane.h>
#include <geometry_msgs/PoseStamped.h>
#include <waypoint_follower/libwaypoint_follower.h>

enum DataType
{
  TYPE_LANE = 0,
  TYPE_POSE = 1,
  TYPE_IDX = 2
};

struct MotionDataset
{
  MotionDataset();
  void reset();
  const bool check() const;
  const int getLaneSize() const;

  const std::pair<int, int> calcNearestPair(unsigned int search_width) const;
  autoware_msgs::Lane lane_;
  geometry_msgs::PoseStamped pose_;
  std_msgs::Int32 closest_idx_;
  std::array<bool, 3> init_;
};

#endif