#include "image_texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image_texture::Image_texture(char const* path_image){
  int width, height, u;
  unsigned char* d = stbi_load(path_image, &width, &height, &u, 0);
  data = d;
  nx = width;
  ny = height;
  path = path_image;
}

Color3 Image_texture::value(float u, float v, const Vec3& p) const {
     int i = (  u)*nx;
     int j = (1-v)*ny-0.001;
     if (i < 0) i = 0;
     if (j < 0) j = 0;
     if (i > nx-1) i = nx-1;
     if (j > ny-1) j = ny-1;
     float r = int(data[3*i + 3*nx*j]  ) / 255.0;
     float g = int(data[3*i + 3*nx*j+1]) / 255.0;
     float b = int(data[3*i + 3*nx*j+2]) / 255.0;
     return Color3(r, g, b);
}

std::string Image_texture::get_info(std::string tab){
  std::ostringstream info;

  info << tab <<"Image Texture: \n";
  info << tab <<"\tPath: " << path << "\n";
  return info.str();
}
