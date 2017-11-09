#include "triangule.h"
#include <sstream>      // std::ostringstream

bool Triangule::hit(const Ray &r_, float t_min, float t_max, Hit& hit) const{
  Vec3 edge1 = v1 - v0;
  Vec3 edge2 = v2 - v0;

  Vec3 tvec = r_.get_origin() - v0;
  Vec3 qvec = cross(tvec, edge1);
  Vec3 pvec = cross(r_.get_direction(), edge2);

  //Determinant (if near 0=> ray lies in plane of triangule)
  float det = dot(edge1, pvec);

  float det_aux = backfaceCulling ? 1 : 1.0/det;
  float det_c = backfaceCulling ? det : 1.0;

  if (backfaceCulling){
      if (det < 0.0001) return 0;
  } else{
    if (det > -0.0001 && det < 0.0001) return 0;
  }

  float u = dot(tvec, pvec) * det_aux;
  if(u < 0.0 || u > det_c) return 0;

  float v = dot(r_.get_direction(), qvec) * det_aux;
  if ((v < 0.0) || ((u + v) > det_c)) return 0;

  float t = dot(edge2, qvec) * det_aux;
  if (t < t_max && t > t_min) {
    hit.t = t;
    hit.point = r_.point_at(hit.t);
    hit.normal = cross(edge1, edge2);
    hit.material = this->material;
    //TODO: u and v only update if backfaceCulling
    return true;
  }
  return false;
}

std::string Triangule::get_info(std::string tab){
  std::ostringstream info;
  info << tab << "Triangule: \n";
  info << tab << "\t Points: " << v0 << " " << v1 << " " << v2 << "\n";
  info << tab << "\t Backface Culling: " << backfaceCulling << "\n";
  info << material->get_info(tab+"\t") << "\n";

  return info.str();
}
