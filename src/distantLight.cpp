#include "../include/light.h"
#include <sstream>      // std::ostringstream

Vec3 DistantLight::get_l(Point3 hit){
  return direction;
}
std::string DistantLight::get_info(std::string tab){
  std::ostringstream info;

  info << tab <<"Distant Light: \n";
  info << tab <<"\t Intensity :" << intensity << "\n";
  info << tab <<"\t Direction :" << direction << "\n";

  return info.str();
}
