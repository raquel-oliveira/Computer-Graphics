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

Color3 find_color(Scene scene,const Ray& r_){
  Hit t_prev, t;
  int check = -1;
  Vec3 n;
  for (std::vector<Object*>::iterator it = scene.getObjects()->begin() ; it != scene.getObjects()->end(); it++){
    if ((*it)->hit(r_, TMIN, TMAX, t_prev)){
      if (check == -1){
        t = t_prev; // initialize t_prev
        n = Vec3((t.normal.x()+1), (t.normal.y()+1), (t.normal.z()+1)) * 0.5; //normal gives a number between -1 and 1, an we want between 0 and 1 (+1/2)
      } else {
        if (t_prev.t < t.t){
          t = t_prev;
          n = Vec3((t.normal.x()+1), (t.normal.y()+1), (t.normal.z()+1)) * 0.5;  //normal gives a number between -1 and 1, an we want between 0 and 1 (+1/2)
        }
      }
      check = 0; // hit a object
    }
  }
  if (check == 0){
    return (255*n);
  }

  return scene.getBg()->get(r_);
}

#endif
