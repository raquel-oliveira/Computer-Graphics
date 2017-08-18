#include "sphere.h"

float Sphere::hit(const Ray &r_) {
  auto dir = r_.get_direction();
  auto orig = r_.get_origin();

  Vec3 oc = orig - center_;
  float a = dot(dir,dir);
  float b = 2.0 * dot(oc, dir);
  float c = dot(oc, oc) - radius_*radius_;
  float delta = b*b - 4*a*c;
  int t1, t2;
  if (delta < 0){ //didn't hit the Sphere
    return -1;
  } else{
    float t1 = (-b + sqrt(delta))/(2*a);
    float t2 = (-b - sqrt(delta))/(2*a);
    if (t1 > 0){
      if (t1 < t2) { return t1;}
      else {
        if (t2 > 0) return t2;
        else return -1; //if both t1 and t2 < 0, can not see in the view
      }
    }
  }
}
