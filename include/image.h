#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "vec3.h"
#include <sstream>      // std::stringstream, std::stringbuf
#include <fstream>

#define MAX 255
#define NB_CHANNEL 3
#define NAME_IMAGE "background"
#define PATH "output/"

class Image {
  private:
    std::string name;
    int width_size; //largura
    int height_size; //altura
    Color3* pixels;

  public:
    Image(std::string name_, int w, int h)
      : name(name_)
      , width_size(w)
      , height_size(h){
        pixels = new Color3[w*h];
        name = name;
      }

    Image(int w, int h)
      : width_size(w)
      , height_size(h){
        pixels = new Color3[w*h];
        name = NAME_IMAGE;
      }

    ~Image () {
      delete [] pixels;
    }

    inline int width() const { return width_size; }
    inline int height() const { return height_size; }

    inline Color3& operator()(int i, int j){ //By row
      return pixels[i*width_size+j];
    }

    void create_by_binary();
    void create_by_ascii();

};
#endif
