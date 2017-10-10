#include "shader.h"
#include <memory>

Color3 ToonShader::find_color(Scene scene, const Ray& r_) const{
  //normal do hit com a camera
  Hit hr, srec;
  float intensity = 0;
  if(intersect(scene, r_, hr)){
    auto t = std::dynamic_pointer_cast<ToonMaterial>(hr.material);
    if (t == NULL){std::cerr << "Not a Toon material";}
    Color3 color(0,0,0);
    Vec3 eye = r_.get_direction(); eye.make_unit_vector();
    float checkBorder = dot(eye, hr.normal);
    if (checkBorder < 0.2 && checkBorder > -0.2) { return t->lineBorder;} //TODO: allow user to set the edge thickness?

    for(const auto &l : scene.getLights()){
      Vec3 lvalue = l->get_l(hr.point); lvalue.make_unit_vector();
      Ray p(hr.point+0.01*hr.normal, lvalue);
      float intensityl = dot(lvalue, hr.normal);
      intensityl = (intensityl+1)*0.5;

      //TODO: Check shadow inconsistence
      /*
      if(intersect(scene, p, srec)){ //Shadow
        continue;
      } else {
        //intensity = std::max(intensityl, intensity);
        intensity += intensityl;
      }*/
      //Without shadow:
      intensity = std::max(intensityl, intensity);
    }

    for(int i = 1; i < t->intervals.size(); i++){
      if(intensity < 0.01f){
        return Color3(0,0,0); //return t->shadow;
      }
      if (intensity <= t->intervals[i]){
        return t->colors[i-1];
      }
    }
    return Color3(1,1,0); //Should never get here. But let's keep it there for debug
  }
  return scene.getBg()->get(r_);
}

std::string ToonShader::get_info(std::string tab){
  return tab+"Toon Shader with equidistant intervals\n";
}
