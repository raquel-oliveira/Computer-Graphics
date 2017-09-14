#include "light.h"
#include <sstream>      // std::ostringstream

inline Vec3 PontualLight::get_l(Point3 hit){
  return -1*(hit-origin);
}
std::string PontualLight::get_info(std::string tab){
  std::ostringstream info;

  info << tab <<"Pontual Light: \n";
  info << tab <<"\t Intensity :" << intensity << "\n";
  info << tab <<"\t Origin :" << origin << "\n";

  return info.str();
}
