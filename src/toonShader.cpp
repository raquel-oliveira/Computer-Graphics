#include "shader.h"
#include <memory>

Color3 ToonShader::find_color(Scene scene, const Ray& r_) const{
  //normal do hit com a camera
  Hit hr, srec;
  float intensity = 0;
  if(intersect(scene, r_, hr)){
    Color3 color(0,0,0);
    Color3 lineBorder(0,0,0); //black
    Color3 shadow(0.5,0.5,0.5); //grey
    for(const auto &l : scene.getLights()){
      Vec3 eye = r_.get_direction(); eye.make_unit_vector();
      float checkBorder = dot(eye, hr.normal);
      if (checkBorder < 0.2 && checkBorder > -0.2) { return lineBorder;}
      Vec3 lvalue = l->get_l(hr.point); lvalue.make_unit_vector();
      intensity = dot(lvalue, hr.normal);
      Ray p(hr.point+0.01*hr.normal, lvalue);
      if(!(intersect(scene, p, srec))){
        if (intensity > 0.95) color += Color3(1.0,0,0);
        else if (intensity > 0.5) color += Color3(0,1.0,0);
        else if (intensity > 0.25) color+= Color3(0,0,1.0);
        else color += Color3(0.5,0,0.5);
      } else {
        return shadow;
      }
    }
    return color;
  }
  return scene.getBg()->get(r_);
}

std::string ToonShader::get_info(std::string tab){
  return tab+"Toon Shader";
}
