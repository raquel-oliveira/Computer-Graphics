#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vec3.h"
#include "ray.h"
#include "object.h"
#include <string>
#include "material.h"
#include <memory> //shared_ptr

class Sphere : public Object {
  private:
      Point3 center_;
      float radius_;

  public:
      Sphere()
        : Object(std::shared_ptr<Material>(new Material(Color3(0,0,0),Color3(0,0,0),Color3(0,0,0),0)))
        , center_(0,0,0)
        , radius_(0.5){}

      Sphere(Point3 p_0, float r_0, std::shared_ptr<Material> m)
        : Object(m)
        , center_(p_0)
        , radius_(r_0){}

      inline Point3 center() const { return center_; }
      inline float radius() const { return radius_; }

      bool hit(const Ray &r_, float t_min, float t_max, Hit& hit) const;

      void transform(Matrix<float> matrix_);

      std::string get_info(std::string tab);
};


#endif
