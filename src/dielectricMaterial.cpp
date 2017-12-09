#include "material.h"
#include "util.h"
#include "object.h"
#include "vec3.h"

bool DielectricMaterial::refract (const Vec3& v,const Vec3& n, float ni_over_nt, Vec3& refracted) const{
    Vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0){
      refracted = ni_over_nt*(uv-n*dt) - n*sqrt(discriminant);
      return true;
    }
    return false;
}

bool DielectricMaterial::refract (const Vec3& normal, const Vec3& incident, Vec3& refracted, float n1, float n2) const{
  Vec3 incident2 = unit_vector(incident);
  float n = n1/n2;
  float cosI = -dot(normal, incident2);
  float sinT2 = n*n*(1.0 - cosI * cosI);
  float cosT = sqrt(1.0 - sinT2);
  if (sinT2 > 1.0) return false;
  else{
    refracted = n*incident2+(n *cosI - cosT) *normal;
    return true;
  }
}

float DielectricMaterial::reflectance(const Vec3& normal, const Vec3& incident, float n1, float n2) const{
			const float n = n1 / n2;
			const float cosI = -dot(normal, incident);
			const float sinT2 = n * n * (1.0 - cosI * cosI);

			if (sinT2 > 1.0){
				return 1.0;
			}

			const float cosT = sqrt(1.0 - sinT2);
			const float r0rth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
			const float rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
			return (r0rth * r0rth + rPar * rPar)/2.0;
		}


float DielectricMaterial::schlick(float cosine, float ref_idx) const{
  float r0 = (1-ref_idx)/(1+ref_idx);
  r0 = r0*r0;
  return r0 + (1-r0)*pow((1-cosine),5);
}

/*source: Reflections and Refractions in Ray Tracing: Bram de Greve (bram.degreve@gmail.com)*/
float DielectricMaterial::schlick2(const Vec3& normal, const Vec3& incident, float n1, float n2) const{
  float r0 = (n1 - n2) / (n1 + n2);
  r0 *= r0;
  float cosX = -1*dot(normal, incident);
  if (n1 > n2){
    const float n = n1/n2;
    const float cosI = -1* dot(normal, incident);
    const float sinT2 = n*n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0) return 1.0;
    cosX = sqrt(1.0 - sinT2);
  }
  const double x = 1.0 - cosX;
  return r0 + (1.0 - r0) * pow(x, 5);
}

bool DielectricMaterial::scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const{
  Vec3 outward_normal;
  float ni_over_nt;
  attenuation = Vec3(1.0,1.0,1.0); //Attenuation is always 1— the glass surface absorbs nothing.
  //Change attenuation to albedo to have 'color'.
  Vec3 refracted;
  float reflect_prob = 0.0;
  float cosine;

  float cos_dir_normal = dot(r.get_direction(), hr.normal);
  if (cos_dir_normal > 0){
    outward_normal = -hr.normal;
    ni_over_nt = ref_idx;
    cosine = cos_dir_normal /r.get_direction().length();
    cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));
    //cosine = ref_idx * cos_dir_normal / r.get_direction().length();
    //cosine = ref_idx * cos_dir_normal;
  } else{
    outward_normal = hr.normal;
    ni_over_nt = 1.0/ref_idx;
    cosine = -(cos_dir_normal /r.get_direction().length());
    //cosine = -1 * cos_dir_normal;
  }

//if(refract(outward_normal, r.get_direction(), refracted, 1.0, ni_over_nt)){
  if (refract(r.get_direction(), outward_normal, ni_over_nt, refracted)){
    reflect_prob = schlick(cosine, ni_over_nt);
    //scattered = Ray(hr.point, refracted);
    //reflect_prob = schlick(cosine, ref_idx);
    //reflect_prob = schlick2(hr.normal, r.get_direction(), 1.0, ni_over_nt);
  } else {
    /*scattered = Ray(hr.point, reflected);
    return true;*/
    reflect_prob = 1.0;
  }

//if (reflectance(outward_normal, r.get_direction(), 1.0, ni_over_nt) < reflect_prob){
  if (drand48() < reflect_prob){
    Vec3 reflected = reflect(r.get_direction(), hr.normal);
    scattered = Ray(hr.point, reflected);
  } else {
    scattered = Ray(hr.point, refracted);
  }
  return true;
}

std::string DielectricMaterial::get_info(std::string tab){
  std::ostringstream info;
  info << tab << "Dielectric\n";
  info << tab << "\tRefractive indice :" << ref_idx;
  return info.str();
}
