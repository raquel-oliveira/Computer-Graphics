#ifndef _UTIL_H_
#define _UTIL_H_

#define TMIN 0
#define TMAX 100000000000000
#include "vec3.h"
#include "object.h" // hit
#include <vector>
#include "background.h"

class Background;

Color3 interp(Color3 p_0, Color3 p_1, float x);

Color3 bi_interp(Background* bg, int i, int j, int n_col, int n_row);

#endif
