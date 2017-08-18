#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "vec3.h"
#include <sstream>      // std::stringstream, std::stringbuf
#include <fstream>

#define MAX 255
#define NB_CHANNEL 3
#define NAME "background"

class Image {
  private:
    std::string name;
    int width_size; //largura
    int height_size; //altura
    //char* pixels; //maybe color3?
    //Color3* pixels_color;

  public:
    Image(std::string name_, int w, int h)
      : name(name_)
      , width_size(w)
      , height_size(h){
      //  pixels = (char*) malloc(w*h*NB_CHANNEL*sizeof(char));
      //  pixels_color = malloc(w*h*sizeof(Color3));
        name = name;
      }

    Image(int w, int h)
      : width_size(w)
      , height_size(h){
      //  pixels = (char*) malloc(w*h*NB_CHANNEL*sizeof(char));
      //  pixels_color = malloc(w*h*sizeof(Color3));
        name = NAME;
      }

    ~Image () {
      //delete [] pixels;
      //delete [] pixels_color;
    }

    inline int width() const { return width_size; }
    inline int height() const { return height_size; }

    void create_by_binary();
    void create_by_ascii();

};
#endif
