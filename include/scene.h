#ifndef _SCENE_H_
#define _SCENE_H_

#include "object.h"
#include <vector>

struct background {
  Color3 upper_left;
  Color3 upper_right;
  Color3 lower_left;
  Color3 lower_right;

  background(Color3 ul,Color3 ur,Color3 ll,Color3 lr) :
    upper_left(ul),
    upper_right(ur),
    lower_left(ll),
    lower_right(lr) {}

  background(){}
};

class Scene{

    private:
      std::vector<Object*> objects;
      background bg;

    public:
      Scene() :
        bg(Color3(0,0,0), Color3(0,0,0), Color3(0,0,0), Color3(0,0,0)){
      }

      Scene(background bg) : bg(bg) {}

      void addObject(Object* o){
        objects.push_back(o);
      }

      //TODO:: Change this
      inline std::vector<Object*>* getObjects() {return &objects;}

      inline Color3 bgUpperLeft() { return bg.upper_left;}
      inline Color3 bgUpperRight() { return bg.upper_right;}
      inline Color3 bgLowerLeft() { return bg.lower_left;}
      inline Color3 bgLowerRight() { return bg.lower_right;}


};

#endif
