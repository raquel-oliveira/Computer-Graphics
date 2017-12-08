#ifndef _UTIL_H_
#define _UTIL_H_

#define TMIN 0.001
#define TMAX 100000000000000
#define DIM 2 //perlin
#include "vec3.h"
#include "object.h" // hit
#include <vector>
#include "background.h"

class Background;

Color3 interp(Color3 p_0, Color3 p_1, float x);

Color3 bi_interp(Background* bg, int i, int j, int n_col, int n_row);

Point3 random_point_sphere();

/****perfect reflection***/
Vec3 reflect(const Vec3& v, const Vec3& n);

//float trilinear_interp(float c[DIM][DIM][DIM], float u, float v, float w);

float perlin_interp(Vec3 c[DIM][DIM][DIM], float u, float v, float w);

//float *perlin_generate();

Vec3* perlin_generate();

void permute(int *p, int n);

int* perlin_generate_perm();

#endif
