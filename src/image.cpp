#include "../include/image.h"

//TODO: Don't create a buffer. Use and update PIXELS from Image.


void Image::create_by_binary(){
  int n_col(width_size);
  int n_row(height_size);
  std::ofstream im (name, std::fstream::out | std::ios::trunc | std::ios::binary);

  if(!im){
    std::cerr << "vixe, problem with " << name << std::endl;
  }
  im << "P6" << "\n" << n_col << " " << n_row << "\n" << MAX << "\n";
  for(int i = n_row-1; i >=0; i--){
    for(int j = 0; j < n_col; j++){
      //USE PIXEL INFO
    }
  }
  im.close();
}

void Image::create_by_ascii(){
  int n_col(width_size);
  int n_row(height_size);
  std::ofstream im (name, std::fstream::out | std::ios::trunc );

  if(!im){
    std::cerr << "vixe, problem with " << name << std::endl;
  }
  im << "P3" << "\n" << n_col << " " << n_row << "\n" << MAX << "\n";
  for(int i = n_row-1; i >=0; i--){
    for(int j = 0; j < n_col; j++){
      //USE PIXEL INFO
    }
    im << "\n";
  }
  im.close();
}
