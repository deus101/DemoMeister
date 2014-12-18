#ifndef VEC_HPP
#define VEC_HPP

#include <glload/gl_3_3.hpp>
#include <glload/gl_load.hpp>


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
/*
	class VEC4
	{
	public:
		GLfloat X;
		GLfloat Y;
		GLfloat Z;
		GLfloat A;

	public:
		VEC4(){}
		VEC4(float x, float y, float z, float a);


	};
*/
		
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