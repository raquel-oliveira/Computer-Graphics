#ifndef _VEC3_H_
#define _VEC3_H_

#include <cmath> // fabs
#include <iostream>
#include <cassert> // assert

/*!
 * Represents a 3D vector, that might be used to represent
 * points, directions, vectors, colors, offset
 */
namespace utility {
class Vec3
{
    public:
        //=== Aliases
        typedef float value_type;
        enum field_t : int { X=0, Y=1, Z=2, R=0, G=1, B=2 };

        //=== Members
        value_type e[ 3 ];

        //=== Special members
        Vec3( value_type e0_=0.f, value_type e1_=0.f, value_type e2_=0.f )
            : e{ e0_, e1_, e2_ }
        { /* empty */ }

        //=== Access operators
        inline value_type x() const { return e[X]; }
        inline value_type y() const { return e[Y]; }
        inline value_type z() const { return e[Z]; }
        inline value_type r() const { return e[R]; }
        inline value_type g() const { return e[G]; }
        inline value_type b() const { return e[B]; }

        // indexed access operator (rhs)
        inline value_type operator[]( size_t idx ) const { return e[ idx ]; }
        // indexed access operator (lhs)
        inline value_type& operator[]( size_t idx ) { return e[ idx ]; }

        //=== Algebraic operators

        // Unary '+'
        inline const Vec3& operator+( void ) const { return *this; }
        // Unary '-'
        inline Vec3 operator-( void ) const { return Vec3( -e[X], -e[Y], -e[Z] ); }

        inline Vec3& operator+=( const Vec3& );
        inline Vec3& operator-=( const Vec3& );
        inline Vec3& operator*=( const Vec3& );
        inline Vec3& operator/=( const Vec3& );
        inline Vec3& operator*=( const value_type );
        inline Vec3& operator/=( const value_type );

        inline value_type length( void ) const
        {
            return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
        }
        inline value_type squared_length( void ) const
        {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
        inline void make_unit_vector( void );
};

typedef Vec3 Color3;
typedef Vec3 Offset;
typedef Vec3 Point3;
}

#include "vec3.inl"

#endif
