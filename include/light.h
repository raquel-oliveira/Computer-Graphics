#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "vec3.h"
#include <string>
#include <cmath>
#define PI 3.14159265

//https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-lights

using namespace utility;

class Light{
  protected:
    Color3 intensity;

  public:
    Light(Color3 i):
      intensity(i){}

    virtual Color3 get_intensity(Point3 hit) {return intensity;}

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

    inline Vec3 get_l(Point3 hit);

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

    inline Vec3 get_l(Point3 hit);

};

class SpotLight : public Light {
  private:
    Point3 light_from;
    Point3 light_at;
    float cutoff_angle;

  public:
    Vec3 dir;

    SpotLight(Color3 i, Point3 lf, Point3 la, float angle) :
      Light(i), light_from(lf), light_at(la) {
        cutoff_angle = std::cos(angle*PI/180.0);
        dir = light_at - light_from;
        dir.make_unit_vector();
    }

    inline float get_angle() { return cutoff_angle; }

    Color3 get_intensity(Point3 hit);

    std::string get_info(std::string tab);

    inline Vec3 get_l(Point3 hit);

};
#endif
