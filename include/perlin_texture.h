#ifndef _PERLIN_TEXTURE_H_
#define _PERLIN_TEXTURE_H_

#include "perlin.h"

class Perlin_texture : public Texture {
  private:
    Perlin p;
    float scale;

  public:
    Perlin_texture(float sc);

    Color3 value(float u, float v, const Vec3& q) const;

    std::string get_info(std::string tab);
};
#endif
