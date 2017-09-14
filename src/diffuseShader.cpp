#include "shader.h"
#include "util.h"
#include <sstream>      // std::ostringstream
#include <math.h>       /* pow */

Color3 DiffuseShader::find_color(Scene scene, const Ray& r_) const{
  Hit hr;
  if(intersect(scene, r_, hr)){
    Vec3 target = hr.point + hr.normal + random_point_sphere();
    return 0.5*find_color(scene, Ray(hr.point, target-hr.point));
  }
  return scene.getBg()->get(r_);
}

std::string DiffuseShader::get_info(std::string tab){
  std::ostringstream info;
      info << tab << "Diffuse Shader\n";
return info.str();
}
