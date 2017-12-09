#include "texture.h"
#include "perlin.h"
#include "util.h"
 /*************** PERLIN ***************/
float Perlin::noise(const Vec3& p) const {
  int i = floor(p.x());
  int j = floor(p.y());
  int k = floor(p.z());
  float u = p.x() - i; u = u*u*(3-2*u);
  float v = p.y() - j; v = v*v*(3-2*v);
  float w = p.z() - k; w = w*w*(3-2*w);
  /*i = int(4*p.x()) & 255;
  j = int(4*p.y()) & 255;
  k = int(4*p.z()) & 255;
  int idx = perm_x[i] ^ perm_y[j] ^ perm_z[k];
  return ranfloat[idx];*/
  Vec3 c[DIM][DIM][DIM];
  for (int di=0; di <DIM; di++){
    for (int dj=0; dj <DIM; dj++){
      for (int dk=0; dk <DIM; dk++){
        /*c[di][dj][dk] = ranfloat[ perm_x[(i+di) & 255] ^
                                  perm_y[(j+dj) & 255] ^
                                  perm_z[(k+dk) & 255]];
        */
        c[di][dj][dk] = ranvec[ perm_x[(i+di) & 255] ^
                                perm_y[(j+dj) & 255] ^
                                perm_z[(k+dk) & 255]];
      }
    }
  }
  //return trilinear_interp(c, u, v, w);
  return perlin_interp(c, u, v, w);
}

float Perlin::turb(const Vec3& p, int depth) const{
 float accum = 0;
 Vec3 temp_p = p;
 float weight = 1.0;
 for(int i = 0; i < depth; i++){
   accum += weight*noise(temp_p);
   weight *= 0.5;
   temp_p *= 2;
 }
 return fabs(accum); //absolute value
}

/*************** PERLIN TEXTURE ***************/
#include "perlin_texture.h"

Perlin_texture::Perlin_texture(float sc) : scale(sc){
  p.ranvec = perlin_generate();
  p.perm_x = perlin_generate_perm();
  p.perm_y = perlin_generate_perm();
  p.perm_z = perlin_generate_perm();
}

Color3 Perlin_texture::value(float u, float v, const Vec3& q) const{
  //return Vec3(1,1,1)*noise(p);
  return Vec3(1,1,1)*0.5*(1 +sin(scale*q.z()+ 10*p.turb(scale*q, 7)));
}

std::string Perlin_texture::get_info(std::string tab){
  std::ostringstream info;

  info << tab << "Perlin Texture: \n";
  info << tab << "\tScale: " << scale << "\n";
  return info.str();
}
