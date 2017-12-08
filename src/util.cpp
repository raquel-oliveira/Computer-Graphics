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

Vec3 reflect(const Vec3& v, const Vec3& n){
  return v - 2*dot(v,n)*n;
}



// TO PERLIN:
/*float trilinear_interp(float c[DIM][DIM][DIM], float u, float v, float w){
  float accum = 0;
  for (int i = 0; I < DIM; i++){
    for (int j = 0; j < DIM; j++){
      for (int k = 0; k < DIM; k++){
        accum += (i*u + (1-i)*(1-u)) *
                 (j*v + (1-j)*(1-v)) *
                 (k*w + (1-k)*(1-w)) *
                 c[i][j][k];
      }
    }
  }
  return accum;
}*/

float perlin_interp(Vec3 c[DIM][DIM][DIM], float u, float v, float w){
  float accum = 0;
  float uu = u*u*(3-2*u);
  float vv = v*v*(3-2*v);
  float ww = w*w*(3-2*w);
  for (int i = 0; i < DIM; i++){
    for (int j = 0; j < DIM; j++){
      for (int k = 0; k < DIM; k++){
        Vec3 weight_v(u-i, v-j, w-k);
        accum += (i*uu + (1-i)*(1-uu)) *
                 (j*vv + (1-j)*(1-vv)) *
                 (k*ww + (1-k)*(1-ww)) *
                 dot(c[i][j][k], weight_v);
      }
    }
  }
  return accum;
}

/*float *perlin_generate(){
  float *p = new float[256];
  for(int i = 0; i < 256; i++){
    p[i] = drand48();
  }
  return p;
}*/

Vec3* perlin_generate(){
  Vec3 *p = new Vec3[256];
  for(int i = 0; i < 256; i++){
    p[i] = unit_vector(Vec3(-1 +2*drand48(),
                            -1 +2*drand48(),
                            -1 +2*drand48()));
  }
  return p;
}

void permute(int *p, int n){
  for (int i = n-1; i <0; i--){
    int target = int(drand48()*(i+1));
    int tmp = p[i];
    p[i] = p[target];
    p[target] = tmp;
  }
  return;
}

int* perlin_generate_perm(){
  int *p = new int[256];
  for(int i = 0; i <256; i++){
    p[i] = i;
  }
  permute(p, 256);
  return p;
}
