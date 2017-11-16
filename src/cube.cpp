#include "cube.h"
#include "triangule.h"
#include <vector>
#include <sstream>      // std::ostringstream


bool Cube::hit(const Ray &r_, float t_min, float t_max, Hit& hit) const{
  bool bfc = true;
  //Vertices
  Point3 llc(upperLeftCorner-Vec3(0,edge, 0));
  Point3 urc(upperLeftCorner+Vec3(edge,0,0));
  Point3 lrc(urc-Vec3(0,edge,0));
  Point3 ulb(upperLeftCorner-Vec3(0,0,edge));
  Point3 llb(llc-Vec3(0,0,edge));
  Point3 lrb(lrc-Vec3(0,0,edge));
  Point3 urb(urc-Vec3(0,0,edge));
  //Triangules
  std::vector<Triangule*> faces;
  faces.push_back(new Triangule(llc, urc, upperLeftCorner, bfc, this->material)); //1
  faces.push_back(new Triangule(lrc, urc, llc, bfc, this->material)); //2
  faces.push_back(new Triangule(lrc, urb, urc, bfc, this->material)); //3
  faces.push_back(new Triangule(lrc, lrb, urb, bfc, this->material)); //4
  faces.push_back(new Triangule(lrb, ulb, urb, bfc, this->material)); //5
  faces.push_back(new Triangule(llb, llc, upperLeftCorner, bfc, this->material)); //8
  faces.push_back(new Triangule(ulb, llb, upperLeftCorner, bfc, this->material)); //9
  faces.push_back(new Triangule(llb, ulb, lrb, bfc, this->material)); //10
  faces.push_back(new Triangule(ulb, upperLeftCorner, urb, bfc, this->material)); //11;
  faces.push_back(new Triangule(urb, upperLeftCorner, urc, bfc, this->material)); //12
  faces.push_back(new Triangule(llb, lrc, llc, bfc, this->material)); //13
  faces.push_back(new Triangule(llb, lrb, lrc, bfc, this->material)); //14
  for(const auto &f : faces){
    if (f->hit(r_, t_min, t_max, hit)){
      return true;
    }
  }
  return false;
}

void Cube::transform(Matrix<float> matrix_){

}

std::string Cube::get_info(std::string tab){
  std::ostringstream info;
  info << tab << "Cube: \n";
  info << tab << "\t Upper left corner: " << upperLeftCorner << "\n";
  info << tab << "\t Edges size: " << edge << "\n";
  info << material->get_info(tab+"\t") << "\n";

  return info.str();
}
