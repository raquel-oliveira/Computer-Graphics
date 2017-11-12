#include "transform.h"

Matrix<float> toTranslate(utility::Vec3 distance) {
  Matrix<float> m {4};
  m.set(0,3, distance.x());
  m.set(1,3, distance.y());
  m.set(2,3, distance.z());
  return m;
}
