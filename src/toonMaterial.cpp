#include "material.h"
#include "util.h"
#include "object.h"
#include "vec3.h"
#include <sstream>      // std::ostringstream

bool ToonMaterial::scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const{
  //to implement
  return false;
}

std::string ToonMaterial::get_info(std::string tab){
  std::ostringstream info;
  info << tab << " Toon Material - to implement\n";
  info << tab << "\t Shadow color: " << shadow << "\n";
  info << tab << "\t Border line color: " << lineBorder << "\n";

  info << tab << "Intensity-> color:\n";
  for(int i = 1; i < intervals.size(); i++){
    info << tab << "\t\t From " << intervals[i-1] << " to " << intervals[i] << " : " << colors[i-1] << "\n";
  }
  return info.str();
}
