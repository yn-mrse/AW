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

#include "matching_score_histogram.h"

#include <pcl/point_types.h>

MatchingScoreHistogram::MatchingScoreHistogram()
    : number_of_bins_(100)
    , bin_width_(0.005)
    , bin_max_height_(100)
{
}

void MatchingScoreHistogram::initHistogram()
{
    jsk_recognition_msgs::HistogramWithRangeBin bin_msg;

    for(size_t i = 0; i < number_of_bins_-1; ++i) {
      bin_msg.min_value = i * bin_width_;
      bin_msg.max_value = (i+1) * bin_width_;
      bin_msg.count = 0;
      histogram_msg_.bins.push_back(bin_msg);
    }

    //to make the scale constant
    bin_msg.min_value = number_of_bins_ * bin_width_;
    bin_msg.max_value = (number_of_bins_+0.001) * bin_width_;
    bin_msg.count = bin_max_height_;
    histogram_msg_.bins.push_back(bin_msg);
}

template<class PointType>
jsk_recognition_msgs::HistogramWithRange MatchingScoreHistogram::createHistogramWithRangeMsg(const std::vector< PointWithDistance<PointType> >& point_with_distance_array)
{
    initHistogram();

    for(const auto point_with_distance : point_with_distance_array) {
        size_t bin_number = point_with_distance.distance / bin_width_;
        if(bin_number > number_of_bins_ - 2) {
            bin_number = number_of_bins_ - 2;
        }

        ++histogram_msg_.bins.at(bin_number).count;

        if(histogram_msg_.bins.at(bin_number).count >= bin_max_height_) {
            histogram_msg_.bins.at(bin_number).count = bin_max_height_;
        }
    }

    return histogram_msg_;
}

template jsk_recognition_msgs::HistogramWithRange MatchingScoreHistogram::createHistogramWithRangeMsg(const std::vector< PointWithDistance<pcl::PointXYZ> >& point_with_distance_array);
template jsk_recognition_msgs::HistogramWithRange MatchingScoreHistogram::createHistogramWithRangeMsg(const std::vector< PointWithDistance<pcl::PointXYZI> >& point_with_distance_array);
template jsk_recognition_msgs::HistogramWithRange MatchingScoreHistogram::createHistogramWithRangeMsg(const std::vector< PointWithDistance<pcl::PointXYZRGB> >& point_with_distance_array);
