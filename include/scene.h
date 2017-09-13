#ifndef _SCENE_H_
#define _SCENE_H_

#include "object.h"
#include "background.h"
#include <vector>
#include <sstream>      // std::ostringstream
#include "light.h"

class Scene{

    private:
      std::vector<Object*> objects;
      Background* bg;
      std::vector<Light*> lights;
      AmbientLight* ambient;

    public:
      Scene() :
        bg(new BackgroundSky(Color3(0,0,0), Color3(0,0,0))),
        ambient(new AmbientLight(Color3(0.4,0.4,0.4))){}

      Scene(Background* bg) : bg(bg), ambient(new AmbientLight(Color3(0,0,0))) {}

      Scene(Background* bg, AmbientLight* al) : bg(bg), ambient(al) {}

      void addObject(Object* o){
        objects.push_back(o);
      }

      void addLight(Light* t){
        lights.push_back(t);
      }

      inline Background* getBg(){ return bg;}

      inline std::vector<Object*>* getObjects() {return &objects;}

      inline std::vector<Light*> getLights() {return lights;}

      inline AmbientLight* getAmbientLight() {return ambient;}

      inline void setAmbientLight(AmbientLight* al){this->ambient = al;}

      inline std::string get_info(std::string tab) {
        std::ostringstream info;
        info << tab << "Background :\n";
        info << tab << "\tColor upperLeft :" << bg->upperLeft() << "\n";
        info << tab << "\tColor upperRight :" << bg->upperRight() << "\n";
        info << tab << "\tColor lowerLeft :" << bg->lowerLeft() << "\n";
        info << tab << "\tColor lowerRight :" << bg->lowerRight() << "\n";
        info << tab << "Objects :\n";
        for(const auto i : objects){
          info << i->get_info(tab+"\t");
        }
        for(const auto i : lights){
          info << i->get_info(tab+"\t");
        }
        return info.str();
      }

};

#endif
