#include "material.h"
#include "util.h"
#include "object.h"

bool LambertianMaterial::scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const{
  Vec3 target = hr.point + hr.normal + random_point_sphere();
  scattered = Ray(hr.point, target-hr.point);
  //attenuation = k_d;
  attenuation = albedo->value(hr.u,hr.v,hr.point);
  return true;
}

std::string LambertianMaterial::get_info(std::string tab){
  std::ostringstream info;
  info << tab << "Lambertian Material\n";
  info << albedo->get_info(tab);
  return info.str();
}
