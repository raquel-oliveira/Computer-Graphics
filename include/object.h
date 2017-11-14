#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"
#include "material.h"
#include <memory> //shared_ptr
#include "matrix.h"

class Material;

struct Hit {
    float t;
    Point3 point;
    Vec3 normal;
    std::shared_ptr<Material> material;
};

class Object {
  protected:
    std::shared_ptr<Material> material;

  public :
    Object(std::shared_ptr<Material> m): material(m){}
    virtual bool hit(const Ray &ray, float t_min, float t_max, Hit& hit) const = 0;

    virtual void transform(Matrix<float> matrix_) = 0;

    virtual std::string get_info(std::string tab) = 0;
};

#endif
