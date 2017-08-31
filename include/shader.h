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
#endif
