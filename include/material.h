#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "vec3.h"
#include <sstream>      // std::ostringstream
#include "object.h"
#include "texture.h"
#include <vector>

class Material {

  protected:
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
    inline float get_alpha(){return alpha;}

    inline virtual bool scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const { return false;}

    virtual Vec3 emitted(float u, float v, const Vec3 &p) const {
      return Vec3(0,0,0);
    }

    inline virtual std::string get_info(std::string tab){
      std::ostringstream info;
      info << tab << "Material : \n";
      info << tab << "\t Specular reflection(k_s)" << k_s << "\n";
      info << tab << "\t Difuse reflection(k_d)" << k_d << "\n";
      info << tab << "\t Ambient reflection(k_a)" << k_a << "\n";
      info << tab << "\t Shiness(alpha)" << alpha << "\n";

      return info.str();
    }
};

class LambertianMaterial : public Material {
  private:
    Texture *albedo;
    bool hasTexture;

  public:
    LambertianMaterial(Color3 a, Texture *b)
     : Material(Color3(0,0,0), a, Color3(0,0,0), 0)
     , albedo(b) {
       hasTexture = true;
     }

     LambertianMaterial(Color3 a)
      : Material(Color3(0,0,0), a, Color3(0,0,0), 0){
        hasTexture = false;
      }

    bool scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const;

    inline std::string get_info(std::string tab);
};

class MetalMaterial : public Material {

  public:
    MetalMaterial(Color3 a)
     : Material(Color3(0,0,0), a, Color3(0,0,0), 0) {}

    bool scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const;

    inline std::string get_info(std::string tab);
};

class ToonMaterial : public Material {
  public:
    std::vector<Color3> colors;
    std::vector<float>intervals;
    Color3 lineBorder;
    Color3 shadow;

    //TODO: create more constructors to allow flexibility for user
    ToonMaterial(std::vector<Color3> c)
     : Material(Color3(0,0,0), Color3(0,0,0), Color3(0,0,0), 0)
     , colors(c)
     , lineBorder(Color3(0,0,0)) //black
     , shadow(Color3(0.1,0.1,0.1)) //grey
     {
       float dif = 1.f/(colors.size()+1);
       intervals.push_back(0);
       for(int i = 0; i < colors.size()-1; i++){
         intervals.push_back(intervals.back()+dif);
       }
       intervals.push_back(1.f);
     }

    bool scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const;

    inline std::string get_info(std::string tab);
};

class DielectricMaterial : public Material {
  private:
    float ref_idx; //refractive indice

  public:

    DielectricMaterial(float refrac)
    : Material(Color3(0,0,0), Color3(0,0,0), Color3(0,0,0), 0),
       ref_idx(refrac)
    {}

    bool refract (const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) const;

    bool refract (const Vec3& normal, const Vec3& incident, Vec3& refracted, float n1, float n2) const;

    float reflectance(const Vec3& normal, const Vec3& incident, float n1, float n2) const;

    float schlick(float cosine, float ref_idx) const;

    float schlick2(const Vec3& normal, const Vec3&incident, float n1, float n2) const;

    bool scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const;

    inline std::string get_info(std::string tab);

};

class Luminary : public Material {
  private:
    Texture* emit;
  public:
    Luminary():
     Material(Color3(0,0,0), Color3(0,0,0), Color3(0,0,0), 0) {
       emit = new Constant_texture(Color3(1,1,1));
     }
    Luminary(Texture *e):
     Material(Color3(0,0,0), Color3(0,0,0), Color3(0,0,0), 0),
     emit(e) {}

    bool scatter(const Ray& r, struct Hit& hr, Vec3& attenuation, Ray& scattered ) const{
      return false;
    }

    Vec3 emitted(float u, float v, const Vec3 &p) const {
      return emit->value(u, v, p);
    }

    inline virtual std::string get_info(std::string tab){
      std::ostringstream info;
      info << tab << "Luminary Material : \n";
      info << emit->get_info(tab+"\t");

      return info.str();
    }
};
#endif
