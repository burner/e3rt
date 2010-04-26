///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2009 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-17
// Updated : 2008-08-17
// Licence : This source is under MIT License
// File    : glm/core/type_half.h
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_half
#define glm_core_type_half

#include <cstdlib>

namespace glm
{
	namespace detail
	{
		typedef short hdata;

		float toFloat32(hdata value);
		hdata toFloat16(float value);

		class thalf
		{
		public: 
			// Constructors
			thalf();
			thalf(thalf const & s);
			
			template <typename U>
			thalf(U const & s);

			// Cast
			//operator float();
			operator float() const;
			//operator double();
			//operator double() const;

			// Unary updatable operators
			thalf& operator= (thalf s);
			thalf& operator+=(thalf s);
			thalf& operator-=(thalf s);
			thalf& operator*=(thalf s);
			thalf& operator/=(thalf s);
			thalf& operator++();
			thalf& operator--();
	
			float toFloat() const{return toFloat32(data);}

			hdata _data() const{return data;}

		private:
			hdata data;
		};

		void test_half_type();
	}//namespace detail

	detail::thalf operator- (detail::thalf s1, detail::thalf s2);

	detail::thalf operator* (detail::thalf s1, detail::thalf s2);

	detail::thalf operator/ (detail::thalf s1, detail::thalf s2);

	// Unary constant operators
	detail::thalf operator- (detail::thalf s);

	detail::thalf operator-- (detail::thalf s, int);

	detail::thalf operator++ (detail::thalf s, int);

}//namespace glm

glm::detail::thalf operator+ (glm::detail::thalf s1, glm::detail::thalf s2);

#include "type_half.inl"

#endif//glm_core_type_half
