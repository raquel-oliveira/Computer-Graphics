#include "util.h"

using namespace utility;

//https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rdrnd4.htm
Point3 random_point_sphere(){
  Point3 p;
  do {
    p = 2.0*Point3(drand48(), drand48(), drand48()) - Vec3(1,1,1);
  } while(dot(p,p)>=1.0);
  return p;
}

Color3 interp(Color3 p_0, Color3 p_1, float x){
  return (1-x)*p_0 + x*p_1;
}

Color3 bi_interp(Background* bg, int i, int j, int n_col, int n_row){
  Color3 top = interp(bg->upperLeft(), bg->upperRight(), (float)j/n_col);
  Color3 bottom = interp(bg->lowerLeft(), bg->lowerRight(), (float)j/n_col);
  return interp(top, bottom, (float)(i)/(float)n_row);
}
