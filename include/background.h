#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "vec3.h"
#include "util.h"

Color3 interp(Color3 p_0, Color3 p_1, float x);

class Background {
protected:
    Color3 upper_left;
    Color3 upper_right;
    Color3 lower_left;
    Color3 lower_right;

  public:
    Background(Color3 ul, Color3 ur, Color3 ll, Color3 lr) :
      upper_left(ul),
      upper_right(ur),
      lower_left(ll),
      lower_right(lr) {}

    inline Color3 upperLeft() { return upper_left;}
    inline Color3 upperRight() { return upper_right;}
    inline Color3 lowerLeft() { return lower_left;}
    inline Color3 lowerRight() { return lower_right;}

    virtual Color3 get(Ray r) const = 0;

};

class BackgroundSky : public Background{
  public:
    BackgroundSky(Color3 top, Color3 bottom) :
    Background(top, top, bottom, bottom){}

    Color3 get(Ray r) const{
      Vec3 unit_direction = unit_vector(r.get_direction());
      float t_0 = (unit_direction.y() + 1) * 0.5; //normal gives a number between -1 and 1, an we want between 0 and 1
      return interp(lower_left, upper_left, t_0);
    }
};



#endif
