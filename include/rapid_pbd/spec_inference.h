//  Created by YSL on 28/11/2017.
//
//

#ifndef _RAPID_PBD_SPEC_INFERENCE_H_
#define _RAPID_PBD_SPEC_INFERENCE_H_
#include <string>
#include <vector>

#include "rapid_pbd_msgs/Condition.h"
#include "rapid_pbd_msgs/Landmark.h"
#include "rapid_pbd_msgs/Specification.h"
#include "rapid_pbd_msgs/Surface.h"

#include "rapid_pbd/world.h"

namespace rapid {
namespace pbd {
// ConditionGenerator takes landmarks and infers conditions that can be used for
// pre-/postconditions
class SpecInference {
 public:
  std::vector<float> priors_, posteriors_;
  std::vector<rapid_pbd_msgs::Specification> specs_;
  SpecInference(const RobotConfig& robot_config);
  void Init();
  void InitSpecs(std::vector<rapid_pbd_msgs::Specification>* specs,
                 const rapid_pbd_msgs::Landmark& landmark);
  void UpdatePosteriors(const World& world,
                        const rapid_pbd_msgs::Landmark& landmark,
                        std::vector<float>* posteriors);
  void GenerateGrid(const rapid_pbd_msgs::Specification& spec,
                    const rapid_pbd_msgs::Surface& surface,
                    std::vector<geometry_msgs::PoseArray>* grid);

 private:
  World* world_;
  const RobotConfig& robot_config_;
  double distance_cutoff;
  float allowedVariance;
  bool flag1D;
  float avg_dx, avg_dy;

  bool ReferencedLandmark(const rapid_pbd_msgs::Landmark& landmark,
                          const World& world,
                          const double squared_distance_cutoff,
                          rapid_pbd_msgs::Landmark* reference);

  void GetPatternPositions(const int& s,
                           std::vector<geometry_msgs::Pose>* positions,
                           const rapid_pbd_msgs::Landmark& landmark,
                           geometry_msgs::Vector3 obj_distance,
                           const int& obj_num);
  int GetPatternIndex(const std::string& s);
  void UpdatePriors(const std::vector<float>& pOfD,
                    std::vector<float>* posteriors);
  void GetPositions(const geometry_msgs::Point& min_pos,
                    const geometry_msgs::Point& max_pos,
                    const geometry_msgs::Vector3& dimensions,
                    const geometry_msgs::Vector3& obj_distance,
                    std::vector<geometry_msgs::Pose>* positions,
                    const int& obj_num);
};
}  // namespace pbd
}  // namespace rapid

#endif  // _RAPID_PBD_SPEC_INFERENCE_H_
