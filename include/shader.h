#ifndef _SHADER_H_
#define _SHADER_H_


class Shader {

  public:
    virtual Color3 find_color(Scene scene,const Ray& r_) const = 0;

    bool intersect( Scene scene, const Ray &r_, Hit &hr ) const{
      bool check = false;
      Hit hr_prev; //hitRecords
      for(const auto i : *scene.getObjects()){
        if (i->hit(r_, TMIN, TMAX, hr_prev)){
          if (!check){ //First time hit
            hr = hr_prev;
          } else{
            if(hr_prev.t < hr.t){ //Update if hit a closest object
              hr = hr_prev;
            }
          }
          check = true;
        }
      }
    return check;
    }
};

class Normal2RGB : public Shader{
  public:
    Normal2RGB(){}

    Color3 find_color(Scene scene,const Ray& r_) const{
      Hit hr;
      if(intersect(scene, r_, hr)){
        Color3 n = ((hr.normal)+Vec3(1,1,1)) * 0.5; //normal gives a number between -1 and 1, an we want between 0 and 1 (+1/2)
        return (255*n);
      }

      return scene.getBg()->get(r_);
    }
};

class Depth : public Shader{
  private:
    float depth_min;
    float depth_max;
    Color3 background_depth;
    Color3 foreground_depth;

  public:
    Depth():
      depth_min(0), depth_max(4), background_depth(Color3(1,1,1)), foreground_depth(Color3(0,0,0)){}

    Depth(float dmin, float dmax, Color3 cmin, Color3 cmax):
      depth_min(dmin),
      depth_max(dmax),
      background_depth(cmin),
      foreground_depth(cmax) {}

    Color3 find_color(Scene scene,const Ray& r_) const{
      float distance=-1;
      Hit hr;
      if(intersect(scene, r_, hr)){
        distance = (hr.point - r_.get_origin()).length();
        distance = std::max(distance, depth_min);
        distance = std::min(distance, depth_max);

        float k = (distance-depth_min)/(depth_max-depth_min); //normalize
        Color3 color = interp(foreground_depth, background_depth, k);
        return (255*color);
      }

      return 255*background_depth;
    }
};

#endif
