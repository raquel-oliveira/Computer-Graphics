#include <iostream>
#include <string> // stoi (string to int)
//#include <boost/algorithm/string.hpp> // Case insensitive string comparison in C++
#include <map>
#include <fstream>
#include "vec3.h"
#include <sstream>      // std::stringstream, std::stringbuf


#define NAME "NOME"
#define TYPE "TYPE"
#define CODIFICATION "CODIFICATION"
#define SIZE_WIDTH "WIDTH"
#define SIZE_HEIGHT "HEIGHT"
#define UPPER_LEFT "UPPER_LEFT"
#define LOWER_LEFT "LOWER_LEFT"
#define UPPER_RIGHT "UPPER_RIGHT"
#define LOWER_RIGHT "LOWER_RIGHT"
#define MAX 255
#define NB_CHANNEL 3

color interp(color p_0, color p_1, float x){
  return (1-x)*p_0 + x*p_1;
}

int main (void) {
  //Default properties:
  std::map<std::string, std::string> properties = { {NAME, "exemplo.ppm"},
                                                    {TYPE, "ppm"},
                                                    {CODIFICATION,"binary"},
                                                    {SIZE_HEIGHT, "100"},
                                                    {SIZE_WIDTH, "200"},
                                                    {UPPER_LEFT, "255 0 255"}, //magenta
                                                    {UPPER_RIGHT, "0 255 255"}, //cyan
                                                    {LOWER_LEFT, "0 0 0"}, //black
                                                    {LOWER_RIGHT, "255 255 0"} //yellow
                                                  };
  std::string format = "P6";


  // TODO: Read input


  //=== Parse of input
  int n_col(std::stoi(properties[SIZE_WIDTH]));
  int n_row(std::stoi(properties[SIZE_HEIGHT]));
  int size = n_col*n_row;

  color upper_left(0,0,0), upper_right(0,0,0), lower_left(0,0,0), lower_right(0,0,0);
  int value;
  std::stringstream ul( properties[UPPER_LEFT] ),
                    ur( properties[UPPER_RIGHT] ),
                    ll( properties[LOWER_LEFT] ),
                    lr( properties[LOWER_RIGHT] );

  for (int i = 0; i < NB_CHANNEL; i++){
    ul >> upper_left.e[i];
    ur >> upper_right.e[i];
    ll >> lower_left.e[i];
    lr >> lower_right.e[i];
  }

  //TODO: Treat TYPE/CODIFICATION
  // insentive verification!
  //bool is_binary = (std::strcmp(properties[CODIFICATION], "binary")) ? true : false;
  bool is_binary;
  if (properties[CODIFICATION] == "binary"){
    is_binary = true;
  }
  else if (properties[CODIFICATION] == "ascii") {
    is_binary = false;
  } else{
    std::cerr << "Codification not accepted" << std::endl;
  }

  if (is_binary){
    format = "P6";
    std::ofstream image (properties[NAME], std::ios::out | std::ios::trunc | std::ios::binary);

    char * buffer = (char*) malloc(size*3*sizeof(char));
    int add = 0;

    for(int i = 0; i < n_row; i++){
      for(int j = 0; j < n_col; j++){
        color top = interp(upper_left, upper_right, (float)j/n_col);
        color bottom = interp(lower_left, lower_right, (float)j/n_col);
        color bi_int = interp(top, bottom, (float)i/n_row);
        buffer[add++] = char(bi_int.e[0]);
        buffer[add++] = char(bi_int.e[1]);
        buffer[add++] = char(bi_int.e[2]);
      }
    }

    if (image){
      //Header
      image << format << "\n" << n_col << " " << n_row << "\n" << MAX << "\n";
      //Content
      image.write((char *)buffer, size*3);
      delete[] buffer;
      image.close();
    } else {
      std::cout << "vixe, problem with " << properties[NAME] << std::endl;
    }

  }

  else { //is ascii
    format = "P3";
    std::ofstream image (properties[NAME], std::fstream::out | std::ios::trunc );

    if(!image){
      std::cout << "vixe, problem with " << properties[NAME] << std::endl;
    }
    image << format << "\n" << n_col << " " << n_row << "\n" << MAX << "\n";
    for(int i = 0; i < n_row; i++){
      for(int j = 0; j < n_col; j++){
        color top = interp(upper_left, upper_right, (float)j/n_col);
        color bottom = interp(lower_left, lower_right, (float)j/n_col);
        color bi_int = interp(top, bottom, (float)i/n_row);
          image << int(bi_int.e[0]) << " " << int(bi_int.e[1]) << " " << int(bi_int.e[2]) << " ";
      }
      image << "\n";
    }
    image.close();
  }
}
