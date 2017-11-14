#include "vec3.h"
#include "matrix.h"

using namespace utility;

//
//=== Member function implementation.
//
inline void Vec3::make_unit_vector( void )
{
    /**
     * +---> unit vector.
     * |
     *
     * ^     1
     * v = _____ * v
     *     ||v||
     *
     * ||v|| = sqrt( v dot v )
     *
     *      1
     * k =_____
     *    ||v||
     */
     auto v_dot_v = e[X]*e[X] + e[Y]*e[Y] + e[Z]*e[Z] ;
     // make sure we divide by zero here.
     assert( fabs( v_dot_v - 0.f ) > 0.000001 );
     value_type k = 1.f/ sqrt( v_dot_v );
     e[X] *= k;
     e[Y] *= k;
     e[Z] *= k;
}

//
//=== Non-member function implementation: operator overloading.
//

inline std::istream& operator>>( std::istream& is, Vec3 & v )
{
    is >> v.e[Vec3::field_t::X]
       >> v.e[Vec3::field_t::Y]
       >> v.e[Vec3::field_t::Z];
    return is;
}

inline std::ostream& operator<<( std::ostream& os, const Vec3 & v )
{
    os << "{ "
       << v.e[Vec3::field_t::X]
       << " "
       << v.e[Vec3::field_t::Y]
       << " "
       << v.e[Vec3::field_t::Z]
       << " }";

    return os;
}

inline Vec3 operator+( const Vec3 & v1, const Vec3 & v2 )
{
    return Vec3( v1.e[Vec3::X] + v2.e[Vec3::X],
                 v1.e[Vec3::Y] + v2.e[Vec3::Y],
                 v1.e[Vec3::Z] + v2.e[Vec3::Z] );
}

inline Vec3 operator-( const Vec3 & v1, const Vec3 & v2 )
{
  return Vec3( v1.e[Vec3::X] - v2.e[Vec3::X],
               v1.e[Vec3::Y] - v2.e[Vec3::Y],
               v1.e[Vec3::Z] - v2.e[Vec3::Z] );
}

inline Vec3 operator*( const Vec3 & v1, const Vec3 & v2 )
{
  return Vec3( v1.e[Vec3::X] * v2.e[Vec3::X],
               v1.e[Vec3::Y] * v2.e[Vec3::Y],
               v1.e[Vec3::Z] * v2.e[Vec3::Z] );
}

inline Vec3 operator/( const Vec3 & v1, const Vec3 & v2 )
{
  return Vec3( v1.e[Vec3::X] / v2.e[Vec3::X],
               v1.e[Vec3::Y] / v2.e[Vec3::Y],
               v1.e[Vec3::Z] / v2.e[Vec3::Z] );
}

// Uso: V * 4
inline Vec3 operator*( const Vec3 & v, Vec3::value_type t )
{
    return Vec3( v.e[Vec3::X] * t,
                 v.e[Vec3::Y] * t,
                 v.e[Vec3::Z] * t );
}

// Uso: 4 * V
inline Vec3 operator*( Vec3::value_type t, const Vec3 & v )
{
  return Vec3( t * v.e[Vec3::X],
               t * v.e[Vec3::Y],
               t * v.e[Vec3::Z] );
}

inline Vec3 operator/( const Vec3 & v, Vec3::value_type t )
{
  return Vec3( v.e[Vec3::X] / t,
               v.e[Vec3::Y] / t,
               v.e[Vec3::Z] / t );
}

inline Vec3::value_type dot( const Vec3 & v1, const Vec3 & v2 )
{
  return v1.e[Vec3::X]*v2.e[Vec3::X] +
         v1.e[Vec3::Y]*v2.e[Vec3::Y] +
         v1.e[Vec3::Z]*v2.e[Vec3::Z];
}

inline Vec3 cross( const Vec3 & v1, const Vec3 & v2 )
{
  return Vec3( v1.e[Vec3::Y]* v2.e[Vec3::Z] - v1.e[Vec3::Z]* v2.e[Vec3::Y] ,
               v1.e[Vec3::Z]* v2.e[Vec3::X] - v1.e[Vec3::X]* v2.e[Vec3::Z] ,
               v1.e[Vec3::X]* v2.e[Vec3::Y] - v1.e[Vec3::Y]* v2.e[Vec3::X] );
}

inline Vec3& Vec3::operator+=( const Vec3 & v )
{
    e[X] += v.e[X];
    e[Y] += v.e[Y];
    e[Z] += v.e[Z];

    return *this;
}

inline Vec3& Vec3::operator-=( const Vec3 & v )
{
  e[X] -= v.e[X];
  e[Y] -= v.e[Y];
  e[Z] -= v.e[Z];

  return *this;
}

inline Vec3& Vec3::operator*=( const Vec3 & v )
{
  e[X] *= v.e[X];
  e[Y] *= v.e[Y];
  e[Z] *= v.e[Z];

  return *this;
}

inline Vec3 operator*( const Vec3 & v, const Matrix<utility::Vec3::value_type> mat){
	// Check multiplication condition
	if (mat.cols != 3 || mat.rows  != 3) //TODO: let general(dont restrict rows)
			throw std::logic_error("Matrix with bad dimensions");
	// Multiply
	Vec3 prod( v.e[Vec3::X]*mat.at(0,0) + v.e[Vec3::Y]*mat.at(1,0) + v.e[Vec3::Z]*mat.at(2,0),
             v.e[Vec3::X]*mat.at(0,1) + v.e[Vec3::Y]*mat.at(1,1) + v.e[Vec3::Z]*mat.at(2,1),
             v.e[Vec3::X]*mat.at(0,2) + v.e[Vec3::Y]*mat.at(1,2) + v.e[Vec3::Z]*mat.at(2,2)
	);
	return prod;
}

inline Vec3 mult_mat4( const Vec3 & v, const Matrix<utility::Vec3::value_type> mat){
	// Check multiplication condition
	if (mat.cols != 4 || mat.rows  != 4)
			throw std::logic_error("Matrix with bad dimensions");
  int w = 1; //1 if Point3 and 0 if vec3
	// Multiply
	Vec3 prod( v.e[Vec3::X]*mat.at(0,0) + v.e[Vec3::Y]*mat.at(1,0) + v.e[Vec3::Z]*mat.at(2,0) + w*mat.at(3,0),
             v.e[Vec3::X]*mat.at(0,1) + v.e[Vec3::Y]*mat.at(1,1) + v.e[Vec3::Z]*mat.at(2,1) + w*mat.at(3,1),
             v.e[Vec3::X]*mat.at(0,2) + v.e[Vec3::Y]*mat.at(1,2) + v.e[Vec3::Z]*mat.at(2,2) + w*mat.at(3,2)
	);
	return prod;
}


// Uso: A /= B;
inline Vec3& Vec3::operator/=( const Vec3 & v )
{
  e[X] /= v.e[X];
  e[Y] /= v.e[Y];
  e[Z] /= v.e[Z];

  return *this;
}

// Uso: A *= 3;
inline Vec3& Vec3::operator*=( const value_type t )
{
  e[X] *= t;
  e[Y] *= t;
  e[Z] *= t;

  return *this;
}

// Uso: A /= 3;
inline Vec3& Vec3::operator/=( const value_type t )
{
  assert( fabs( t - 0.f ) > 0.000001 );
  value_type k = 1.f/t;

  e[X] *= k;
  e[Y] *= k;
  e[Z] *= k;

  return *this;
}

// Uso: Vec3 A = unit_vector( B );
inline Vec3 unit_vector( const Vec3 & v )
{
  return v/v.length();
}

//==============================[ Vec3.inl ]==============================//
