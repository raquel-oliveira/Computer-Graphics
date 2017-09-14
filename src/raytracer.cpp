#include "raytracer.h"
#include "ray.h"
#include <random>   //std::random_device rd; std::mt19937
#include <iostream> //std::random_device rd; std::mt19937

void Raytracer::get_description(std::string name){
  std::ofstream description_file (name+".txt", std::fstream::out | std::ios::trunc);
  if (!description_file){}
  else{
    //description_file << name << "\n";
    description_file << camera->get_info("");
    description_file << "Number of samples(antialiasing) :" << nb_samples << "\n";
    description_file << "Scene : \n" << scene.get_info("\t") << "\n";
    description_file << shader->get_info("") << "\n";


  }
}

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
        col+= shader->find_color(scene, r);;
      }
      col = col/nb_samples;
      auto r = std::min(1.0f, col.r());
      auto g = std::min(1.0f, col.g());
      auto b = std::min(1.0f, col.b());
      Color3 d(std::sqrt(r), std::sqrt(g), std::sqrt(b));
      image(i, j) = 255*d;
    }
  }
  get_description(PATH+name);
  return image;
}
