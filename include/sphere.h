#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vec3.h"

using namespace utility;

class sphere {
  private:
      point3 center_;
      float radius_;
      color3 color_;

  public:
      sphere():
        center_(0,0,0), radius_(0.5) , color_(255,0,0){}

      sphere(point3 p_0=point3(), float r_0 = float(), color3 c_0=color3())
        : center_(p_0)
        , radius_(r_0)
        , color_(c_0)
      {}

      inline point3 center() const { return center_; }
      inline float radius() const { return radius_; }
      inline color3 color() const { return color_; }

};

#endif
