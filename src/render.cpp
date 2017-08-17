#include <iostream>
#include <string> // stoi (string to int)
//#include <boost/algorithm/string.hpp> // Case insensitive string comparison in C++
#include <map>
#include <fstream>
#include "../include/vec3.h"
#include "../include/ray.h"
#include "../include/sphere.h"
#include <sstream>      // std::stringstream, std::stringbuf


#define NAME "NAME"
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

//https://stackoverflow.com/questions/16329358/remove-spaces-from-a-string-in-c
std::string removeSpaces(std::string input)
{
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}

float hit_sphere(const Ray & r_, const sphere s){
  auto dir = r_.get_direction();
  auto orig = r_.get_origin();
  vec3 oc = orig - s.center();
  float a = dot(dir,dir);
  float b = 2.0 * dot(oc, dir);
  float c = dot(oc, oc) - s.radius()*s.radius();
  float delta = b*b - 4*a*c;
  int p1, p2;
  if (delta < 0){ //didn't hit the sphere
    return -1;
  } else{
    float p1 = (-b + sqrt(delta))/(2*a);
    float p2 = (-b - sqrt(delta))/(2*a);
    return p1 < p2? p1: p2;
  }
}

color3 interp(color3 p_0, color3 p_1, float x){
  return (1-x)*p_0 + x*p_1;
}

color3 find_color(color3 upper_left, color3 upper_right,
                 color3 lower_left, color3 lower_right,
                 std::pair <int,int> ij,
                 std::pair <float, float> dimension, //n_col, n_row (xy)
                 const Ray& r_,
                 sphere s_
                 ){
  float t = hit_sphere(r_, s_);
  if( t != -1){
    //return s_.color();
    vec3 n = unit_vector(r_.point_at(t) - s_.center());
    return 255*(s_.radius()*vec3(n.x()+1, n.y()+1, n.z()+1)); //return 255*(s_.radius()*(n+1));
  }
  int i = ij.first;
  int j = ij.second;
  int n_col = dimension.first;
  int n_row = dimension.second;
  color3 top = interp(upper_left, upper_right, (float)j/n_col);
  color3 bottom = interp(lower_left, lower_right, (float)j/n_col);
  return interp(top, bottom, (float)i/n_row);
}

int main (int argc, char* argv[]) {
  //Default properties
  std::map<std::string, std::string> properties = { {NAME, ""},
                                                    {TYPE, ""},
                                                    {CODIFICATION,""},
                                                    {SIZE_HEIGHT, ""},
                                                    {SIZE_WIDTH, ""},
                                                    {UPPER_LEFT, ""},
                                                    {UPPER_RIGHT, ""},
                                                    {LOWER_LEFT, ""},
                                                    {LOWER_RIGHT, ""}
                                                  };
  std::string format = "P6";

  //== READ FILE
  if (argc < 2 ){
    std::cerr << "Gibe me input, plx" << '\n';
  }
  std::string file_name = argv[1];
  std::ifstream file(file_name.c_str(), std::ifstream::in);
  std::string content = "";
  if (file.is_open()) {
    while(!file.eof()){
      getline(file, content);
      std::istringstream field(content);
      //TODO Check if has comments to delete before the parse
      int limiter = content.find_first_of("=");
      if (limiter != std::string::npos) {
        std::string key = content.substr(0,limiter);
        key = removeSpaces(key); //TODO:: also put all Capital letter or Small Letter to make a better comparsion (INSENSITIVE VERIFICATION)
        std::string val = content.substr(limiter+1,content.length());
        if ( properties.find(key) == properties.end() ) {
          //Nothing to do. Not a key defined.
        } else {
          //Update value
          //TODO maybe use a token to check and etc
          properties[key] = val;
        }
      }
    }
  } else{
    std::cerr << "Not a correct file: " << file_name << '\n';
  }

  //=== PARSE INFO
  properties[NAME] = removeSpaces(properties[NAME]);
  properties[CODIFICATION] = removeSpaces(properties[CODIFICATION]);

  int n_col(std::stoi(properties[SIZE_WIDTH]));
  int n_row(std::stoi(properties[SIZE_HEIGHT]));
  int size = n_col*n_row;

  color3 upper_left(0,0,0), upper_right(0,0,0), lower_left(0,0,0), lower_right(0,0,0);
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
  bool is_binary;
  if (properties[CODIFICATION] == "binary"){
    is_binary = true;
  }
  else if (properties[CODIFICATION] == "ascii") {
    is_binary = false;
  } else{
    std::cerr << "Codification not accepted (yet)" << std::endl;
  }

  point3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0,0.0,0.0);  // Horizontal dimension of the plane
  vec3 vertical(0.0,2.0,0.0); // Vertical dimension of the plane
  point3 origin(0,0,0); // the camera's origin

  sphere sp(point3(0,0,-1), 0.5, color3(255,255,255)); //white sphere

  if (is_binary){
    format = "P6";
    std::ofstream image (properties[NAME], std::ios::out | std::ios::trunc | std::ios::binary);

    char * buffer = (char*) malloc(size*3*sizeof(char));
    int add = 0;

    for(int i = 0; i < n_row; i++){ //for(int i = n_row-1; i >=0; i--){
      for(int j = 0; j < n_col; j++){
        float u = (float)j/(float)n_col;
        float v = (float)i/(float)n_row;
        Ray r(origin, lower_left_corner+(u*horizontal)+(v*vertical));
        color3 bi_int = find_color(upper_left, upper_right, lower_left, lower_right, std::make_pair(i,j), std::make_pair(n_col,n_row), r, sp);
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
    for(int i = 0; i < n_row; i++){ //for(int i = n_row-1; i >=0; i--){
      for(int j = 0; j < n_col; j++){
        float u = (float)j/(float)n_col;
        float v = (float)i/(float)n_row;
        Ray r(origin, lower_left_corner+u*horizontal+v*vertical);
        color3 bi_int = find_color(upper_left, upper_right, lower_left, lower_right, std::make_pair(i,j), std::make_pair(n_col,n_row), r, sp);
        image << int(bi_int.e[0]) << " " << int(bi_int.e[1]) << " " << int(bi_int.e[2]) << " ";
      }
      image << "\n";
    }
    image.close();
  }
}
