#include "../include/render.h"

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

  Image image(properties[NAME], n_col, n_row);
  Camera* c = new Camera(Point3(-2.0, -1.0, -1.0), Vec3(0,2,0), Vec3(4,0,0), Point3(0,0,0));
  BackgroundSky bg(c_ul, c_ll);
  Scene scene(&bg);
  scene.addObject(new Sphere(Point3(0,-100.5,-3), 99.f));
  scene.addObject(new Sphere(Point3(0.3,0,-1), 0.4));
  scene.addObject(new Sphere(Point3(0,1,-2), 0.6));
  scene.addObject(new Sphere(Point3(-0.4,0,-3), 0.7));
  //Shader* s = new Normal2RGB();
  Shader* s = new Depth();

  std::random_device rd;
  std::mt19937 gen(rd());

  for(int i = 0; i < n_row; i++){
    for(int j = 0; j < n_col; j++){
      Color3 col(0,0,0);
      for(int k = 0; k < nb_sample; k++){
        float u = (j+std::generate_canonical<double, 10>(gen))/ n_col;
        float v =  1 - (i+std::generate_canonical<double, 10>(gen))/ n_row;
        Ray r(c->origin(), c->llc()+(u*c->horizontal())+(v*c->vertical()));
        col+= s->find_color(scene, r);
      }
      col = col/nb_sample;
      image(i, j) = col;
    }
  }

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
