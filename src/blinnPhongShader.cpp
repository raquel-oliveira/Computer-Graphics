#include "shader.h"
#include "vec3.h"
#include <sstream>      // std::ostringstream
#include <math.h>       /* pow */

Color3 BlinnPhongShader::find_color(Scene scene, const Ray& r_) const{
  Hit hr, srec;
  if(intersect(scene, r_, hr)){
    Color3 color(0,0,0);
    float cosNL = 0; float cosNH =0;
    Color3 difuseR = hr.material->kd();
    Color3 specularR = hr.material->ks();
    Color3 ambientR = hr.material->ka();
    for(const auto &l : scene.getLights()){
      Vec3 lvalue = l->get_l(hr.point); lvalue.make_unit_vector();
      Ray p(hr.point+0.01*hr.normal, lvalue);
    //  if(!(intersect(scene, p, srec))){
        Vec3 v = r_.get_origin() - hr.point; v.make_unit_vector();
        Vec3 hvalue = v + lvalue; hvalue.make_unit_vector();
        cosNL = dot(hr.normal,lvalue);
        cosNH = dot(hr.normal, hvalue);
        float maxNL = std::max(0.f, (float)cosNL);
        float maxNH = std::max(0.f, (float)cosNH);
        color += difuseR * l->get_intensity() * maxNL;
        color += specularR * l->get_intensity() * pow(maxNH, hr.material->get_alpha());
    //  }
    }
    color+= ambientR * scene.getAmbientLight()->get_intensity();
    return color;
  }
  return scene.getBg()->get(r_);
}

std::string BlinnPhongShader::get_info(std::string tab){
  std::ostringstream info;
      info << tab << "Blinn-Phong Shader\n";
return info.str();
}
