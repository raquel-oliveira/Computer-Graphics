#include "../include/raytracer.h"
#include "../include/ray.h"
#include <random>   //std::random_device rd; std::mt19937
#include <iostream> //std::random_device rd; std::mt19937

Image Raytracer::render (std::string name, int n_col, int n_row){
  std::random_device rd;
  std::mt19937 gen(rd());
  Image image(name, n_col, n_row);

  for(int i = 0; i < n_row; i++){
    for(int j = 0; j < n_col; j++){
      Color3 col(0,0,0);
      for(int k = 0; k < nb_samples; k++){
        float u = (j+std::generate_canonical<double, 10>(gen))/ n_col;
        float v =  1 - (i+std::generate_canonical<double, 10>(gen))/ n_row;
        Ray r(camera->origin(), camera->llc()+(u*camera->horizontal())+(v*camera->vertical()));
        col+= shader->find_color(scene, r);
      }
      col = col/nb_samples;
      image(i, j) = col;
    }
  }
  return image;
}
