#include "image.h"
#define EXTENSION ".ppm"

void Image::create_by_binary(){
  int n_col(width_size);
  int n_row(height_size);
  std::ofstream im (PATH+name+EXTENSION, std::fstream::out | std::ios::trunc | std::ios::binary);

  if(!im){
    std::cerr << "vixe, problem with " << name << std::endl;
  }
  im << "P6" << "\n" << n_col << " " << n_row << "\n" << MAX << "\n";
  for(int i = 0; i < n_row; i++){
    for(int j = 0; j < n_col; j++){
      Color3& ij = (*this)(i,j);
      im << (char)ij.r()  << (char)ij.g() << (char)ij.b();
    }
  }
  im.close();
}

void Image::create_by_ascii(){
  int n_col(width_size);
  int n_row(height_size);
  std::ofstream im (PATH+name+EXTENSION, std::fstream::out | std::ios::trunc );

  if(!im){
    std::cerr << "vixe, problem with " << name << std::endl;
  }
  im << "P3" << "\n" << n_col << " " << n_row << "\n" << MAX << "\n";
  for(int i = 0; i < n_row; i++){
    for(int j = 0; j < n_col; j++){
      Color3& ij = (*this)(i,j);
      im << (int)ij.r() << " " << (int)ij.g() <<  " " << (int)ij.b() << " ";
    }
    im << "\n";
  }
  im.close();
}
