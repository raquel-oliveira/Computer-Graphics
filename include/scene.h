#ifndef _SCENE_H_
#define _SCENE_H_

#include "object.h"
#include "background.h"
#include <vector>

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

      //TODO:: Change this
      inline std::vector<Object*>* getObjects() {return &objects;}


};

#endif
