#ifndef _TRIANGULE_H_
#define _TRIANGULE_H_
#include "object.h"

class Triangule : public Object {
  private:
      Point3 v0;
      Point3 v1;
      Point3 v2;
      bool backfaceCulling;

  public:
      Triangule()
        : Object(std::shared_ptr<Material>(new Material(Color3(0,0,0),Color3(0,0,0),Color3(0,0,0),0)))
        , v0(0,0,0)
        , v1(0,0,0)
        , v2(0,0,0)
        , backfaceCulling(false){}

      Triangule(Point3 v_0, Point3 v_1, Point3 v_2, bool bfc, std::shared_ptr<Material> m)
        : Object(m)
        , v0(v_0)
        , v1(v_1)
        , v2(v_2)
        , backfaceCulling(bfc){}

      inline Point3 getV0() const { return v0; }
      inline Point3 getV1() const { return v1; }
      inline Point3 getV2() const { return v2; }

      bool hit(const Ray &r_, float t_min, float t_max, Hit& hit) const;

      std::string get_info(std::string tab);
};
#endif
