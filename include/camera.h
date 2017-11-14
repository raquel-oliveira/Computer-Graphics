#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vec3.h"
#include <string>
#include <sstream>      // std::ostringstream
#define PI 3.14159265
#include <math.h>       //tan
#include "ray.h"


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

    Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, float vfov, float aspect){
      Vec3 u, v, w;
      float theta = vfov*PI/180; //to rad
      float half_height = tan(theta/2);
      float half_width = aspect *half_height;
      origin_point = lookfrom;
      w = unit_vector(lookfrom-lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w, u);
      lower_left_corner = Vec3(-1*half_width, -1*half_height, -1.0);
      lower_left_corner = origin_point - half_width*u - half_height*v - w;
      horizontal_axis = 2*half_width*u;
      vertical_axis = 2*half_height*v;
    }

    inline Ray get_ray(float s, float t) { return Ray(origin_point, lower_left_corner + s*horizontal_axis + t*vertical_axis - origin_point);}

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
