#ifndef VEC_INLINE_HPP
#define VEC_INLINE_HPP

//#define M_PI 3.14159265358979323846
#define M_PI 3.14159265

#include <math.h>

namespace NS_VEC
{
	inline VEC4::VEC4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w){}

	inline VEC3::VEC3(float x, float y, float z) : X(x), Y(y), Z(z){}

	inline VEC2::VEC2(float x, float y ) :  X(x), Y(y){}

	//just convert to radians be fore putting in the arguments
	inline QUAT::QUAT(float w, float x, float y, float z) {
		//nevermind did it here
		w = w / 360 * (float)M_PI * 2;

		W = cos(w/2);
		X = x*sin(w/2);
		Y = y*sin(w/2);
		Z = z*sin(w/2);

	}

	inline const QUAT QUAT::Inverse(void) const
	{
		QUAT q;

		q.W = W;
		q.X = -X;
		q.Y = -Y;
		q.Z = -Z;
		
		return q;
	}

	inline const QUAT QUAT::operator*(const QUAT& q) const
	{
		QUAT r;

		r.W = W * q.W - (X*q.X + Y*q.Y + Z*q.Z);

		r.X = X * q.W + q.X * W + (Y * q.Z - q.Y * Z);
		r.Y = Y * q.W + q.Y * W + (X * q.Z - q.X * Z);
		r.Z = Z * q.W + q.Z * W + (X * q.Y - q.X * Y);
	

		return r;
	}

	inline const VEC3 QUAT::operator*(const VEC3& v) const
	{
		VEC3 ret;
		VEC3 V(X,Y,Z);
		VEC3 Vcv = cross(V, v);

		ret = v + Vcv*(2 * W) + cross(V, Vcv) * 2;

		/*
		QUAT p;
		p.W = 0;
		p.X = v.X;
		p.Y = v.Y;
		p.Z = v.Z;


		const QUAT& q = (*this);

		ret.X = (q * p * q.Inverse()).X;
		ret.Y = (q * p * q.Inverse()).Y;
		ret.Z = (q * p * q.Inverse()).Z;
		*/


		return ret;

	}
	inline const QUAT QUAT::operator^(float t) const
	{

		//getting a normalized vector and multiply the angle by t
		float a;
		VEC3 n;

		TAA(n, a);

		float at = a*t;
		//returning the transformed/exponatiated QUATERNION
		return QUAT(at, n.X, n.Y, n.Z);

	}

	inline void QUAT::TAA(VEC3& vAxis, float& fAngle) const
	{
		
		VEC3 V(X, Y, Z);

		if (V.CalcLengthSqr() < 0.0001f)
			vAxis = VEC3(1, 0, 0);
		else
			vAxis = (V /= V.CalcLength());
		//No assert so make sure this works

		//fabs(vAxis.CalcLengthSqr() -1) < 0.000001f;

		fAngle = acos(W) * 2;

	
		fAngle *= 360 / ((float)M_PI * 2);

	}

	inline const QUAT QUAT::Slerp(const QUAT& other, float t) const
	{
		const QUAT& q = *this;
		QUAT r = other;
		return ((r * q.Inverse()) ^ t) *q;


	}

	inline const VEC4 VEC4::operator- (void) const
	{// men  skal egentlig skalaren være negativ her?
		return (VEC4(-X, -Y, -Z, -W));

	}

	inline const VEC3 VEC3::operator- (void) const
	{
		return (VEC3 (-X, -Y, -Z));

	}

	inline const VEC2 VEC2::operator- (void) const
	{
		return (VEC2 (-X, -Y));
	}

	inline const VEC4& VEC4::operator+= (const VEC4& cc)
	{
		X += cc.X;
		Y += cc.Y;
		Z += cc.Z;
		W += cc.W;
		return (*this);


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


	inline const VEC4& VEC4::operator-= (const VEC4& cc)
	{
		X -= cc.X;
		Y -= cc.Y;
		Z -= cc.Z;
		W -= cc.W;
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

	inline const VEC4& VEC4::operator*= (float f)
	{
		X *= f;
		Y *= f;
		Z *= f;
		W *= f;

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

	inline const VEC4& VEC4::operator/= (float f)
	{
		const float inverse = 1.0f / f;

		X *= inverse;
		Y *= inverse;
		Z *= inverse;
		W *= inverse;
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

	inline float VEC4::CalcLength(void) const
	{
		return (sqrtf(X * X + Y * Y + Z * Z + W * W));
	}

	inline float VEC3::CalcLengthSqr(void) const
	{
		return (X * X + Y * Y + Z * Z);
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