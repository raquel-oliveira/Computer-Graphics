#include "util.h"

using namespace utility;

Color3 interp(Color3 p_0, Color3 p_1, float x){
  return (1-x)*p_0 + x*p_1;
}

Color3 bi_interp(Background* bg, int i, int j, int n_col, int n_row){
  Color3 top = interp(bg->upperLeft(), bg->upperRight(), (float)j/n_col);
  Color3 bottom = interp(bg->lowerLeft(), bg->lowerRight(), (float)j/n_col);
  return interp(top, bottom, (float)(i)/(float)n_row);
}
