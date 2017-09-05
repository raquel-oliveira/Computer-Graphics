#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "vec3.h"
#include <sstream>      // std::ostringstream

class Material {

  private:
    Color3 k_s; // specular reflection
    Color3 k_d; // difuse reflection
    Color3 k_a; // ambient reflection
    float alpha; //shininess

  public:
    Material(Color3 ks, Color3 kd, Color3 ka, float alpha_):
      k_s(ks), k_d(kd), k_a(ka), alpha(alpha_){}

    inline Color3 ks(){return k_s;}
    inline Color3 kd(){return k_d;}
    inline Color3 ka(){return k_a;}
    inline Color3 get_alpha(){return alpha;}

    inline std::string get_info(std::string tab){
      std::ostringstream info;
      info << tab << "Material : \n";
      info << tab << "\t Specular reflection(k_s)" << k_s << "\n";
      info << tab << "\t Difuse reflection(k_d)" << k_d << "\n";
      info << tab << "\t Ambient reflection(k_a)" << k_a << "\n";
      info << tab << "\t Shiness(alpha)" << alpha << "\n";

      return info.str();
    }
};

#endif
