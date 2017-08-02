/*
Creation of a gradient image 100x200.
Format ppm(P3)

@author Raquel Oliveira
@version 0.1
*/#include <iostream>
#include <fstream>
#include <stdio.h>

#define MAX 255
#define FILE_NAME "backgroundP3.ppm"
#define X 200
#define Y 100
#define FORMAT "P3"

using namespace std;


int main(){
  fstream image;
  cout << "This program will delete the old content of any file with name \" " << FILE_NAME << "\"\n";
  image.open(FILE_NAME, std::fstream::out | std::fstream::app);

  int n_col(X); int n_row(Y);

  float g_c = (float)MAX/(float)n_row;
  float r_c = (float)MAX/(float)n_col;

  int r = 0; int g = MAX; int b = 0;


  if (image){
    //Header
    image << FORMAT << " " << n_col << " " << n_row << "\n" << MAX << "\n";

    for(int i = 0; i < n_row; i++){
      g = MAX-(int)(g_c*i);
      for(int j = 0; j < n_col; j++){
        r = (int)(r_c*j);
        image << r << " " << g << " " << b << " ";
      }
      image << "\n";
    }
    image.close();
  }

  return 0;
}
