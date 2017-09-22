#include "shader.h"
#include <memory>

Color3 ToonShader::find_color(Scene scene, const Ray& r_) const{
  //normal do hit com a camera
  Hit hr, srec;
  float intensity = 0;
  if(intersect(scene, r_, hr)){
    auto t = std::dynamic_pointer_cast<ToonMaterial>(hr.material);
    /*Makes sense ambientecolor in this shader?
    Color3 ambientR = hr.material->ka();
    Color3 color = ambientR * scene.getAmbientLight()->get_intensity();*/
    Color3 color(0,0,0);
    for(const auto &l : scene.getLights()){
      Vec3 eye = r_.get_direction(); eye.make_unit_vector();
      float checkBorder = dot(eye, hr.normal);
      if (checkBorder < 0.2 && checkBorder > -0.2) { return t->lineBorder;} //TODO: allow user to set the edge thickness?
      Vec3 lvalue = l->get_l(hr.point); lvalue.make_unit_vector();
      intensity = dot(lvalue, hr.normal); //TODO: update to multiple lights, so chose the min/max
      Ray p(hr.point+0.01*hr.normal, lvalue);
       if(!(intersect(scene, p, srec))){
        if (t == NULL){std::cerr << "Not a Toon material";}
        for(int i = 1; i < t->intervals.size(); i++){
          if (intensity < t->intervals[i]){
            return t->colors[i-1];
            //color+= t->colors[i-1];break;
          } //TODO: see case of 0 and 1(intensity). else if (intensity == 1 ) color == t->colors[t->colors.size()+1];
        }
      } else {
        //TODO: order of lights, to doesn't color with shadow if another light colored
        return t->shadow;
      }
    }
    return color;
  }
  return scene.getBg()->get(r_);
}

std::string ToonShader::get_info(std::string tab){
  return tab+"Toon Shader with equidistant intervals\n";
}
