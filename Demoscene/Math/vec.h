#ifndef VEC_HPP
#define VEC_HPP


//#include <glload/gl_all.hpp>
//#include <glload/gl_load.hpp>
#include <GL\glew.h>
//husk lerp
//#include "../util.h"

//C:\Program Files(x86)\Windows Kits\8.1\Include\um  why does this contain glload?


namespace NS_VEC
{
	class VEC3
	{
	public:
		GLfloat X;
		GLfloat Y;
		GLfloat Z;
		

	public:
		VEC3(){}
		VEC3(float x, float y, float z);
	
		float CalcLengthSqr(void) const;
		float CalcLength (void) const;
		
		void NormIt (void);
		
	
		const VEC3 operator- (void) const;
		const VEC3& operator+= (const VEC3& cc);
		const VEC3& operator-= (const VEC3& cc);
		const VEC3& operator*= (float f);
		const VEC3& operator/= (float f);

		void CalcNorm( const VEC3& v1, const VEC3& v2, const VEC3& v3);


	};

	class VEC2
	{
	public:
		GLfloat X;
		GLfloat Y;

	public:
		VEC2(){}
		VEC2(float x, float y);

		const VEC2 operator- (void) const;
		const VEC2& operator+= (const VEC2& cc);
		const VEC2& operator-= (const VEC2& cc);
		const VEC2& operator*= (float f);
		const VEC2& operator/= (float f);
		
		
		float CalcLength (void) const;

		
		void NormIt (void);

	};
	//ikke glem homogeniser funksjonen
	class VEC4
	{
	public:
		GLfloat X;
		GLfloat Y;
		GLfloat Z;
		GLfloat W;

	public:
		VEC4(){}
		VEC4(float x, float y, float z, float w);

		const VEC4 operator- (void) const;
		const VEC4& operator+= (const VEC4& cc);
		const VEC4& operator-= (const VEC4& cc);
		const VEC4& operator*= (float f);
		const VEC4& operator/= (float f);

		float CalcLength(void) const;

		void NormIt(void);

	};

	class QUAT
	{
	public:
		GLfloat W;
		GLfloat X;
		GLfloat Y;
		GLfloat Z;

		QUAT(){}
		//QUAT(float w, VEC3 n);
		QUAT(float w, float x, float y, float z);
		QUAT( float x, float y, float z);
		const QUAT Inverse(void) const;
		const VEC3 operator*(const VEC3& v) const;
		const QUAT operator*(const QUAT& q) const;
		const QUAT operator^(float t) const;
		const QUAT Slerp(const QUAT& r, float t) const;


		void TAA(VEC3& vAxis, float& fAngle) const;

		void NormIt();
	};

		
		const VEC3 cross(const VEC3& v1, const VEC3& v2);

		const VEC3 operator+ (const VEC3& v1, const VEC3& v2);
		const VEC3 operator- (const VEC3& v1, const VEC3& v2);
		
		const VEC3 operator* (float f, const VEC3& v);
		const VEC3 operator* (const VEC3& v, float f);

		const VEC3 operator/ (const VEC3& v, const VEC3& v2);

		




	


}


#pragma once
#include "vec_inline.h"

#endif