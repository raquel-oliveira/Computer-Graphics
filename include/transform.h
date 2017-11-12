#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "vec3.h"
#include "matrix.h"

//TODO::use template (update vec3)
//TODO::refactor document.

/**
* Method that gets a distance (from a point) and gives a matrix
* to be use to transform (3D) in order to translate
* an object by update the points.
*
* @return Matrix Matrix to translate
* */

Matrix<float> toTranslate(utility::Vec3 distance);

Matrix<float> toScale(utility::Vec3 proportion);

#endif
