#include "material.h"
#include "util.h"
#include "object.h"
#include "vec3.h"


bool MetalMaterial::scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const{
  Vec3 v = r.get_direction();
  v.make_unit_vector();
  Vec3 reflected = reflect(v, hr.normal);
  scattered = Ray(hr.point, reflected);
  attenuation = k_d;
  return (dot(scattered.get_direction(), hr.normal) > 0);
}

std::string MetalMaterial::get_info(std::string tab){
  return "Metal - to implement";
}
