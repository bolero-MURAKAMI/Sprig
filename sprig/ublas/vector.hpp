#ifndef SPRIG_UBLAS_VECTOR_HPP
#define SPRIG_UBLAS_VECTOR_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <boost/array.hpp>
#include <boost/call_traits.hpp>
#include <boost/operators.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace sprig {
	namespace ublas {
		//
		// make_vector
		//
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::vector<T> make_vector(
			T const t1
			)
		{
			boost::numeric::ublas::vector<T> vec(2);
			vec(0) = t1;
			return vec;
		}
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::vector<T> make_vector(
			T const t1,
			T const t2
			)
		{
			boost::numeric::ublas::vector<T> vec(2);
			vec(0) = t1;
			vec(1) = t2;
			return vec;
		}
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::vector<T> make_vector(
			T const t1,
			T const t2,
			T const t3
			)
		{
			boost::numeric::ublas::vector<T> vec(3);
			vec(0) = t1;
			vec(1) = t2;
			vec(2) = t3;
			return vec;
		}
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::vector<T> make_vector(
			T const t1,
			T const t2,
			T const t3,
			T const t4
			)
		{
			boost::numeric::ublas::vector<T> vec(4);
			vec(0) = t1;
			vec(1) = t2;
			vec(2) = t3;
			vec(3) = t4;
			return vec;
		}
		template<typename T>
		SPRIG_INLINE boost::numeric::ublas::vector<T> make_vector(
			T const t1,
			T const t2,
			T const t3,
			T const t4,
			T const t5
			)
		{
			boost::numeric::ublas::vector<T> vec(5);
			vec(0) = t1;
			vec(1) = t2;
			vec(2) = t3;
			vec(3) = t4;
			vec(4) = t5;
			return vec;
		}
		//
		// coordinate_2d
		//
		template<typename T>
		class coordinate_2d
			: private boost::addable<coordinate_2d<T> >
			, private boost::subtractable<coordinate_2d<T> >
		{
		private:
			typedef coordinate_2d this_type;
		public:
			typedef T value_type;
			typedef boost::numeric::ublas::vector<value_type> vector_type;
		private:
			boost::array<value_type, 2> elems_;
		public:
			coordinate_2d() {
				elems_[0] = value_type();
				elems_[1] = value_type();
			}
			coordinate_2d(
				typename boost::call_traits<value_type>::param_type v1,
				typename boost::call_traits<value_type>::param_type v2
				)
			{
				elems_[0] = v1;
				elems_[1] = v2;
			}
			coordinate_2d(vector_type const& v) {
				elems_[0] = v(0);
				elems_[1] = v(1);
			}
			template<typename U>
			coordinate_2d(boost::numeric::ublas::vector<U> const& v) {
				elems_[0] = value_type(v(0));
				elems_[1] = value_type(v(1));
			}
			template<typename U>
			coordinate_2d(coordinate_2d<U> const& other) {
				elems_[0] = other.get<0>();
				elems_[1] = other.get<1>();
			}
			vector_type vector() const{
				return make_vector(elems_[0], elems_[1], value_type(1));
			}
			template<typename U>
			boost::numeric::ublas::vector<U> vector() const{
				return make_vector(U(elems_[0]), U(elems_[1]), U(1));
			}
			template<std::size_t N>
			value_type const& get() const {
				return elems_[N];
			}
			template<std::size_t N>
			value_type& get() {
				return elems_[N];
			}
			void assign(
				typename boost::call_traits<value_type>::param_type v1,
				typename boost::call_traits<value_type>::param_type v2
				)
			{
				elems_[0] = v1;
				elems_[1] = v2;
			}
			this_type& operator+=(this_type const& rhs) {
				elems_[0] += rhs.elems_[0];
				elems_[1] += rhs.elems_[1];
				return *this;
			}
			this_type& operator-=(this_type const& rhs) {
				elems_[0] -= rhs.elems_[0];
				elems_[1] -= rhs.elems_[1];
				return *this;
			}
		};
	}	// namespace ublas
}	// namespace sprig

#endif	// #ifndef SPRIG_UBLAS_VECTOR_HPP
