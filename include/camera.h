#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vec3.h"
#include <string>
#include <sstream>      // std::ostringstream

class Camera{
  private:
    Point3 lower_left_corner;
    Vec3 vertical_axis;
    Vec3 horizontal_axis;
    Point3 origin_point;

  public:
    Camera()
     : lower_left_corner(-2.0, -1.0, -1.0)
     , vertical_axis(0.0,2.0,0.0)
     , horizontal_axis(4.0,0.0,0.0)
     , origin_point(0,0,0)
    {}

    Camera(Vec3 llf, Vec3 v, Vec3 h, Point3 origin_)
      :lower_left_corner(llf)
      ,vertical_axis(v)
      ,horizontal_axis(h)
      ,origin_point(origin_)
    {}

    inline Vec3 llc() const { return lower_left_corner; }
    inline Vec3 vertical() const { return vertical_axis; }
    inline Vec3 horizontal() const { return horizontal_axis; }
    inline Point3 origin() const { return origin_point; }

    inline std::string get_info(std::string tab){
      std::ostringstream info;

      info << tab <<"Camera: \n";
      info << tab <<"\t Lower left corner :" << lower_left_corner << "\n";
      info << tab <<"\t Vertical axis :" << vertical_axis << "\n";
      info << tab <<"\t Horizontal axis :" << horizontal_axis << "\n";
      info << tab <<"\t Origin point :" << origin_point << "\n";

      return info.str();
    }

};

#endif
