/*=============================================================================
  Copyright (c) 2010-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprig

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPRIG_UBLAS_MATRIX_HPP
#define SPRIG_UBLAS_MATRIX_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <cmath>
#include <boost/array.hpp>
#include <boost/call_traits.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace sprig {
	namespace ublas {
		//
		// make_scaling_matrix_2d
		//
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::matrix<T> make_scaling_matrix_2d(T const sx, T const sy) {
			boost::numeric::ublas::matrix<T> mat = boost::numeric::ublas::identity_matrix<T>(3);
			mat(0, 0) = sx;
			mat(1, 1) = sy;
			return mat;
		}
		//
		// make_rotation_matrix_2d
		//
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::matrix<T> make_rotation_matrix_2d(T const a) {
			boost::numeric::ublas::matrix<T> mat = boost::numeric::ublas::identity_matrix<T>(3);
			mat(0, 0) = std::cos(a);
			mat(0, 1) = std::sin(a);
			mat(1, 0) = -mat(0, 1);
			mat(1, 1) = mat(0, 0);
			return mat;
		}
		//
		// make_translation_matrix_2d
		//
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::matrix<T> make_translation_matrix_2d(T const tx, T const ty) {
			boost::numeric::ublas::matrix<T> mat = boost::numeric::ublas::identity_matrix<T>(3);
			mat(2, 0) = tx;
			mat(2, 1) = ty;
			return mat;
		}
		//
		// matrix_prod
		//
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::matrix<T> matrix_prod(
			boost::numeric::ublas::matrix<T> const& m1,
			boost::numeric::ublas::matrix<T> const& m2
			)
		{
			return boost::numeric::ublas::prod(m1, m2);
		}
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::matrix<T> matrix_prod(
			boost::numeric::ublas::matrix<T> const& m1,
			boost::numeric::ublas::matrix<T> const& m2,
			boost::numeric::ublas::matrix<T> const& m3
			)
		{
			return boost::numeric::ublas::prod(matrix_prod(m1, m2), m3);
		}
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::matrix<T> matrix_prod(
			boost::numeric::ublas::matrix<T> const& m1,
			boost::numeric::ublas::matrix<T> const& m2,
			boost::numeric::ublas::matrix<T> const& m3,
			boost::numeric::ublas::matrix<T> const& m4
			)
		{
			return boost::numeric::ublas::prod(matrix_prod(m1, m2, m3), m4);
		}
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::matrix<T> matrix_prod(
			boost::numeric::ublas::matrix<T> const& m1,
			boost::numeric::ublas::matrix<T> const& m2,
			boost::numeric::ublas::matrix<T> const& m3,
			boost::numeric::ublas::matrix<T> const& m4,
			boost::numeric::ublas::matrix<T> const& m5
			)
		{
			return boost::numeric::ublas::prod(matrix_prod(m1, m2, m3, m4), m5);
		}
		//
		// scaling_2d
		//
		template<typename T>
		class scaling_2d {
		public:
			typedef T value_type;
			typedef boost::numeric::ublas::matrix<value_type> matrix_type;
		private:
			boost::array<value_type, 2> elems_;
		public:
			scaling_2d() {
				elems_[0] = value_type();
				elems_[1] = value_type();
			}
			scaling_2d(
				typename boost::call_traits<value_type>::param_type v1,
				typename boost::call_traits<value_type>::param_type v2
				)
			{
				elems_[0] = v1;
				elems_[1] = v2;
			}
			matrix_type matrix() const{
				return make_scaling_matrix_2d(elems_[0], elems_[1]);
			}
			template<std::size_t N>
			value_type const& get() const {
				return elems_[N];
			}
			template<std::size_t N>
			value_type& get() {
				return elems_[N];
			}
		};
		//
		// rotation_2d
		//
		template<typename T>
		class rotation_2d {
		public:
			typedef T value_type;
			typedef boost::numeric::ublas::matrix<value_type> matrix_type;
		private:
			boost::array<value_type, 1> elems_;
		public:
			rotation_2d() {
				elems_[0] = value_type();
			}
			rotation_2d(
				typename boost::call_traits<value_type>::param_type v1
				)
			{
				elems_[0] = v1;
			}
			matrix_type matrix() const{
				return make_rotation_matrix_2d(elems_[0]);
			}
			template<std::size_t N>
			value_type const& get() const {
				return elems_[N];
			}
			template<std::size_t N>
			value_type& get() {
				return elems_[N];
			}
		};
		//
		// translation_2d
		//
		template<typename T>
		class translation_2d {
		public:
			typedef T value_type;
			typedef boost::numeric::ublas::matrix<value_type> matrix_type;
		private:
			boost::array<value_type, 2> elems_;
		public:
			translation_2d() {
				elems_[0] = value_type();
				elems_[1] = value_type();
			}
			translation_2d(
				typename boost::call_traits<value_type>::param_type v1,
				typename boost::call_traits<value_type>::param_type v2
				)
			{
				elems_[0] = v1;
				elems_[1] = v2;
			}
			matrix_type matrix() const{
				return make_translation_matrix_2d(elems_[0], elems_[1]);
			}
			template<std::size_t N>
			value_type const& get() const {
				return elems_[N];
			}
			template<std::size_t N>
			value_type& get() {
				return elems_[N];
			}
		};
	}	// namespace ublas
}	// namespace sprig

#endif	// #ifndef SPRIG_UBLAS_MATRIX_HPP
