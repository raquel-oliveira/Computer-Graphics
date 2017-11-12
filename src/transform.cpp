#include "transform.h"
#include <math.h>       /* cos sin */
#define PI 3.14159265

Matrix<float> toTranslate(utility::Vec3 distance) {
  Matrix<float> m {4};
  m.set(0,3, distance.x());
  m.set(1,3, distance.y());
  m.set(2,3, distance.z());
  return m;
}

Matrix<float> toScale(utility::Vec3 proportion){
  Matrix<float> m {4};
  m.set(0,0, proportion.x());
  m.set(1,1, proportion.y());
  m.set(2,2, proportion.z());
  return m;
}

Matrix<float> toRotateZ(float rad){
  float value = rad * PI / 180.0;
  Matrix<float> m {4};
  m.set(0,0, cos(value));
  m.set(0,1, -1*sin(value));
  m.set(1,0, sin(value));
  m.set(1,1, cos(value));
  return m;
}


Matrix<float> toRotateX(float rad){
  float value = rad * PI / 180.0;
  Matrix<float> m {4};
  m.set(1,1, cos(value));
  m.set(1,2, -1*sin(value));
  m.set(2,1, sin(value));
  m.set(2,2, cos(value));
  return m;
}


Matrix<float> toRotateY(float rad){
  float value = rad * PI / 180.0;
  Matrix<float> m {4};
  m.set(0,0, cos(value));
  m.set(0,2, sin(value));
  m.set(2,0, -1*sin(value));
  m.set(2,2, cos(value));
  return m;
}
