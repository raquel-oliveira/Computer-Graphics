#ifndef _IMAGE_TEXTURE_H_
#define __IMAGE TEXTURE_H_

#include "texture.h"

class Image_texture : public Texture {
  private:
    unsigned char *data;
    int nx, ny;
    char const *path;

  public:
    Image_texture(char const * path_image);
    Vec3 value(float u, float v, const Vec3& p) const;
    std::string get_info(std::string tab);

};

#endif
