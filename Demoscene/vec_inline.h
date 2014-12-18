#ifndef VEC_INLINE_HPP
#define VEC_INLINE_HPP

#include <math.h>

namespace NS_VEC
{
	//inline VEC4::VEC4(float x, float y, float z, float a)	

	inline VEC3::VEC3(float x, float y, float z) : X(x), Y(y), Z(z){}

	inline VEC2::VEC2(float x, float y ) :  X(x), Y(y){}


	inline const VEC3 VEC3::operator- (void) const
	{
		return (VEC3 (-X, -Y, -Z));

	}

	inline const VEC2 VEC2::operator- (void) const
	{
		return (VEC2 (-X, -Y));
	}

	inline const VEC3& VEC3::operator+= (const VEC3& cc)
	{
		X += cc.X;
		Y += cc.Y;
		Z += cc.Z;

		return (*this);


	}

	inline const VEC2& VEC2::operator+= (const VEC2& cc)
	{
		X += cc.X;
		Y += cc.Y;

		return (*this);
	
	}

	inline const VEC3& VEC3::operator-= (const VEC3& cc)
	{
		X -= cc.X;
		Y -= cc.Y;
		Z -= cc.Z;

		return (*this);

	}


		inline const VEC2& VEC2::operator-= (const VEC2& cc)
	{
		X -= cc.X;
		Y -= cc.Y;
		

		return (*this);

	}



	inline const VEC3& VEC3::operator*= (float f)
	{

		X *= f;
		Y *= f;
		Z *= f;

		return (*this);


	}


	inline const VEC2& VEC2::operator*= (float f)
	{

		X *= f;
		Y *= f;
	

		return (*this);


	}
	
	inline const VEC3& VEC3::operator/= (float f)
	{
		const float inverse = 1.0f / f;

		X *= inverse;
		Y *= inverse;
		Z *= inverse;

		return (*this);

	}

	inline const VEC2& VEC2::operator/= (float f)
	{
		const float inverse = 1.0f / f;

		X *= inverse;
		Y *= inverse;
		
		return (*this);

	}



	inline void VEC3::NormIt(void) 
	{
		const float inv = 1.0f / CalcLength();

		X *= inv;
		Y *= inv;
		Z *= inv;
	}

	
	inline void VEC2::NormIt(void) 
	{
		const float inv = 1.0f / CalcLength();

		X *= inv;
		Y *= inv;
		
	}




	inline void VEC3::CalcNorm( const VEC3& v1, const VEC3& v2, const VEC3& v3)
	{
		*this = cross((v3 - v2), (v1 - v2));
		NormIt();

	}


	inline const VEC3 operator+ (const VEC3& v1, const VEC3& v2)
	{
		return (VEC3 (v1.X + v2.X, v1.Y + v2.Y, v1.Z + v2.Z));
	}

	inline const VEC3 operator- (const VEC3& v1, const VEC3& v2)
	{
		return (VEC3 (v1.X - v2.X, v1.Y - v2.Y, v1.Z - v2.Z));
	}

	inline const VEC3 operator* (const VEC3& v, float f)
	{
		return (VEC3 (v.X * f, v.Y * f, v.Z * f));
	}

	inline const VEC3 operator* (float f, const VEC3& v)
	{
		return (VEC3 (v.X * f, v.Y * f, v.Z * f));
	}

	inline float VEC3::CalcLength(void) const
	{
		return (sqrtf ( X * X + Y * Y + Z * Z ));
	}

	inline float VEC2::CalcLength(void) const
	{
		return (sqrtf ( X * X + Y * Y ));
	}


	inline const VEC3 cross (const VEC3& v1, const VEC3& v2)
	{
		return( VEC3 (v1.Y * v2.Z - v2.Y * v1.Z,
						-v1.X * v2.Z + v2.X * v1.Z,
						v1.X * v2.Y - v2.X * v1.Y));
	}





}



#pragma once

#endif