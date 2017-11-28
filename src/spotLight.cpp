#include "light.h"
#include <sstream>      // std::ostringstream

inline Vec3 SpotLight::get_l(Point3 hit){
  return light_from - hit;

}

Color3 SpotLight::get_intensity(Point3 hit) {
  Vec3 distance = hit - light_from;
  distance.make_unit_vector();
  float alpha = dot(dir, distance);

  if(alpha > cutoff_angle){ //cos bigger when angle smaller
    return intensity * ((alpha - cutoff_angle)/(1- cutoff_angle));
  } else{
    return Color3(0,0,0);
  }
}

std::string SpotLight::get_info(std::string tab){
  std::ostringstream info;

  info << tab <<"SpotLight : \n";
  info << tab <<"\t Light from :" << light_from << "\n";
  info << tab <<"\t Light at :" << light_at << "\n";
  info << tab <<"\t Angle :" << cutoff_angle << "\n";

  return info.str();
}
