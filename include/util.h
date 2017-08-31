#ifndef _UTIL_H_
#define _UTIL_H_

#define TMIN 0
#define TMAX 100000000000000
#include "vec3.h"
#include "object.h" // hit
#include <vector>
#include "scene.h"
#include "background.h"

Color3 interp(Color3 p_0, Color3 p_1, float x){
  return (1-x)*p_0 + x*p_1;
}

Color3 bi_interp(Scene s, int i, int j, int n_col, int n_row){
  Color3 top = interp(s.getBg()->upperLeft(), s.getBg()->upperRight(), (float)j/n_col);
  Color3 bottom = interp(s.getBg()->lowerLeft(), s.getBg()->lowerRight(), (float)j/n_col);
  return interp(top, bottom, (float)(i)/(float)n_row);
}

#endif
