#include "raytracer.h"
#include <iostream>
#include <string> // stoi (string to int)
#include <map>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "triangule.h"
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
#include "matrix.h"
#include "transform.h"
#include "cube.h"
#include "perlin_texture.h"

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
                                                    {UPPER_LEFT, "0.68 0.81 0.96"},
                                                    {UPPER_RIGHT, "0.68 0.81 0.96"},
                                                    {LOWER_LEFT, "0.68 0.81 0.96"},
                                                    {LOWER_RIGHT, "0.68 0.81 0.96"},
                                                    {SAMPLE, "12"}
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
  Color3 difuso3(0.7,0.2,0.1);
  Color3 difuso4(0.8,0.8,0.8);
  Color3 difuso5(0.9,0.2,0.1);
  Color3 difuso6(0.2,0.9,0.2);
  Color3 difuso7(0.1,0.2,0.9);
  Color3 difuso8(0.7,0.7,0.1);
  Color3 lb_col(0.8,0.3,0.3);
  Color3 lb_col2(0.8,0.8,0.0);
  Color3 met_col(0.8,0.6,0.2);
  Color3 specular1(1,1,1);
  Color3 specular2(0.9,0.9,0.9);
  Color3 specular3(0.8,0.8,0.8);
  Color3 specular4(0.8,0.8,0.6);
  //Luzes
  Color3 intensidade1(1,1,1);
  Color3 intensidade2(0.4,0.4,0.4);
  Color3 intensidade3(0.5,0.5,0.5);
  Color3 intensidade4(0.8,0.8,0.8);
  Color3 intensidade5(0.2,0.2,0.2);
  Color3 intensidade6(0.3,0.9,0.3);
  Color3 intensidade7(0.7,0.2,0.2);
  Color3 intensidade8(0.2,0.2,0.7);
  Vec3 direction(20,10,15);
  Vec3 direction2(-8,7,0);
  Vec3 direction3(-3,20,0);
  Vec3 direction4(0.5,0,-0.6);

  Texture* grayTexture = new Constant_texture(Color3(0.5,0.5,0.5));
  Texture* purpleTexture = new Constant_texture(Color3(0.66,0.44,0.87));
  Texture* grayPurpleTexture = new Checker_texture(grayTexture, purpleTexture);
  Texture* blackNoise = new Perlin_texture(1.3);


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
  std::shared_ptr<Material> Material_extra(new Material(specular1, difuso3, ambiente1, 64));
  std::shared_ptr<Material> Material_extra2(new Material(neutro, difuso4, ambiente1, 64));
  std::shared_ptr<Material> lb1(new LambertianMaterial(lb_col, blackNoise));
  std::shared_ptr<Material> lb2(new LambertianMaterial(lb_col2, purpleTexture));
  std::shared_ptr<Material> lb3(new LambertianMaterial(lb_col2, grayPurpleTexture));
  std::shared_ptr<Material> met1(new MetalMaterial(met_col));
  std::shared_ptr<Material> met2(new MetalMaterial(difuso4));
  std::shared_ptr<Material> floor_mat(new Material(neutro, difuso4, ambiente1, 64));
  std::shared_ptr<Material> redish(new Material(specular3, difuso5, ambiente1, 256));
  std::shared_ptr<Material> greenish(new Material(specular3, difuso6, ambiente1, 256));
  std::shared_ptr<Material> blueish(new Material(specular4, difuso7, ambiente1, 256));
  std::shared_ptr<Material> gnd(new Material(neutro, difuso4, ambiente1, 8));
  std::shared_ptr<Material> tri(new Material(specular3, difuso8, ambiente1, 256));
  std::shared_ptr<Material> dia(new DielectricMaterial(1.5));


  std::vector<Color3> colors; //red gradient
  colors.push_back(Color3(0.10,0,0));
  colors.push_back(Color3(0.25,0,0));
  colors.push_back(Color3(0.5,0,0));
  colors.push_back(Color3(0.75,0,0));
  colors.push_back(Color3(1,0,0));
  std::shared_ptr<Material> toon1(new ToonMaterial(colors));

  std::vector<Color3> colors2; //green gradient
  colors2.push_back(Color3(0,0.10,0));
  colors2.push_back(Color3(0,0.25,0));
  colors2.push_back(Color3(0,0.5,0));
  colors2.push_back(Color3(0,0.75,0));
  colors2.push_back(Color3(0,1,0));
  std::shared_ptr<Material> toon2(new ToonMaterial(colors2));

  std::vector<Color3> colors3; //blue gradient
  colors3.push_back(Color3(0,0, 0.10));
  colors3.push_back(Color3(0,0, 0.25));
  colors3.push_back(Color3(0,0, 0.5));
  colors3.push_back(Color3(0,0, 0.75));
  colors3.push_back(Color3(0,0,1));
  std::shared_ptr<Material> toon3(new ToonMaterial(colors3));

  std::vector<Color3> colors4; //yellow gradient
  colors4.push_back(Color3(0.1,0.1, 0));
  colors4.push_back(Color3(0.25,0.25, 0));
  colors4.push_back(Color3(0.5,0.5,0));
  colors4.push_back(Color3(0.75,0.75,0));
  colors4.push_back(Color3(1,1,0));
  std::shared_ptr<Material> toon4(new ToonMaterial(colors4));

  //Shader
  Shader* s;
  //s = new Normal2RGB();
  //s = new Depth(0,4,Color3(0,0,0),Color3(1,1,1));
  //s = new LambertianShader();
  s = new RecursiveShader(100);
  //s = new ToonShader();
  // s = new BlinnPhongShader();

  //Camera
  //Camera* c = new Camera(Point3(-2.0, -1.0, -1.0), Vec3(0,2,0), Vec3(4,0,0), Point3(0,0,0));
  Point3 lookf = Point3(9, 3.5, 2);
  Point3 lookat = Point3(0,0,-1);
  Vec3 vup = Vec3(0,1,0);
  float vfov = 20;
  float asp = 2.3;
  Camera* c = new Camera(lookf, lookat, vup, vfov, asp);
  Scene scene(&bg);
  //scene.setAmbientLight(new AmbientLight(intensidade2));
  //scene.addLight(new DistantLight(intensidade4, direction2));
  //scene.addLight(new PontualLight(intensidade3, Point3(1.5,4,-0.9)));
  scene.addLight(new SpotLight(intensidade6, Point3(0,1,2), Point3(0,0,-2), 15));
  scene.addLight(new SpotLight(intensidade7, Point3(0,4,-2), Point3(-4,0,-2), 18));
  scene.addLight(new SpotLight(intensidade8, Point3(0,4,-2), Point3(4,0,-2), 18));
  //scene.addLight(new DistantLight(Color3(0.25,0.1,0.1), Vec3(0, 0.5, 1)));
  //scene.addObject(new Sphere(Point3(0,0,-2), 0.5, greenish));
  //scene.addObject(new Sphere(Point3(-4,0,-2), 0.5, redish));
  //scene.addObject(new Sphere(Point3(4,0,-2), 0.5, blueish));
  scene.addObject(new Sphere(Point3(0,-1000.5,-1), 1000.0, lb3));
  //scene.addObject(new Sphere(Point3(0,0,-1), 0.5, lb1));
  //scene.addObject(new Sphere(Point3(1,0,-1), 0.5, met1));
  //scene.addObject(new Sphere(Point3(0,0,-1), 0.5, dia));
  //scene.addObject(new Sphere(Point3(0,0,-1), -0.48, dia));
  scene.addObject(new Sphere(Point3(0,0,-2), 0.5, lb1));


  //scene.addObject(new Sphere(Point3(0,0,-1), 0.5, Material_extra));
  //scene.addObject(new Sphere(Point3(-1,0,-1), 0.5, toon3)); //lado esquerdo
  //scene.addObject(new Sphere(Point3(0,-100.5,-1), 100.f, MaterialS1)); //big one

  //scene.addObject(new Sphere(Point3(0,0,-1), 0.5, MaterialS1)); //center
  //scene.addObject(new Sphere(Point3(1,0,-1), 0.5, met1)); //lado direto
  //scene.addObject(new Cube(Point3(0,3,-1), 1, met1));
  //scene.addObject(new Sphere(Point3(0,-100.5,-1), 100.f, floor_mat));
  //scene.addObject(new Sphere(Point3(1,0,-1), 0.5, met1));
  //scene.addObject(new Sphere(Point3(-1,0,-1), 0.5, met2));
  //scene.addObject(new Sphere(direction4, 0.1, MaterialS1));
  //Object* t = new Triangule(Point3(0,-1,-1),Point3(0, 0, -1),Point3(-1,0,-1),false, MaterialS1);
  //scene.addObject(t);
  //scene.addObject(new Triangule(Point3(0,1,-1),Point3(1, 2, -1),Point3(0,2,-1),true, MaterialS1));

  Raytracer r(c, scene, s, nb_sample );
  Image img = r.render("img1 "+time_file, n_col, n_row);
  if (properties[CODIFICATION] == "binary"){ img.create_by_binary(); }
  else if (properties[CODIFICATION] == "ascii") { img.create_by_ascii();}
  else{std::cerr << "Codification not accepted (yet)" << std::endl;}

}
