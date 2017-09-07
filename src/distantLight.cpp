#include "../include/light.h"
#include <sstream>      // std::ostringstream

std::string DistantLight::get_info(std::string tab){
  std::ostringstream info;

  info << tab <<"Light: \n";
  info << tab <<"\t Intensity :" << intensity << "\n";
  info << tab <<"\t Direction :" << direction << "\n";

  return info.str();
}
