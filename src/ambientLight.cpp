#include "light.h"
#include <sstream>      // std::ostringstream

Vec3 AmbientLight::get_l(Point3 hit){
  return intensity;
}

std::string AmbientLight::get_info(std::string tab){
  std::ostringstream info;

  info << tab <<"Ambient Light: \n";
  info << tab <<"\t Intensity :" << intensity << "\n";

  return info.str();
}
