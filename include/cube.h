#ifndef _CUBE_H_
#define _CUBE_H_
#include "object.h"

class Cube : public Object {
  private:
      Point3 upperLeftCorner;
      float edge;

  public:
      Cube(Point3 ulc, float size, std::shared_ptr<Material> m)
        : Object(m)
        , upperLeftCorner(ulc)
        , edge(size){}

      inline Point3 getUlc() const { return upperLeftCorner; }

      bool hit(const Ray &r_, float t_min, float t_max, Hit& hit) const;

      void transform(Matrix<float> matrix_);

      std::string get_info(std::string tab);
};
#endif
