#include "raytracer.h"
#include <iostream>
#include <string> // stoi (string to int)
#include <map>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include <sstream>      // std::stringstream, std::stringbuf
#include "camera.h"
#include "object.h"
#include <vector>
#include "image.h"
#include "scene.h"
#include "shader.h"
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <iomanip> // put_time
#include <memory> //shared_ptr
#include "light.h"

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
                                                    {UPPER_LEFT, "0.5 0.7 1"},
                                                    {UPPER_RIGHT, "0.5 0.7 1"},
                                                    {LOWER_LEFT, "1 1 1"},
                                                    {LOWER_RIGHT, "1 1 1"},
                                                    {SAMPLE, "1"}
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

  //Color
  BackgroundSky bg(c_ul, c_ll);
  Color3 neutro(0,0,0);
  Color3 ambiente1(0.1,0.1,0.1);
  Color3 difuso1(0.4,0.4,0.4);
  Color3 difuso2(0.0,0.3,0.8);
  Color3 specular1(1,1,1);
  Color3 specular2(0.9,0.9,0.9);
  //Luzes
  Color3 intensidade1(1,1,1);
  Color3 intensidade2(0.4,0.4,0.4);
  Vec3 direction(20,10,5);


  //Material
  std::shared_ptr<Material> nothing(new Material(neutro,neutro,neutro, 0));
  std::shared_ptr<Material> MaterialS1(new Material(specular1, difuso1, ambiente1, 5));
  std::shared_ptr<Material> MaterialS1_esp(new Material(specular1, neutro, ambiente1, 5));
  std::shared_ptr<Material> MaterialS1_dif(new Material(neutro, difuso1, ambiente1, 5));
  std::shared_ptr<Material> MaterialS2_4(new Material(specular2, difuso2, ambiente1, 4));
  std::shared_ptr<Material> MaterialS2_16(new Material(specular2, difuso2, ambiente1, 16));
  std::shared_ptr<Material> MaterialS2_32(new Material(specular2, difuso2, ambiente1, 32));
  std::shared_ptr<Material> MaterialS2_64(new Material(specular2, difuso2, ambiente1, 64));
  std::shared_ptr<Material> MaterialS2_64_esp(new Material(specular2, neutro, ambiente1, 64));
  std::shared_ptr<Material> MaterialS2_64_dif(new Material(neutro, difuso2, ambiente1, 64));

  //Shader
  Shader* s;
  //s = new Normal2RGB();
  //s = new Depth(0,4,Color3(0,0,0),Color3(1,1,1));
  //s = new LambertianShader();

  //Camera
  Camera* c = new Camera(Point3(-2.0, -1.0, -1.0), Vec3(0,2,0), Vec3(4,0,0), Point3(0,0,0));

 //Diffuse Shader
  s = new DiffuseShader();
  Scene scene(&bg);
  scene.addObject(new Sphere(Point3(0,-100.5,-1), 100.f, MaterialS1));
  scene.addObject(new Sphere(Point3(0,0,-1), 0.4, MaterialS1));
  Raytracer r(c, scene, s, nb_sample );
  Image img = r.render("img "+time_file, n_col, n_row);
  if (properties[CODIFICATION] == "binary"){ img.create_by_binary(); }
  else if (properties[CODIFICATION] == "ascii") { img.create_by_ascii();}
  else{std::cerr << "Codification not accepted (yet)" << std::endl;}
  
  /*====================== Exercise 4 -- blinn phong
  s = new BlinnPhongShader();
  // no Light
  Scene scene(&bg);
  scene.addObject(new Sphere(Point3(0,-100.5,-1), 100.f, MaterialS1));
  scene.addObject(new Sphere(Point3(0,0,-1), 0.4, MaterialS1));
  Raytracer r(c, scene, s, nb_sample );
  Image img_0 = r.render("img_0 "+time_file, n_col, n_row);

  // Ambient Light
  scene.setAmbientLight(new AmbientLight(intensidade2));
  r = Raytracer(c, scene, s, nb_sample);
  Image img_1 = r.render("img_1 "+time_file, n_col, n_row);

  DistantLight* l = new DistantLight(Color3(1,1,1), Vec3(20,10,5));

  // difuso only
  Scene scene_dif(&bg);
  scene_dif.addLight(l);
  scene_dif.addObject(new Sphere(Point3(0,-100.5,-1), 100.f, MaterialS1_dif));
  scene_dif.addObject(new Sphere(Point3(0,0,-1), 0.4, MaterialS2_64_dif));
  r = Raytracer(c, scene_dif, s, nb_sample);
  Image img_2 = r.render("img_2 "+time_file, n_col, n_row);

  // especular only
  Scene scene_esp(&bg);
  scene_esp.addLight(l);
  //TO LET BE LIKE TEACHER OUTPUT:
  scene_esp.addObject(new Sphere(Point3(0,-100.5,-1), 100.f, MaterialS1_dif));
  //To match description of the output file:
  //scene_esp.addObject(new Sphere(Point3(0,-100.5,-1), 100.f, MaterialS1_esp));
  scene_esp.addObject(new Sphere(Point3(0,0,-1), 0.4, MaterialS2_64_esp));
  r = Raytracer(c, scene_esp, s, nb_sample);
  Image img_3 = r.render("img_3 "+time_file, n_col, n_row);


  Sphere* sheree = new Sphere(Point3(0,-100.5,-1), 100.f, MaterialS1);

  // especular, difuso
  Scene scene2(&bg);
  scene2.addLight(l);
  scene2.addObject(sheree);
  scene2.addObject(new Sphere(Point3(0,0,-1), 0.4, MaterialS2_64));
  r = Raytracer(c, scene2, s, nb_sample);
  Image img_4 = r.render("img_4 "+time_file, n_col, n_row);
  //with ambient
  scene2.setAmbientLight(new AmbientLight(intensidade2));
  r = Raytracer(c, scene2, s, nb_sample);
  Image img_8 = r.render("img_8 "+time_file, n_col, n_row);

  // especular, difuso, 4
  Scene scene4(&bg);
  scene4.addLight(l);
  scene4.addObject(sheree);
  scene4.addObject(new Sphere(Point3(0,0,-1), 0.4, MaterialS2_4));
  r = Raytracer(c, scene4, s, nb_sample);
  Image img_7 = r.render("img_7 "+time_file, n_col, n_row);

  // especular, difuso, 16
  Scene scene16(&bg);
  scene16.addLight(l);
  scene16.addObject(sheree);
  scene16.addObject(new Sphere(Point3(0,0,-1), 0.4, MaterialS2_16));
  r = Raytracer(c, scene16, s, nb_sample);
  Image img_6 = r.render("img_6 "+time_file, n_col, n_row);

  // especular, difuso, 32
  Scene scene32(&bg);
  scene32.addLight(l);
  scene32.addObject(sheree);
  scene32.addObject(new Sphere(Point3(0,0,-1), 0.4, MaterialS2_32));
   Raytracer rr(c, scene32, s, nb_sample);
  Image img_5 = rr.render("img_5 "+time_file, n_col, n_row);

  //TODO: Treat TYPE/CODIFICATION
  if (properties[CODIFICATION] == "binary"){
    img_0.create_by_binary();
    img_1.create_by_binary();
    img_2.create_by_binary();
    img_3.create_by_binary();
    img_4.create_by_binary();
    img_5.create_by_binary();
    img_6.create_by_binary();
    img_7.create_by_binary();
    img_8.create_by_binary();
  }
  else if (properties[CODIFICATION] == "ascii") {
    img_0.create_by_ascii();
    img_1.create_by_ascii();
    img_2.create_by_ascii();
    img_3.create_by_ascii();
    img_4.create_by_ascii();
    img_5.create_by_ascii();
    img_6.create_by_ascii();
    img_7.create_by_ascii();
    img_8.create_by_ascii();
  } else{
    std::cerr << "Codification not accepted (yet)" << std::endl;
  }*/
}
