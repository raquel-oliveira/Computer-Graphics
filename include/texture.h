#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "vec3.h"
#include <string>

class Texture {
  public:
      virtual Color3 value(float u, float v, const Vec3& p) const = 0;
      virtual std::string get_info(std::string tab) = 0;
};

class Constant_texture : public Texture{
  private:
    Color3 color;
  public:
    Constant_texture(Color3 c) : color(c) {}
    Color3 value(float u, float v, const Vec3& p) const{ return color;}
    std::string get_info(std::string tab){
      std::ostringstream info;

      info << tab <<"Constant Texture: \n";
      info << tab << tab << "\t Color :" << color << "\n";

      return info.str();
    }
};

#endif
