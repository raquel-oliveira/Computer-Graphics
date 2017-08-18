#include "../include/sphere.h"

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
      return true;
    }
    t = (-b + sqrt(delta))/(2*a);
    if (t < t_max && t > t_min) {
      hit.t = t;
      hit.point = r_.point_at(hit.t);
      hit.normal = (hit.point - center_) / radius_;
      return true;
    }
    return false; // can not see in this perspective
  }
}
