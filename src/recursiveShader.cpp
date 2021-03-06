#include "shader.h"
#include <sstream>      // std::ostringstream

Color3 RecursiveShader::find_color(Scene scene, const Ray& r_) const {
  return find_color2(scene, r_, 0);
}


Color3 RecursiveShader::find_color2(Scene scene, const Ray& r_, int dp) const{
  Hit hr;
  if(intersect(scene, r_, hr)){
    Ray scattered;
    Vec3 attenuation;
    Vec3 emitted = hr.material->emitted(hr.u, hr.v, hr.point);
    if (dp < depth && hr.material->scatter(r_, hr, attenuation, scattered)){
      return emitted + attenuation*find_color2(scene, scattered, dp+1);
    } else{
      return emitted;
    }
  }
  return scene.getBg()->get(r_);
}

std::string RecursiveShader::get_info(std::string tab){
  std::ostringstream info;
      info << tab << "Recursive Shader\n";
      info << tab << "\tDepth: " << depth <<"\n";
return info.str();
}
