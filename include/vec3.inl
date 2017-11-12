#include "vec3.h"

using namespace utility;

//
//=== Member function implementation.
//
template<typename TField>
inline void Vec3<TField>::make_unit_vector( void )
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
     TField k = 1.f/ sqrt( v_dot_v );
     e[X] *= k;
     e[Y] *= k;
     e[Z] *= k;
}

//
//=== Non-member function implementation: operator overloading.
//

template<typename TField>
inline std::istream& operator>>( std::istream& is, Vec3<TField> & v )
{
    is >> v.e[Vec3<TField>::field_t::X]
       >> v.e[Vec3<TField>::field_t::Y]
       >> v.e[Vec3<TField>::field_t::Z];
    return is;
}

template<typename TField>
inline std::ostream& operator<<( std::ostream& os, const Vec3<TField> & v )
{
    os << "{ "
       << v.e[Vec3<TField>::field_t::X]
       << " "
       << v.e[Vec3<TField>::field_t::Y]
       << " "
       << v.e[Vec3<TField>::field_t::Z]
       << " }";

    return os;
}

template<typename TField>
inline Vec3<TField> operator+( const Vec3<TField> & v1, const Vec3<TField> & v2 )
{
    return Vec3<TField>( v1.e[Vec3<TField>::X] + v2.e[Vec3<TField>::X],
                         v1.e[Vec3<TField>::Y] + v2.e[Vec3<TField>::Y],
                         v1.e[Vec3<TField>::Z] + v2.e[Vec3<TField>::Z] );
}

template<typename TField>
inline Vec3<TField> operator-( const Vec3<TField> & v1, const Vec3<TField> & v2 )
{
  return Vec3<TField>( v1.e[Vec3<TField>::X] - v2.e[Vec3<TField>::X],
                       v1.e[Vec3<TField>::Y] - v2.e[Vec3<TField>::Y],
                       v1.e[Vec3<TField>::Z] - v2.e[Vec3<TField>::Z] );
}

template<typename TField>
inline Vec3<TField> operator*( const Vec3<TField> & v1, const Vec3<TField> & v2 )
{
  return Vec3<TField>( v1.e[Vec3<TField>::X] * v2.e[Vec3<TField>::X],
                       v1.e[Vec3<TField>::Y] * v2.e[Vec3<TField>::Y],
                       v1.e[Vec3<TField>::Z] * v2.e[Vec3<TField>::Z] );
}

template<typename TField>
inline Vec3<TField> operator/( const Vec3<TField> & v1, const Vec3<TField> & v2 )
{
  return Vec3<TField>( v1.e[Vec3<TField>::X] / v2.e[Vec3<TField>::X],
                       v1.e[Vec3<TField>::Y] / v2.e[Vec3<TField>::Y],
                       v1.e[Vec3<TField>::Z] / v2.e[Vec3<TField>::Z] );
}

// Uso: V * 4
template<typename TField>
inline Vec3<TField> operator*( const Vec3<TField> & v, TField t )
{
    return Vec3<TField>( v.e[Vec3<TField>::X] * t,
                         v.e[Vec3<TField>::Y] * t,
                         v.e[Vec3<TField>::Z] * t );
}

// Uso: 4 * V
template<typename TField>
inline Vec3<TField> operator*( TField t, const Vec3<TField> & v )
{
  return Vec3<TField>( t * v.e[Vec3<TField>::X],
                       t * v.e[Vec3<TField>::Y],
                       t * v.e[Vec3<TField>::Z] );
}

template<typename TField>
inline Vec3<TField> operator/( const Vec3<TField> & v, TField t )
{
  return Vec3<TField>( v.e[Vec3<TField>::X] / t,
                       v.e[Vec3<TField>::Y] / t,
                       v.e[Vec3<TField>::Z] / t );
}

template<typename TField>
inline TField dot( const Vec3<TField> & v1, const Vec3<TField> & v2 )
{
  return v1.e[Vec3<TField>::X]*v2.e[Vec3<TField>::X] +
         v1.e[Vec3<TField>::Y]*v2.e[Vec3<TField>::Y] +
         v1.e[Vec3<TField>::Z]*v2.e[Vec3<TField>::Z];
}

template<typename TField>
inline Vec3<TField> cross( const Vec3<TField> & v1, const Vec3<TField> & v2 )
{
  return Vec3<TField>( v1.e[Vec3<TField>::Y]* v2.e[Vec3<TField>::Z] - v1.e[Vec3<TField>::Z]* v2.e[Vec3<TField>::Y] ,
                       v1.e[Vec3<TField>::Z]* v2.e[Vec3<TField>::X] - v1.e[Vec3<TField>::X]* v2.e[Vec3<TField>::Z] ,
                       v1.e[Vec3<TField>::X]* v2.e[Vec3<TField>::Y] - v1.e[Vec3<TField>::Y]* v2.e[Vec3<TField>::X] );
}

template<typename TField>
inline Vec3<TField>& Vec3<TField>::operator+=( const Vec3<TField> & v )
{
    e[X] += v.e[X];
    e[Y] += v.e[Y];
    e[Z] += v.e[Z];

    return *this;
}

template<typename TField>
inline Vec3<TField>& Vec3<TField>::operator-=( const Vec3<TField> & v )
{
  e[X] -= v.e[X];
  e[Y] -= v.e[Y];
  e[Z] -= v.e[Z];

  return *this;
}

template<typename TField>
inline Vec3<TField>& Vec3<TField>::operator*=( const Vec3<TField> & v )
{
  e[X] *= v.e[X];
  e[Y] *= v.e[Y];
  e[Z] *= v.e[Z];

  return *this;
}

// Uso: A /= B;
template<typename TField>
inline Vec3<TField>& Vec3<TField>::operator/=( const Vec3<TField> & v )
{
  e[X] /= v.e[X];
  e[Y] /= v.e[Y];
  e[Z] /= v.e[Z];

  return *this;
}

// Uso: A *= 3;
template<typename TField>
inline Vec3<TField>& Vec3<TField>::operator*=( const TField t )
{
  e[X] *= t;
  e[Y] *= t;
  e[Z] *= t;

  return *this;
}

// Uso: A /= 3;
template<typename TField>
inline Vec3<TField>& Vec3<TField>::operator/=( const TField t )
{
  assert( fabs( t - 0.f ) > 0.000001 );
  TField k = 1.f/t;

  e[X] *= k;
  e[Y] *= k;
  e[Z] *= k;

  return *this;
}

// Uso: Vec3 A = unit_vector( B );
template<typename TField>
inline Vec3<TField> unit_vector( const Vec3<TField> & v )
{
  return v/v.length();
}

//==============================[ Vec3.inl ]==============================//
