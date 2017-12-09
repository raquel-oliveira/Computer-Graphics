#include "material.h"
#include "util.h"
#include "object.h"

bool LambertianMaterial::scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const{
  Vec3 target = hr.point + hr.normal + random_point_sphere();
  scattered = Ray(hr.point, target-hr.point);
  if (hasTexture){
      attenuation = albedo->value(hr.u,hr.v,hr.point);
  }
  else{
    attenuation = k_d;
  }
  return true;
}

std::string LambertianMaterial::get_info(std::string tab){
  std::ostringstream info;
  info << tab << "Lambertian Material:\n";
  if (hasTexture){
    info << albedo->get_info(tab+"\t");
  } else{
    info << tab << "\tDifuse reflection" << k_d << "\n";
  }
  return info.str();
}
