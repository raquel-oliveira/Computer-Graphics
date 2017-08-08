/*
Creation of a gradient image 100x200.
Format ppm(P6)

@author Raquel Oliveira
@version 0.2
*/
#include <iostream>
#include <fstream>
#include <stdio.h>

#define MAX 255
#define FILE_NAME "backgroundP6.ppm"
#define X 200
#define Y 100
#define FORMAT "P6"

using namespace std;

struct pixel {
  char r;
  char g;
  char b;
};

int main(){
  cout << "This program will delete the old content of any file with name \" " << FILE_NAME << "\"\n";
  ofstream image (FILE_NAME, std::ios::out | std::ios::trunc | std::ios::binary); // trunc to clear. binary to P6
  int n_col(X); int n_row(Y);
  int size = n_col*n_row;
  struct pixel grad[n_row][n_col];

  float g_c = (float)MAX/(float)n_row;
  float r_c = (float)MAX/(float)n_col;

  int r = 0; int g = MAX; int b = 0;
  //fill matrix of gradient color
  for(int i = 0; i < n_row; i++){
    g = MAX-(int)(g_c*i);
    for(int j = 0; j < n_col; j++){
      r = (int)(r_c*j);
      grad[i][j].r = r;
      grad[i][j].g = g;
      grad[i][j].b = b;
    }
  }
  // Write image
  if (image){
    //Header
    image << FORMAT << "\n" << n_col << " " << n_row << "\n" << MAX << "\n";
    //Content
    image.write((char *)grad, size*3);
    image.close();

  }

  return 0;
}
