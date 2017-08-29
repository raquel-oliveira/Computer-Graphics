#include "../include/render.h"

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
      size_t limiter = content.find_first_of("=");
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

  BackgroundSky bg(c_ul, c_ll);


  //TODO: Treat TYPE/CODIFICATION
  bool is_binary = false;
  if (properties[CODIFICATION] == "binary"){
    is_binary = true;
  }
  else if (properties[CODIFICATION] == "ascii") {
    is_binary = false;
  } else{
    std::cerr << "Codification not accepted (yet)" << std::endl;
  }

  Image image(properties[NAME], n_col, n_row);
  Camera* c = new Camera(Point3(-2.0, -1.0, -1.0), Vec3(0,2,0), Vec3(4,0,0), Point3(0,0,0));
  int nb_sample(80);

  Scene scene(&bg);
  scene.addObject(new Sphere(Point3(0,-100.5,-3), 99.f));
  scene.addObject(new Sphere(Point3(0.3,0,-1), 0.4));
  scene.addObject(new Sphere(Point3(0,1,-2), 0.6));
  scene.addObject(new Sphere(Point3(-0.4,0,-3), 0.7));

  std::random_device rd;
  std::mt19937 gen(rd());

  for(int i = 0; i < n_row; i++){
    for(int j = 0; j < n_col; j++){
      Color3 col(0,0,0);
      for(int k = 0; k < nb_sample; k++){
        float u = (j+std::generate_canonical<double, 10>(gen))/ n_col;
        float v =  1 - (i+std::generate_canonical<double, 10>(gen))/ n_row;
        Ray r(c->origin(), c->llc()+(u*c->horizontal())+(v*c->vertical()));
        col+= find_color(scene, r);
      }
      col = col/nb_sample;
      image(i, j) = col;
    }
  }

  if (is_binary){
    image.create_by_binary();
  } else { //is ascii
    image.create_by_ascii();
  }
}
