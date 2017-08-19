#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"

struct Hit {
    float t;
    Point3 point;
    Vec3 normal;
};

class Object {
  public :
    virtual bool hit(const Ray &ray, float t_min, float t_max, Hit& hit) const = 0;
};

#endif
