#ifndef _SHADER_H_
#define _SHADER_H_

Color3 interp(Color3 p_0, Color3 p_1, float x);

class Shader {

  public:
    virtual Color3 find_color(Scene scene,const Ray& r_) const = 0;

};

class Normal2RGB : public Shader{
  public:
    Normal2RGB(){}

    Color3 find_color(Scene scene,const Ray& r_) const{
      Hit hr, hr2; //hitRecords
      int check = -1;
      Vec3 n;
      for (std::vector<Object*>::iterator it = scene.getObjects()->begin() ; it != scene.getObjects()->end(); it++){
        if ((*it)->hit(r_, TMIN, TMAX, hr2)){
          if (check == -1){
            hr = hr2; // initialize t_prev
            n = Vec3((hr.normal.x()+1), (hr.normal.y()+1), (hr.normal.z()+1)) * 0.5; //normal gives a number between -1 and 1, an we want between 0 and 1 (+1/2)
          } else {
            if (hr2.t < hr.t){
              hr = hr2;
              n = Vec3((hr.normal.x()+1), (hr.normal.y()+1), (hr.normal.z()+1)) * 0.5; //normal gives a number between -1 and 1, an we want between 0 and 1 (+1/2)
            }
          }
          check = 0; // hit a object
        }
      }
      if (check == 0){
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
      Hit hr_prev, hr;
      int check = -1;
      float distance=-1;
      for (std::vector<Object*>::iterator it = scene.getObjects()->begin() ; it != scene.getObjects()->end(); it++){
        if ((*it)->hit(r_, TMIN, TMAX, hr_prev)){
          if (check == -1){
            hr = hr_prev; // initialize t_prev
            distance = (hr.point - r_.get_origin()).length();
            distance = std::max(distance, depth_min);
            distance = std::min(distance, depth_max);
          } else {
            if (hr_prev.t < hr.t){
              hr = hr_prev;
              distance = (hr.point - r_.get_origin()).length();
              distance = std::max(distance, depth_min);
              distance = std::min(distance, depth_max);
            }
          }
          check = 0; // hit a object
        }
      }
      if (check == 0){
        float k = (distance-depth_min)/(depth_max-depth_min); //normalize
        Color3 color = interp(foreground_depth, background_depth, k);
        return (255*color);
      }
      return 255*background_depth;
    }
};

#endif
