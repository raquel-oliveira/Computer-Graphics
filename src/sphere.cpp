#include "../include/sphere.h"
#include <sstream>      // std::ostringstream

bool Sphere::hit(const Ray &r_, float t_min, float t_max, Hit& hit) const{
  auto dir = r_.get_direction();
  auto orig = r_.get_origin();

  Vec3 oc = orig - center_;
  float a = dot(dir,dir);
  float b = 2.0 * dot(oc, dir);
  float c = dot(oc, oc) - radius_*radius_;
  float delta = b*b - 4*a*c;
  if (delta < 0){ //didn't hit the Sphere
    return false;
  } else{
    float t = (-b - sqrt(delta))/(2*a);
    if (t < t_max && t > t_min) {
      hit.t = t;
      hit.point = r_.point_at(hit.t);
      hit.normal = (hit.point - center_) / radius_;
      hit.material = this->material;
      return true;
    }
    t = (-b + sqrt(delta))/(2*a);
    if (t < t_max && t > t_min) {
      hit.t = t;
      hit.point = r_.point_at(hit.t);
      hit.normal = (hit.point - center_) / radius_;
      hit.material = this->material;
      return true;
    }
    return false; // can not see in this perspective
  }
}

std::string Sphere::get_info(std::string tab){
  std::ostringstream info;
  info << tab << "Sphere: \n";
  info << tab << "\t Center Point: " << center_ << "\n";
  info << tab << "\t Radius Point: " << radius_ << "\n";
  info << material->get_info(tab+"\t") << "\n";

  return info.str();
}
