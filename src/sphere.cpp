#include "sphere.h"
#include <sstream>      // std::ostringstream
//const float PI = acos(-1);

void get_sphere_uv(const Vec3& p, float& u, float& v){
  float phi = atan2(p.z(), p.x());
  float theta = asin(p.y());
  u = 1-(phi+M_PI)/ (2*M_PI);
  v = (theta + M_PI/2)/M_PI;
}

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
      get_sphere_uv(hit.normal, hit.u, hit.v);
      return true;
    }
    t = (-b + sqrt(delta))/(2*a);
    if (t < t_max && t > t_min) {
      hit.t = t;
      hit.point = r_.point_at(hit.t);
      hit.normal = (hit.point - center_) / radius_;
      hit.material = this->material;
      get_sphere_uv(hit.normal, hit.u, hit.v);
      return true;
    }
    return false; // can not see in this perspective
  }
}

void Sphere::transform(Matrix<float> matrix_){

}

std::string Sphere::get_info(std::string tab){
  std::ostringstream info;
  info << tab << "Sphere: \n";
  info << tab << "\tCenter Point: " << center_ << "\n";
  info << tab << "\tRadius Point: " << radius_ << "\n";
  info << tab << "\tTransformation not implemented" << center_ << "\n";
  info << material->get_info(tab+"\t") << "\n";

  return info.str();
}
