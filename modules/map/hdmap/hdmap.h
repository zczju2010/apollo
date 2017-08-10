/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef MODULES_MAP_HDMAP_HDMAP_H_
#define MODULES_MAP_HDMAP_HDMAP_H_

#include <memory>
#include <string>
#include <vector>

#include "modules/common/macro.h"
#include "modules/common/proto/geometry.pb.h"
#include "modules/map/hdmap/hdmap_common.h"
#include "modules/map/hdmap/hdmap_impl.h"
#include "modules/map/proto/map_crosswalk.pb.h"
#include "modules/map/proto/map_junction.pb.h"
#include "modules/map/proto/map_lane.pb.h"
#include "modules/map/proto/map_overlap.pb.h"
#include "modules/map/proto/map_road.pb.h"
#include "modules/map/proto/map_signal.pb.h"
#include "modules/map/proto/map_stop_sign.pb.h"
#include "modules/map/proto/map_yield_sign.pb.h"

namespace apollo {
namespace hdmap {

class HDMap {
 public:
  static std::unique_ptr<HDMap> CreateMap(const std::string& map_filename);

  // Call SetDefaultMap() before your first call to DefaultMap(), or it will not
  // take effect. It's generally used in test cases' SetUp() function.
  static void SetDefaultMap(const std::string& map_filename);
  // Get default map loaded from the file specified by FLAGS_default_map_file.
  static const HDMap& DefaultMap();

  int load_map_from_file(const std::string& map_filename);

  LaneInfoConstPtr get_lane_by_id(const apollo::hdmap::Id& id) const;
  JunctionInfoConstPtr get_junction_by_id(const apollo::hdmap::Id& id) const;
  SignalInfoConstPtr get_signal_by_id(const apollo::hdmap::Id& id) const;
  CrosswalkInfoConstPtr get_crosswalk_by_id(const apollo::hdmap::Id& id) const;
  StopSignInfoConstPtr get_stop_sign_by_id(const apollo::hdmap::Id& id) const;
  YieldSignInfoConstPtr get_yield_sign_by_id(const apollo::hdmap::Id& id) const;
  OverlapInfoConstPtr get_overlap_by_id(const apollo::hdmap::Id& id) const;
  RoadInfoConstPtr get_road_by_id(const apollo::hdmap::Id& id) const;

  int get_lanes(const apollo::common::PointENU& point, double distance,
                std::vector<LaneInfoConstPtr>* lanes) const;
  int get_junctions(const apollo::common::PointENU& point, double distance,
                    std::vector<JunctionInfoConstPtr>* junctions) const;
  int get_signals(const apollo::common::PointENU& point, double distance,
                  std::vector<SignalInfoConstPtr>* signals) const;
  int get_crosswalks(const apollo::common::PointENU& point, double distance,
                     std::vector<CrosswalkInfoConstPtr>* crosswalks) const;
  int get_stop_signs(const apollo::common::PointENU& point, double distance,
                     std::vector<StopSignInfoConstPtr>* stop_signs) const;
  int get_yield_signs(const apollo::common::PointENU& point, double distance,
                      std::vector<YieldSignInfoConstPtr>* yield_signs) const;
  int get_roads(const apollo::common::PointENU& point, double distance,
                std::vector<RoadInfoConstPtr>* roads) const;

  int get_nearest_lane(const apollo::common::PointENU& point,
                       LaneInfoConstPtr* nearest_lane, double* nearest_s,
                       double* nearest_l) const;
  int get_nearest_lane_with_heading(const apollo::common::PointENU& point,
                                    const double distance,
                                    const double central_heading,
                                    const double max_heading_difference,
                                    LaneInfoConstPtr* nearest_lane,
                                    double* nearest_s, double* nearest_l) const;
  int get_lanes_with_heading(const apollo::common::PointENU& point,
                             const double distance,
                             const double central_heading,
                             const double max_heading_difference,
                             std::vector<LaneInfoConstPtr>* lanes) const;
  int get_road_boundaries(const apollo::common::PointENU& point, double radius,
                          std::vector<RoadROIBoundaryPtr>* road_boundaries,
                          std::vector<JunctionBoundaryPtr>* junctions) const;

 private:
  HDMapImpl _impl;
};

}  // namespace hdmap
}  // namespace apollo

#endif  // MODULES_MAP_HDMAP_HDMAP_H_
