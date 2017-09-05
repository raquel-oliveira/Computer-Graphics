#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "camera.h"
#include "scene.h"
#include "shader.h"
#include "image.h"
#include <string>

class Raytracer {
  private:
    Camera* camera;
    Scene scene;
    Shader* shader;
    int nb_samples;

    void get_description(std::string name);

  public:
    Raytracer(Camera* c, Scene s, Shader* sh, int i) :
      camera(c), scene(s), shader(sh) {
        nb_samples = (i < 1) ? 1 : i;
      }

    Image render (std::string name, int n_col, int n_row);

};
#endif
