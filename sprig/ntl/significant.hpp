#ifndef SPRIG_NTL_SIGNIFICANT_HPP
#define SPRIG_NTL_SIGNIFICANT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <boost/range.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/call_traits.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/external/ntl/zz.hpp>
#include <sprig/external/ntl/rr.hpp>
#include <sprig/math.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/type_traits/is_char_type.hpp>
#include <sprig/type_traits/is_wchar_type.hpp>
#include <sprig/type_traits/is_c_str.hpp>
#include <sprig/type_traits/is_basic_string.hpp>
#include <sprig/type_traits/c_str_element.hpp>
#include <sprig/type_traits/remove_const_reference.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/ntl/to_ZZ.hpp>
#include <sprig/ntl/to_RR.hpp>

namespace sprig {
	//
	// significant
	//
	template<typename T, typename Enable = void>
	class significant {};

	//
	// significant_base
	//
	template<typename T>
	class significant_base {
	public:
		typedef T type;
		typedef typename boost::call_traits<type>::param_type param_type;
		typedef std::size_t digits_type;
		typedef NTL::ZZ digits_ZZ_type;
		typedef NTL::RR digits_RR_type;
	protected:
		~significant_base();
	//public:
	//	static digits_type digits();
	//	static digits_ZZ_type const& digits_ZZ();
	//	static digits_RR_type const& digits_RR();
	//	static digits_type digits(param_type target);
	//	static digits_ZZ_type const& digits_ZZ(param_type target);
	//	static digits_RR_type const& digits_RR(param_type target);
	//	static digits_type digits10();
	//	static digits_ZZ_type const& digits10_ZZ();
	//	static digits_RR_type const& digits10_RR();
	};

	//
	// significant_float_base
	//
	template<typename T, std::size_t N>
	class significant_float_base
		: public significant_base<T>
	{
	private:
		typedef significant_base<T> base_type;
	public:
		typedef typename base_type::param_type param_type;
		typedef typename base_type::digits_type digits_type;
		typedef typename base_type::digits_ZZ_type digits_ZZ_type;
		typedef typename base_type::digits_RR_type digits_RR_type;
	public:
		static digits_type digits() {
			return N;
		}
		static digits_ZZ_type const& digits_ZZ() {
			static digits_ZZ_type const digits_(NTL::to_ZZ(N));
			return digits_;
		}
		static digits_RR_type const& digits_RR() {
			static digits_RR_type const digits_(NTL::to_RR(N));
			return digits_;
		}
		static digits_type digits(param_type) {
			return digits();
		}
		static digits_ZZ_type const& digits_ZZ(param_type) {
			return digits_RR();
		}
		static digits_RR_type const& digits_RR(param_type) {
			return digits_RR();
		}
		static digits_type digits10() {
			static digits_type const digits_(std::pow(10.0, static_cast<int>(N)));
			return digits_;
		}
		static digits_ZZ_type const& digits10_ZZ() {
			static digits_ZZ_type const digits_(NTL::power(NTL::to_ZZ(10), N));
			return digits_;
		}
		static digits_RR_type const& digits10_RR() {
			static digits_RR_type const digits_(NTL::power(NTL::to_RR(10), N));
			return digits_;
		}
	};

	//
	// significant_float_utils
	//
	template<typename Char, typename Enable = void>
	class significant_float_utils {};
	template<typename Char>
	class significant_float_utils<
		Char,
		typename boost::enable_if<
			is_char_type<Char>
		>::type
	> {
	public:
		typedef Char char_type;
	public:
		static char_type const e = 'e';
		static char_type const point = '.';
	public:
		template<typename IntType, typename Range>
		static IntType exponent(Range const& range) {
			typedef std::basic_string<char_type> string_type;
			typedef typename boost::range_iterator<Range>::type iterator;
			iterator i_e = std::find(boost::begin(range), boost::end(range), e);
			return i_e != boost::end(range)
				? boost::lexical_cast<IntType>(string_type(i_e + 1, boost::end(range)))
				: 0
				;
		}
		template<typename IntType, typename Range>
		static IntType integral(Range const& range) {
			typedef std::basic_string<char_type> string_type;
			typedef typename boost::range_iterator<Range>::type iterator;
			iterator i_point = std::find(boost::begin(range), boost::end(range), point);
			iterator i_e = std::find(boost::begin(range), boost::end(range), e);
			return i_point != boost::end(range)
				? boost::lexical_cast<IntType>(string_type(boost::begin(range), i_point))
				: i_e != boost::end(range)
					? boost::lexical_cast<IntType>(string_type(boost::begin(range), i_e))
					: boost::lexical_cast<IntType>(string_type(boost::begin(range), boost::end(range)))
				;
		}
		template<typename IntType, typename Range>
		static IntType fractional(Range const& range) {
			typedef std::basic_string<char_type> string_type;
			typedef typename boost::range_iterator<Range>::type iterator;
			iterator i_point = std::find(boost::begin(range), boost::end(range), point);
			iterator i_e = std::find(boost::begin(range), boost::end(range), e);
			return i_point != boost::end(range)
				? boost::lexical_cast<IntType>(string_type(i_point + 1, i_e))
				: 0
				;
		}
	};
	template<typename Char>
	class significant_float_utils<
		Char,
		typename boost::enable_if<
			is_wchar_type<Char>
		>::type
	> {
	public:
		typedef Char char_type;
	public:
		static char_type const e = L'e';
		static char_type const point = L'.';
	};

	//
	// significant_c_str_impl
	//
	template<typename Char>
	class significant_c_str_impl
		: public significant_base<Char const*>
	{
	private:
		typedef significant_base<Char const*> base_type;
	public:
		typedef typename base_type::param_type param_type;
		typedef typename base_type::digits_type digits_type;
		typedef typename base_type::digits_ZZ_type digits_ZZ_type;
		typedef typename base_type::digits_RR_type digits_RR_type;
	public:
		typedef Char char_type;
	public:
		static digits_type digits() {
			return 0;
		}
		static digits_ZZ_type const& digits_ZZ() {
			static digits_ZZ_type const digits_(NTL::to_ZZ(0));
			return digits_;
		}
		static digits_RR_type const& digits_RR() {
			static digits_RR_type const digits_(NTL::to_RR(0));
			return digits_;
		}
		static digits_type digits(param_type target) {
			return digits<std::basic_string<char_type> >(target);
		}
		template<typename String>
		static digits_type digits(String const& target) {
			typedef String string_type;
			typedef typename string_type::iterator iterator;
			digits_type result = 0;
			string_type value(target);
			iterator i_e = std::find(value.begin(), value.end(), significant_float_utils<char_type>::e);
			iterator i_point = std::find(value.begin(), value.end(), significant_float_utils<char_type>::point);
			if (i_point != value.end()) {
				result += std::distance(i_point + 1, i_e);
			}
			if (i_e != value.end()) {
				result -= boost::lexical_cast<digits_type>(string_type(i_e + 1, value.end()));
			}
			return result >= 0 ? result : 0;
		}
		static digits_ZZ_type const& digits_ZZ(param_type target) {
			return NTL::to_ZZ(digits(target));
		}
		static digits_RR_type const& digits_RR(param_type target) {
			return NTL::to_RR(digits(target));
		}
		static digits_type digits10() {
			return 1;
		}
		static digits_ZZ_type const& digits10_ZZ() {
			static digits_ZZ_type const digits_(NTL::to_ZZ(1));
			return digits_;
		}
		static digits_RR_type const& digits10_RR() {
			static digits_RR_type const digits_(NTL::to_RR(1));
			return digits_;
		}
	};

	//
	// specialization significant: is_integral(T)
	//
	template<typename T>
	class significant<
		T,
		typename boost::enable_if<
			boost::is_integral<T>
		>::type
	>
		: public significant_base<T>
	{
	private:
		typedef significant_base<T> base_type;
	public:
		typedef typename base_type::param_type param_type;
		typedef typename base_type::digits_type digits_type;
		typedef typename base_type::digits_ZZ_type digits_ZZ_type;
		typedef typename base_type::digits_RR_type digits_RR_type;
	public:
		static digits_type digits() {
			return 1;
		}
		static digits_ZZ_type const& digits_ZZ() {
			static digits_ZZ_type const digits_(NTL::to_ZZ(1));
			return digits_;
		}
		static digits_RR_type const& digits_RR() {
			static digits_RR_type const digits_(NTL::to_RR(1));
			return digits_;
		}
		static digits_type digits(param_type) {
			return 1;
		}
		static digits_ZZ_type const& digits_ZZ(param_type) {
			return digits_ZZ();
		}
		static digits_RR_type const& digits_RR(param_type) {
			return digits_RR();
		}
		static digits_type digits10() {
			return 10;
		}
		static digits_ZZ_type const& digits10_ZZ() {
			static digits_ZZ_type const digits_(NTL::to_ZZ(10));
			return digits_;
		}
		static digits_RR_type const& digits10_RR() {
			static digits_RR_type const digits_(NTL::to_RR(10));
			return digits_;
		}
	};
	//
	// specialization significant: is_same(T, float), is_same(T, double), is_same(T, long double)
	//
	template<typename T>
	class significant<
		T,
		typename boost::enable_if<
			boost::is_same<T, float>
		>::type
	>
		: public significant_float_base<T, 7>
	{};
	template<typename T>
	class significant<T, typename boost::enable_if<boost::is_same<T, double> >::type>
		: public significant_float_base<T, 15>
	{};
	template<typename T>
	class significant<T, typename boost::enable_if<boost::is_same<T, long double> >::type>
		: public significant_float_base<T, 15>
	{};
	//
	// specialization significant: is_c_str(T)
	//
	template<typename T>
	class significant<
		T,
		typename boost::enable_if<
			is_c_str<T>
		>::type
	>
		: public significant_base<T>
	{
	private:
		typedef significant_base<T> base_type;
	public:
		typedef typename base_type::param_type param_type;
		typedef typename base_type::digits_type digits_type;
		typedef typename base_type::digits_ZZ_type digits_ZZ_type;
		typedef typename base_type::digits_RR_type digits_RR_type;
	private:
		typedef significant_c_str_impl<
			typename c_str_element_value<T>::type
		> impl_type;
	public:
		static digits_type digits() {
			return impl_type::digits();
		}
		static digits_ZZ_type const& digits_ZZ() {
			return impl_type::digits_ZZ();
		}
		static digits_RR_type const& digits_RR() {
			return impl_type::digits_RR();
		}
		static digits_type digits(param_type target) {
			return impl_type::digits(target);
		}
		static digits_ZZ_type const& digits_ZZ(param_type target) {
			return impl_type::digits_ZZ(target);
		}
		static digits_RR_type const& digits_RR(param_type target) {
			return impl_type::digits_RR(target);
		}
		static digits_type digits10() {
			return impl_type::digits10();
		}
		static digits_ZZ_type const& digits10_ZZ() {
			return impl_type::digits10_ZZ();
		}
		static digits_RR_type const& digits10_RR() {
			return impl_type::digits10_RR();
		}
	};

	//
	// specialization significant: is_basic_string(T)
	//
	template<typename T>
	class significant<
		T,
		typename boost::enable_if<
			is_basic_string<T>
		>::type
	>
		: public significant_base<T>
	{
	private:
		typedef significant_base<T> base_type;
	public:
		typedef typename base_type::param_type param_type;
		typedef typename base_type::digits_type digits_type;
		typedef typename base_type::digits_ZZ_type digits_ZZ_type;
		typedef typename base_type::digits_RR_type digits_RR_type;
	private:
		typedef significant_c_str_impl<
			typename remove_const_reference<T>::type::value_type
		> impl_type;
	public:
		static digits_type digits() {
			return impl_type::digits();
		}
		static digits_ZZ_type const& digits_ZZ() {
			return impl_type::digits_ZZ();
		}
		static digits_RR_type const& digits_RR() {
			return impl_type::digits_RR();
		}
		static digits_type digits(param_type target) {
			return impl_type::template digits<typename remove_const_reference<T>::type>(target);
		}
		static digits_ZZ_type const& digits_ZZ(param_type target) {
			return impl_type::digits_ZZ(target);
		}
		static digits_RR_type const& digits_RR(param_type target) {
			return impl_type::digits_RR(target);
		}
		static digits_type digits10() {
			return impl_type::digits10();
		}
		static digits_ZZ_type const& digits10_ZZ() {
			return impl_type::digits10_ZZ();
		}
		static digits_RR_type const& digits10_RR() {
			return impl_type::digits10_RR();
		}
	};

	//
	// significant_digits
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_call_copy_param<typename significant<T>::param_type>,
		typename significant<T>::digits_type
	>::type
	significant_digits(T const target) {
		return significant<T>::digits(target);
	}
	template<typename T>
	SPRIG_INLINE typename boost::disable_if<
		is_call_copy_param<typename significant<T>::param_type>,
		typename significant<T>::digits_type
	>::type
	significant_digits(T const& target) {
		return significant<T>::digits(target);
	}

	//
	// to_ZZ_full_significant
	//
	// specialization to_ZZ_full_significant: is_integral(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_integral<T>,
		NTL::ZZ
	>::type
	to_ZZ_full_significant(T const target) {
		return to_ZZ(target);
	}
	//
	// specialization to_ZZ_full_significant: is_float(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_float<T>,
		NTL::ZZ
	>::type
	to_ZZ_full_significant(T const target) {
		typename significant<T>::digits_type digits = integer_digits(target);
		return to_ZZ(NTL::trunc(to_RR(target) * NTL::power(to_RR(10), static_cast<long>(significant<T>::digits() - digits))))
			* NTL::power(to_ZZ(10), static_cast<long>(digits));
	}
	//
	// specialization to_ZZ_full_significant: is_c_str(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_c_str<T>,
		NTL::ZZ
	>::type
	to_ZZ_full_significant(T const target) {
		typename significant<T>::digits_type digits = significant<T>::digits(target);
		return to_ZZ(to_RR(target) * NTL::power(to_RR(10), digits));
	}
	//
	// specialization to_ZZ_full_significant: is_basic_string(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_basic_string<T>,
		NTL::ZZ
	>::type
	to_ZZ_full_significant(T const& target) {
		typename significant<T>::digits_type digits = significant<T>::digits(target);
		return to_ZZ(to_RR(target) * NTL::power(to_RR(10), digits));
	}

	//
	// to_RR_full_significant
	//
	// specialization to_RR_full_significant: is_integral(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_integral<T>,
		NTL::RR
	>::type
	to_RR_full_significant(T const target) {
		return to_ZZ(target);
	}
	//
	// specialization to_RR_full_significant: is_float(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_float<T>,
		NTL::RR
	>::type
	to_RR_full_significant(T const target) {
		typename significant<T>::digits_type digits10 = significant<T>::digits10();
		return NTL::trunc(to_RR(target) * digits10);
	}
	//
	// specialization to_RR_full_significant: is_c_str(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_c_str<T>,
		NTL::RR
	>::type
	to_RR_full_significant(T const target) {
		typename significant<T>::digits_type digits10 = significant<T>::digits10(target);
		return NTL::trunc(to_RR(target) * digits10);
	}
	//
	// specialization to_RR_full_significant: is_basic_string(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_basic_string<T>,
		NTL::RR
	>::type
	to_RR_full_significant(T const& target) {
		typename significant<T>::digits_type digits = significant<T>::digits(target);
		return NTL::trunc(to_RR(target) * NTL::power(to_RR(10), digits));
	}

	//
	// to_ZZ_significant
	//
	// specialization to_ZZ_significant: is_integral(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_integral<T>,
		NTL::ZZ
	>::type
	to_ZZ_significant(T const target) {
		return to_ZZ(target);
	}
	//
	// specialization to_ZZ_significant: is_float(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_float<T>,
		NTL::ZZ
	>::type
	to_ZZ_significant(T const target) {
		return to_ZZ(target);
	}
	//
	// specialization to_ZZ_significant: is_c_str(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_c_str<T>,
		NTL::ZZ
	>::type
	to_ZZ_significant(T const target) {
		return to_ZZ(target);
	}
	//
	// specialization to_ZZ_significant: is_basic_string(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_basic_string<T>,
		NTL::ZZ
	>::type
	to_ZZ_significant(T const& target) {
		return to_ZZ(target);
	}

	//
	// to_RR_significant
	//
	// specialization to_RR_significant: is_integral(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_integral<T>,
		NTL::RR
	>::type
	to_RR_significant(T const target) {
		return to_RR(target);
	}
	//
	// specialization to_RR_significant: is_float(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		boost::is_float<T>,
		NTL::RR
	>::type
	to_RR_significant(T const target) {
		typename significant<T>::digits_type digits10 = significant<T>::digits10();
		return to_RR_full_significant(target) / digits10;
	}
	//
	// specialization to_RR_significant: is_c_str(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_c_str<T>,
		NTL::RR
	>::type
	to_RR_significant(T const target) {
		return to_RR(target);
	}
	//
	// specialization to_RR_significant: is_basic_string(T)
	//
	template<typename T>
	SPRIG_INLINE typename boost::enable_if<
		is_basic_string<T>,
		NTL::RR
	>::type
	to_RR_significant(T const& target) {
		return to_RR(target);
	}
} // namespace sprig

#endif	// #ifndef SPRIG_NTL_SIGNIFICANT_HPP
