#include "../include/light.h"
#include <sstream>      // std::ostringstream

std::string PontualLight::get_info(std::string tab){
  std::ostringstream info;

  info << tab <<"Pontual Light: \n";
  info << tab <<"\t Intensity :" << intensity << "\n";
  info << tab <<"\t Origin :" << origin << "\n";

  return info.str();
}
