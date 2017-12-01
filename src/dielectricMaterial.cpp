#include "material.h"
#include "util.h"
#include "object.h"
#include "vec3.h"

bool DielectricMaterial::refract (const Vec3& v, Vec3& n, float ni_over_nt, Vec3& refracted) const{
    Vec3 uv = v; uv.make_unit_vector();
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0){
      refracted = ni_over_nt*(v-n*dt) - n*sqrt(discriminant);
      return true;
    }
    return false;
}

bool DielectricMaterial::scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const{
  Vec3 outward_normal;
  Vec3 reflected = reflect(r.get_direction(), hr.normal);
  float ni_over_nt;
  attenuation = Vec3(1.0,1.0,1.0); //Attenuation is always 1— the glass surface absorbs nothing.
  Vec3 refracted;

  if (dot(r.get_direction(), hr.normal) > 0){
    outward_normal = -1*hr.normal;
    ni_over_nt = ref_idx;
  } else{
    outward_normal = hr.normal;
    ni_over_nt = 1.0/ref_idx;
  }

  if (refract(r.get_direction(), outward_normal, ni_over_nt, refracted)){
    scattered = Ray(hr.point, refracted);
  } else {
    scattered = Ray(hr.point, reflected);
  //  return false;
  }
  return true;
}

std::string DielectricMaterial::get_info(std::string tab){
  return "Dielectric:";
}
