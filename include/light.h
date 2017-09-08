#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "vec3.h"
#include <string>

//https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-lights

using namespace utility;

class Light{
  protected:
    Color3 intensity;

  public:
    Light(Color3 i):
      intensity(i){}

    inline Color3 get_intensity() {return intensity;}

    virtual std::string get_info(std::string tab) = 0;

    virtual Vec3 get_l(Point3 hit) = 0;

};

class AmbientLight : public Light{
  public:
    AmbientLight(Color3 i):
      Light(i){}

    std::string get_info(std::string tab);

    inline Vec3 get_l(Point3 hit);
};

class DistantLight : public Light {
  private:
    Vec3 direction;

  public:
    DistantLight(Color3 i, Vec3 dist):
      Light(i),
      direction(dist){}

    inline Vec3 get_direction() {return direction;}

    std::string get_info(std::string tab);

    inline Vec3 get_l(Point3 hit) {return direction;}

};

class PontualLight : public Light {
  private:
    Point3 origin;

  public:
    PontualLight(Color3 i, Point3 o):
      Light(i),
      origin(o){}

    inline Point3 get_origin() {return origin;}

    std::string get_info(std::string tab);

    inline Vec3 get_l(Point3 hit){
      return -1*(hit-origin);
    }

};
#endif
