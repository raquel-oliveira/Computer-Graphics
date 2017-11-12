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
template<typename TField>
class Vec3
{
    public:
        //=== Aliases
        enum field_t : int { X=0, Y=1, Z=2, R=0, G=1, B=2 };

        //=== Members
        TField e[ 3 ];

        //=== Special members
        Vec3( TField e0_=0.f, TField e1_=0.f, TField e2_=0.f )
            : e{ e0_, e1_, e2_ }
        { /* empty */ }

        //=== Access operators
        inline TField x() const { return e[X]; }
        inline TField y() const { return e[Y]; }
        inline TField z() const { return e[Z]; }
        inline TField r() const { return e[R]; }
        inline TField g() const { return e[G]; }
        inline TField b() const { return e[B]; }

        // indexed access operator (rhs)
        inline TField operator[]( size_t idx ) const { return e[ idx ]; }
        // indexed access operator (lhs)
        inline TField& operator[]( size_t idx ) { return e[ idx ]; }

        //=== Algebraic operators

        // Unary '+'
        inline const Vec3& operator+( void ) const { return *this; }
        // Unary '-'
        inline Vec3 operator-( void ) const { return Vec3( -e[X], -e[Y], -e[Z] ); }

        inline Vec3& operator+=( const Vec3& );
        inline Vec3& operator-=( const Vec3& );
        inline Vec3& operator*=( const Vec3& );
        inline Vec3& operator/=( const Vec3& );
        inline Vec3& operator*=( const TField );
        inline Vec3& operator/=( const TField );

        inline TField length( void ) const
        {
            return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
        }
        inline TField squared_length( void ) const
        {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
        inline void make_unit_vector( void );
};

template<typename TField> using Color3 = Vec3<TField>;
template<typename TField> using Offset = Vec3<TField>;
template<typename TField> using Point3 = Vec3<TField>;
}

#include "vec3.inl"

#endif
