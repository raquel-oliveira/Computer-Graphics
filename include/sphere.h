#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vec3.h"
#include "ray.h"

using namespace utility;

class Sphere {
  private:
      Point3 center_;
      float radius_;
      Color3 color_;

  public:
      Sphere():
        center_(0,0,0), radius_(0.5) , color_(255,0,0){}

      Sphere(Point3 p_0=Point3(), float r_0 = float(), Color3 c_0=Color3())
        : center_(p_0)
        , radius_(r_0)
        , color_(c_0)
      {}

      inline Point3 center() const { return center_; }
      inline float radius() const { return radius_; }
      inline Color3 color() const { return color_; }

      float hit(const Ray &r_);
};

#endif
