#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "vec3.h"
#include <string>
#include <sstream>      // std::ostringstream

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
      info << tab << "\tColor :" << color << "\n";

      return info.str();
    }
};

class Checker_texture : public Texture{
  private:
    Texture *odd;
    Texture *even;
  public:
    Checker_texture(Texture* t1, Texture* t2) : odd(t1), even(t2) {}
    Color3 value(float u, float v, const Vec3& p) const{
      float sines = p.sines();
      if(sines < 0) return odd->value(u, v, p);
      else return even->value(u, v, p);
    }

    std::string get_info(std::string tab){
      std::ostringstream info;

      info << tab <<"Checker Texture: \n";
      info << tab <<"\tTexture1: \n";
      info << odd->get_info(tab+"\t");
      info << tab <<"\tTexture2: \n";
      info << even->get_info(tab+"\t");

      return info.str();
    }

};
#endif
