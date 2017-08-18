#ifndef _UTIL_H_
#define _UTIL_H_

#include "vec3.h"

//https://stackoverflow.com/questions/16329358/remove-spaces-from-a-string-in-c
std::string removeSpaces(std::string input)
{
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}

Color3 interp(Color3 p_0, Color3 p_1, float x){
  return (1-x)*p_0 + x*p_1;
}

Color3 find_color(Color3 upper_left, Color3 upper_right,
                 Color3 lower_left, Color3 lower_right,
                 std::pair <int,int> ij,
                 std::pair <float, float> dimension, //n_col, n_row (xy)
                 const Ray& r_,
                 Sphere s_
                 ){
  float t = s_.hit(r_);
  if( t != -1){
    //return s_.color();
    Vec3 n = unit_vector(r_.point_at(t) - s_.center());
    return 255*(s_.radius()*Vec3(n.x()+1, n.y()+1, n.z()+1)); //return 255*(s_.radius()*(n+1));
  }
  int i = ij.first;
  int j = ij.second;
  int n_col = dimension.first;
  int n_row = dimension.second;
  Color3 top = interp(upper_left, upper_right, (float)j/n_col);
  Color3 bottom = interp(lower_left, lower_right, (float)j/n_col);
  return interp(top, bottom, (float)(n_row-i)/(float)n_row);
}
#endif
