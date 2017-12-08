#ifndef _PERLIN_H_
#define _PERLIN_H_

class Perlin{
  public:
    float turb(const Vec3& p, int depth) const;
    float noise(const Vec3& p) const;
  //private:
    Vec3 *ranvec;
    //float *ranfloat;
    int* perm_x;
    int* perm_y;
    int* perm_z;

};
#endif
