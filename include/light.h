#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "vec3.h"
#include <string>
#include <cmath>
#include <random>
#define PI 3.14159265

//https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-lights

using namespace utility;

class Light{
  protected:
    Color3 intensity;

  public:
    Light(Color3 i):
      intensity(i){}

    virtual Color3 get_intensity(Point3 hit) {return intensity;}

    virtual std::string get_info(std::string tab) = 0;

    virtual Vec3 get_l(Point3 hit) = 0;

};

class AmbientLight : public Light{
  public:
    AmbientLight(Color3 i):
      Light(i){}

    std::string get_info(std::string tab);

    inline Vec3 get_l(Point3 hit);
};

class DistantLight : public Light {
  private:
    Vec3 direction;

  public:
    DistantLight(Color3 i, Vec3 dist):
      Light(i),
      direction(dist){}

    inline Vec3 get_direction() {return direction;}

    std::string get_info(std::string tab);

    inline Vec3 get_l(Point3 hit);

};

class PontualLight : public Light {
  private:
    Point3 origin;

  public:
    PontualLight(Color3 i, Point3 o):
      Light(i),
      origin(o){}

    inline Point3 get_origin() {return origin;}

    std::string get_info(std::string tab);

    inline Vec3 get_l(Point3 hit);

};

class SpotLight : public Light {
  private:
    Point3 light_from;
    Point3 light_at;
    float cutoff_angle;

  public:
    Vec3 dir;

    SpotLight(Color3 i, Point3 lf, Point3 la, float angle) :
      Light(i), light_from(lf), light_at(la) {
        cutoff_angle = std::cos(angle*PI/180.0);
        dir = light_at - light_from;
        dir.make_unit_vector();
    }

    inline float get_angle() { return cutoff_angle; }

    Color3 get_intensity(Point3 hit);

    std::string get_info(std::string tab);

    inline Vec3 get_l(Point3 hit);

};

class AreaLight : public Light {
  private:
    Point3 upper_left_corner;
    Vec3 vertical_axis;
    Vec3 horizontal_axis;
    int samples;
    std::vector<Light*> lights;
    int nx;
    int ny;

  public:
    AreaLight(Point3 ulc, Vec3 h, Vec3 w, int s, int x, int y, Color3 i)
        : Light(i)
        , upper_left_corner(ulc)
        , vertical_axis(h)
        , horizontal_axis(w)
        , nx(x), ny(y)
        , samples(s) {
          float stepX = 1.0/nx;
          float stepY = 1.0/ny;
          Color3 sub_intensity = intensity/(nx*ny*samples);
          std::random_device rd;
          std::mt19937 gen(rd());
          //TODO: not put always in the center of the pixel
          for(float i = 0; i <= 1.03; i+=stepX){
            for (float j=0; j <= 1.03; j+=stepY){
              for (int k = 0; k < samples; k++){
                float deltax = std::generate_canonical<float, 9> (gen)*0.01;
                float deltay = std::generate_canonical<float, 9> (gen)*0.01;
                Point3 origin = upper_left_corner + (vertical_axis+deltax)*i + (horizontal_axis+deltay)*j;
                lights.push_back(new PontualLight(sub_intensity, origin));
              //  std::cout << lights.size() << std::endl;
              }

            }
          }
        }

    inline std::vector<Light*> getLights(){
      return lights;
    }

    std::string get_info(std::string tab){
      return "Todo";
    }

    inline Vec3 get_l(Point3 hit){
      return Vec3(0,0,0);
    }
};
#endif
