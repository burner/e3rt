///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2009 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-08
// Updated : 2006-11-13
// Licence : This source is under MIT License
// File    : glm/gtx/fast_trigonometry.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_fast_trigonometry
#define glm_gtx_fast_trigonometry

// Dependency:
#include "../glm.hpp"

namespace glm
{
   	namespace test{
		void main_gtx_fast_trigonometry();
	}//namespace test

    namespace gtx{
	//! GLM_GTX_fast_trigonometry extension: Fast but less accurate implementations of trigonometric functions.
    namespace fast_trigonometry
    {
		//! Faster than the common sin function but less accurate. 
		//! Defined between -2pi and 2pi. 
		//! From GLM_GTX_fast_trigonometry extension.
        template <typename T> 
		T fastSin(const T& angle);

        //! Faster than the common cos function but less accurate.
		//! Defined between -2pi and 2pi.
		//! From GLM_GTX_fast_trigonometry extension.
		template <typename T> 
		T fastCos(const T& angle);

        //! Faster than the common tan function but less accurate. 
		//! Defined between -2pi and 2pi. 
		//! From GLM_GTX_fast_trigonometry extension.
		template <typename T> 
		T fastTan(const T& angle);

        //! Faster than the common asin function but less accurate. 
		//! Defined between -2pi and 2pi.
		//! From GLM_GTX_fast_trigonometry extension.
		template <typename T> 
		T fastAsin(const T& angle);

		//! Faster than the common acos function but less accurate. 
		//! Defined between -2pi and 2pi. 
		//! From GLM_GTX_fast_trigonometry extension.
        template <typename T> 
		T fastAcos(const T& angle);

		//! Faster than the common atan function but less accurate.
		//! Defined between -2pi and 2pi. 
		//! From GLM_GTX_fast_trigonometry extension.
		template <typename T> 
		T fastAtan(const T& y, const T& x);

		//! Faster than the common atan function but less accurate. 
		//! Defined between -2pi and 2pi.
		//! From GLM_GTX_fast_trigonometry extension.
        template <typename T> 
		T fastAtan(const T& angle);

    }//namespace fast_trigonometry
    }//namespace gtx
}//namespace glm

#define GLM_GTX_fast_trigonometry namespace gtx::fast_trigonometry
#ifndef GLM_GTX_GLOBAL
namespace glm {using GLM_GTX_fast_trigonometry;}
#endif//GLM_GTX_GLOBAL

#include "fast_trigonometry.inl"

#endif//glm_gtx_fast_trigonometry
