#include "../include/raytracer.h"
#include <iostream>
#include <string> // stoi (string to int)
#include <map>
#include <fstream>
#include "../include/vec3.h"
#include "../include/ray.h"
#include "../include/sphere.h"
#include <sstream>      // std::stringstream, std::stringbuf
#include "../include/camera.h"
#include "../include/object.h"
#include <vector>
#include "../include/image.h"
#include "../include/scene.h"
#include "../include/shader.h"
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <iomanip> // put_time
#include <memory> //shared_ptr

#define NAME "NAME"
#define TYPE "TYPE"
#define CODIFICATION "CODIFICATION"
#define SIZE_WIDTH "WIDTH"
#define SIZE_HEIGHT "HEIGHT"
#define UPPER_LEFT "UPPER_LEFT"
#define LOWER_LEFT "LOWER_LEFT"
#define UPPER_RIGHT "UPPER_RIGHT"
#define LOWER_RIGHT "LOWER_RIGHT"
#define SAMPLE "SAMPLE"
#define MAX 255
#define NB_CHANNEL 3

//Source: https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
std::string return_current_time_and_date(){
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << "../output/";
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

int main () {
  //Default properties
  std::map<std::string, std::string> properties = { {NAME, "background.ppm"},
                                                    {TYPE, "PPM"},
                                                    {CODIFICATION,"binary"},
                                                    {SIZE_HEIGHT, "600"},
                                                    {SIZE_WIDTH, "1200"},
                                                    {UPPER_LEFT, "127 178 255"},
                                                    {UPPER_RIGHT, "127 178 255"},
                                                    {LOWER_LEFT, "255 255 255"},
                                                    {LOWER_RIGHT, "255 255 255"},
                                                    {SAMPLE, "200"}
                                                  };

  //Parse
  int n_col(std::stoi(properties[SIZE_WIDTH]));
  int n_row(std::stoi(properties[SIZE_HEIGHT]));
  int nb_sample(std::stoi(properties[SAMPLE]));

  std::stringstream ul( properties[UPPER_LEFT] ),
                    ur( properties[UPPER_RIGHT] ),
                    ll( properties[LOWER_LEFT] ),
                    lr( properties[LOWER_RIGHT] );

  Color3 c_ul, c_ur, c_ll, c_lr;
  for (int i = 0; i < NB_CHANNEL; i++){

    ul >> c_ul.e[i];
    ur >> c_ur.e[i];
    ll >> c_ll.e[i];
    lr >> c_lr.e[i];
  }

  std::string time_file = return_current_time_and_date();

  Camera* c = new Camera(Point3(-2.0, -1.0, -1.0), Vec3(0,2,0), Vec3(4,0,0), Point3(0,0,0));
  BackgroundSky bg(c_ul, c_ll);
  std::shared_ptr<Material> nothing(new Material(Color3(0,0,0), Color3(0,0,0), Color3(0,0,0), 0));
  Scene scene(&bg);
  scene.addObject(new Sphere(Point3(0,-100.5,-3), 99.f, nothing));
  scene.addObject(new Sphere(Point3(0.3,0,-1), 0.4, nothing));
  scene.addObject(new Sphere(Point3(0,1,-2), 0.6, nothing));
  scene.addObject(new Sphere(Point3(-0.4,0,-3), 0.7, nothing));
  //Shader* s = new Normal2RGB();
  Shader* s = new Depth(0,4,Color3(0,0,0),Color3(1,1,1));



  /*********RAY TRACE************/
  Raytracer r(c, scene, s, nb_sample );
  Image image = r.render(time_file, n_col, n_row);

  //TODO: Treat TYPE/CODIFICATION
  if (properties[CODIFICATION] == "binary"){
    image.create_by_binary();
  }
  else if (properties[CODIFICATION] == "ascii") {
    image.create_by_ascii();
  } else{
    std::cerr << "Codification not accepted (yet)" << std::endl;
  }
}
