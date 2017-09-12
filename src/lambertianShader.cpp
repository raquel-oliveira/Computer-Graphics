#include "../include/shader.h"
#include "../include/vec3.h"
#include <sstream>      // std::ostringstream
#include <algorithm>

Color3 LambertianShader::find_color(Scene scene, const Ray& r_) const{
  Hit hr;
  if(intersect(scene, r_, hr)){
    Color3 color(0,0,0);
    float cosNL = 0;
    Color3 incidentLight = hr.material->kd();
    for(const auto &l : scene.getLights()){
      Vec3 lvalue = l->get_l(hr.point);
      lvalue.make_unit_vector();
      cosNL = dot(hr.normal,lvalue);
      float max = std::max(0.f, (float)cosNL);
      color += incidentLight * l->get_intensity() * max;
    }
    color+=scene.getAmbientLight()->get_intensity();
    return color;
  }
  return scene.getBg()->get(r_);
}

std::string LambertianShader::get_info(std::string tab){
  std::ostringstream info;
      info << tab << "Lambertian/Difuse shader\n";
return info.str();
}
