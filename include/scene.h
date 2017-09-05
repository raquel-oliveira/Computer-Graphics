#ifndef _SCENE_H_
#define _SCENE_H_

#include "object.h"
#include "background.h"
#include <vector>
#include <sstream>      // std::ostringstream


class Scene{

    private:
      std::vector<Object*> objects;
      Background* bg;

    public:
      Scene() :
        bg(new BackgroundSky(Color3(0,0,0), Color3(0,0,0))){
      }

      Scene(Background* bg) : bg(bg) {}

      void addObject(Object* o){
        objects.push_back(o);
      }

      inline Background* getBg(){ return bg;}

      inline std::vector<Object*>* getObjects() {return &objects;}

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
        return info.str();
      }

};

#endif
