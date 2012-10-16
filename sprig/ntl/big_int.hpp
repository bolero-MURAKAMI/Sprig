#ifndef SPRIG_NTL_BIG_INT_HPP
#define SPRIG_NTL_BIG_INT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <climits>
#include <iosfwd>
#include <limits>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/operators.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/swap.hpp>
#include <sprig/external/ntl/zz.hpp>
#include <sprig/str_cast.hpp>
#include <sprig/cast_converter.hpp>
#include <sprig/type_traits/is_call_copy_param.hpp>
#include <sprig/type_traits/is_char_type.hpp>
#include <sprig/type_traits/is_wchar_type.hpp>
#include <sprig/ntl/to_ZZ.hpp>
#include <sprig/ntl/from_ZZ.hpp>
#include <sprig/ntl/significant.hpp>

//
// SPRIG_NTL_BIG_INT_DIGITS
//
#ifndef SPRIG_NTL_BIG_INT_DIGITS
#	define SPRIG_NTL_BIG_INT_DIGITS 0x0000FFFF
#endif	// #ifndef SPRIG_NTL_BIG_INT_DIGITS
//
// SPRIG_NTL_BIG_INT_DIGITS10
//
#ifndef SPRIG_NTL_BIG_INT_DIGITS10
#	define SPRIG_NTL_BIG_INT_DIGITS10 0x0000FFFF
#endif	// #ifndef SPRIG_NTL_BIG_INT_DIGITS10

namespace sprig {
	namespace big_int_detail {
		//
		// typedef
		//
		typedef NTL::ZZ internal_type;
		typedef unsigned char byte_type;
		typedef long int_type;
		//
		// neq_zero
		//
		struct neq_zero {
			bool operator()(byte_type b) const {
				return b != 0;
			}
		};
	}	// namespace big_int_detail
	//
	// big_int
	//
	class big_int
		: private boost::operators<big_int>
	{
	private:
		typedef big_int this_type;
		typedef big_int_detail::internal_type internal_type;
		typedef big_int_detail::byte_type byte_type;
	private:
		internal_type value_;
	public:
		//
		//	COMMENT: 符号
		//
		enum sign {
			sign_zero = 0,
			sign_plus = 1,
			sign_minus = -1
		};
	public:
		//
		//	COMMENT: ゼロ
		//
		static big_int const& zero() {
			static this_type value;
			return value;
		}
	public:
		//
		//	COMMENT: デフォルトコンストラクタ
		//
		big_int() {}
		//
		//	COMMENT: コピーコンストラクタ
		//
		big_int(this_type const& other)
			: value_(other.value_)
		{}
		//
		//	COMMENT: コンストラクタ（バイト列から）
		//	NOTE: JavaのBigIntegerと違い、リトルエンディアンで解釈される
		//
		big_int(byte_type const* source, std::size_t n)
			: value_(NTL::ZZFromBytes(source, static_cast<long>(n)))
		{}
		big_int(char const* source, std::size_t n)
			: value_(NTL::ZZFromBytes(reinterpret_cast<byte_type const*>(source), static_cast<long>(n)))
		{}
		big_int(signed char const* source, std::size_t n)
			: value_(NTL::ZZFromBytes(reinterpret_cast<byte_type const*>(source), static_cast<long>(n)))
		{}
		template<std::size_t N>
		big_int(byte_type const (&source)[N])
			: value_(NTL::ZZFromBytes(source, N))
		{}
		template<std::size_t N>
		big_int(char const (&source)[N])
			: value_(NTL::ZZFromBytes(reinterpret_cast<byte_type const (&)[N]>(source), N))
		{}
		template<std::size_t N>
		big_int(signed char const (&source)[N])
			: value_(NTL::ZZFromBytes(reinterpret_cast<byte_type const (&)[N]>(source), N))
		{}
		template<typename Iterator>
		big_int(Iterator first, Iterator last) {
			std::vector<byte_type> bytes(std::distance(first, last));
			value_ = NTL::ZZFromBytes(&bytes[0], bytes.size());
		}
		//
		//	COMMENT: コンストラクタ（バイト列から／符号付）
		//	NOTE: JavaのBigIntegerと違い、リトルエンディアンで解釈される
		//
		big_int(byte_type const* source, std::size_t n, sign s)
			: value_(s >= sign_zero
				? NTL::ZZFromBytes(source, static_cast<long>(n))
				: -NTL::ZZFromBytes(source, static_cast<long>(n))
				)
		{}
		big_int(char const* source, std::size_t n, sign s)
			: value_(s >= sign_zero
				? NTL::ZZFromBytes(reinterpret_cast<byte_type const*>(source), static_cast<long>(n))
				: -NTL::ZZFromBytes(reinterpret_cast<byte_type const*>(source), static_cast<long>(n))
				)
		{}
		big_int(signed char const* source, std::size_t n, sign s)
			: value_(s >= sign_zero
				? NTL::ZZFromBytes(reinterpret_cast<byte_type const*>(source), static_cast<long>(n))
				: -NTL::ZZFromBytes(reinterpret_cast<byte_type const*>(source), static_cast<long>(n))
				)
		{}
		template<std::size_t N>
		big_int(byte_type const (&source)[N], sign s)
			: value_(s >= sign_zero
				? NTL::ZZFromBytes(source, N)
				: -NTL::ZZFromBytes(source, N)
				)
		{}
		template<std::size_t N>
		big_int(char const (&source)[N], sign s)
			: value_(s >= sign_zero
				? NTL::ZZFromBytes(reinterpret_cast<byte_type const (&)[N]>(source), N)
				: -NTL::ZZFromBytes(reinterpret_cast<byte_type const (&)[N]>(source), N)
				)
		{}
		template<std::size_t N>
		big_int(signed char const (&source)[N], sign s)
			: value_(s >= sign_zero
				? NTL::ZZFromBytes(reinterpret_cast<byte_type const (&)[N]>(source), N)
				: -NTL::ZZFromBytes(reinterpret_cast<byte_type const (&)[N]>(source), N)
				)
		{}
		template<typename Iterator>
		big_int(Iterator first, Iterator last, sign s) {
			std::vector<byte_type> bytes(std::distance(first, last));
			value_ = s >= sign_zero
				? NTL::ZZFromBytes(&bytes[0], bytes.size())
				: -NTL::ZZFromBytes(&bytes[0], bytes.size())
				;
		}
		//
		//	COMMENT: 変換コンストラクタ（内部型，算術型，文字列型）
		//
		big_int(internal_type const& source)
			: value_(source)
		{}
		template<typename T>
		big_int(T const& source)
			: value_(to_ZZ(source))
		{}
		//
		//	COMMENT: デストラクタ
		//
		~big_int() {}
		//
		//	COMMENT: 代入
		//
		this_type& operator=(this_type const& rhs) {
			this_type(rhs).swap(*this);
			return *this;
		}
		//
		//	COMMENT: swap
		//
		void swap(this_type& rhs) {
			boost::swap(value_, rhs.value_);
		}
		//
		// SPRIG_NTL_BIGINT_COMPARE_OPERATION
		//
#define SPRIG_NTL_BIGINT_COMPARE_OPERATION(OP) \
		bool operator OP(this_type const& rhs) const { \
			return value_ OP rhs.value_ != 0; \
		} \
		bool operator OP(internal_type const& rhs) const { \
			return value_ OP rhs != 0; \
		} \
		template<typename T> \
		typename boost::enable_if<sprig::is_call_copy_param<T>, bool>::type \
		operator OP(T const rhs) const { \
			return value_ OP rhs != 0; \
		} \
		template<typename T> \
		typename boost::disable_if<sprig::is_call_copy_param<T>, bool>::type \
		operator OP(T const& rhs) const { \
			return value_ OP rhs != 0; \
		}
		//
		// SPRIG_NTL_BIGINT_SUBSTITUTE_OPERATION
		//
#define SPRIG_NTL_BIGINT_SUBSTITUTE_OPERATION(OP) \
		this_type& operator OP(this_type const& rhs) { \
			value_ OP rhs.value_; \
			return *this; \
		} \
		this_type& operator OP(internal_type const& rhs) { \
			value_ OP rhs; \
			return *this; \
		} \
		template<typename T> \
		typename boost::enable_if<sprig::is_call_copy_param<T>, this_type>::type& \
		operator OP(T const rhs) { \
			value_ OP to_ZZ(rhs); \
			return *this; \
		} \
		template<typename T> \
		typename boost::disable_if<sprig::is_call_copy_param<T>, this_type>::type& \
		operator OP(T const& rhs) { \
			value_ OP to_ZZ(rhs); \
			return *this; \
		}
		//
		// SPRIG_NTL_BIGINT_SUBSTITUTE_DIRECT_OPERATION
		//
#define SPRIG_NTL_BIGINT_SUBSTITUTE_DIRECT_OPERATION(OP) \
		template<typename T> \
		typename boost::enable_if<sprig::is_call_copy_param<T>, this_type>::type& \
		operator OP(T const rhs) { \
			value_ OP rhs; \
			return *this; \
		} \
		template<typename T> \
		typename boost::disable_if<sprig::is_call_copy_param<T>, this_type>::type& \
		operator OP(T const& rhs) { \
			value_ OP rhs; \
			return *this; \
		}
		//
		//	COMMENT: 算術演算子
		//
		SPRIG_NTL_BIGINT_COMPARE_OPERATION(<)
		SPRIG_NTL_BIGINT_COMPARE_OPERATION(==)
		SPRIG_NTL_BIGINT_SUBSTITUTE_OPERATION(+=)
		SPRIG_NTL_BIGINT_SUBSTITUTE_OPERATION(-=)
		SPRIG_NTL_BIGINT_SUBSTITUTE_OPERATION(*=)
		SPRIG_NTL_BIGINT_SUBSTITUTE_OPERATION(/=)
		SPRIG_NTL_BIGINT_SUBSTITUTE_OPERATION(%=)
		SPRIG_NTL_BIGINT_SUBSTITUTE_OPERATION(|=)
		SPRIG_NTL_BIGINT_SUBSTITUTE_OPERATION(&=)
		SPRIG_NTL_BIGINT_SUBSTITUTE_OPERATION(^=)
		SPRIG_NTL_BIGINT_SUBSTITUTE_DIRECT_OPERATION(<<=)
		SPRIG_NTL_BIGINT_SUBSTITUTE_DIRECT_OPERATION(>>=)
		//
		//	COMMENT: 単項演算子
		//
		this_type operator+() const {
			return this_type(value_);
		}
		this_type operator-() const {
			return this_type(-value_);
		}
		this_type& operator++() {
			++value_;
			return *this;
		}
		this_type& operator--() {
			--value_;
			return *this;
		}
		this_type operator++(int) {
			this_type temp(*this);
			value_++;
			return temp;
		}
		this_type operator--(int) {
			this_type temp(*this);
			value_--;
			return temp;
		}
		//
		//	COMMENT: 変換演算子
		//
		operator internal_type const&() const {
			return value_;
		}
		//
		//	COMMENT: 取得
		//
		internal_type const& get() const {
			return value_;
		}
		internal_type const& ref() const {
			return value_;
		}
		internal_type& ref() {
			return value_;
		}
	};

	//
	// operators
	//
	template<typename Elem, typename Traits>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>&
	operator<<(std::basic_ostream<Elem, Traits>& lhs, big_int const& rhs) {
		return lhs << rhs.ref();
	}
	template<typename Elem, typename Traits>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>&
	operator>>(std::basic_istream<Elem, Traits>& lhs, big_int& rhs) {
		return lhs >> rhs.ref();
	}

	//
	// get_bytes
	//	COMMENT: バイト列取得
	//	NOTE: JavaのBigIntegerと違い、リトルエンディアンで解釈される
	//
	SPRIG_INLINE void get_bytes(big_int const& v, big_int_detail::byte_type* dest, std::size_t n) {
		std::vector<big_int_detail::byte_type> bytes(n);
		NTL::BytesFromZZ(&bytes[0], v.get(), static_cast<long>(bytes.size()));
		std::copy(bytes.begin(), bytes.end(), dest);
	}
	SPRIG_INLINE void get_bytes(big_int const& v, char* dest, std::size_t n) {
		get_bytes(v, reinterpret_cast<big_int_detail::byte_type*>(dest), n);
	}
	SPRIG_INLINE void get_bytes(big_int const& v, signed char* dest, std::size_t n) {
		get_bytes(v, reinterpret_cast<big_int_detail::byte_type*>(dest), n);
	}
	template<std::size_t N>
	SPRIG_INLINE void get_bytes(big_int const& v, big_int_detail::byte_type (&dest)[N]) {
		get_bytes(v, dest, N);
	}
	template<std::size_t N>
	SPRIG_INLINE void get_bytes(big_int const& v, char (&dest)[N]) {
		get_bytes(v, reinterpret_cast<big_int_detail::byte_type (&)[N]>(dest));
	}
	template<std::size_t N>
	SPRIG_INLINE void get_bytes(big_int const& v, signed char (&dest)[N]) {
		get_bytes(v, reinterpret_cast<big_int_detail::byte_type (&)[N]>(dest));
	}
	template<typename Iterator>
	SPRIG_INLINE void get_bytes(big_int const& v, Iterator first, Iterator last) {
		std::vector<big_int_detail::byte_type> bytes(std::distance(first, last));
		NTL::BytesFromZZ(&bytes[0], v.get(), bytes.size());
		std::vector<big_int_detail::byte_type>::iterator valid_last = std::find_if(
			bytes.rbegin(),
			bytes.rend(),
			big_int_detail::neq_zero()
			).base();
		bytes.erase(valid_last, bytes.end());
		std::copy(bytes.begin(), bytes.end(), first);
	}
	template<typename Iterator>
	SPRIG_INLINE void get_bytes(big_int const& v, Iterator out) {
		std::vector<big_int_detail::byte_type> bytes(
			(v.get().size() * NTL_ZZ_NBITS + (CHAR_BIT - 1)) / CHAR_BIT
			);
		NTL::BytesFromZZ(&bytes[0], v.get(), bytes.size());
		std::vector<big_int_detail::byte_type>::iterator valid_last = std::find_if(
			bytes.rbegin(),
			bytes.rend(),
			big_int_detail::neq_zero()
			).base();
		bytes.erase(valid_last, bytes.end());
		std::copy(bytes.begin(), bytes.end(), out);
	}

	//
	// sign
	//
	SPRIG_INLINE big_int::sign sign(big_int const& v) {
		return v == big_int::zero()
			? big_int::sign_zero
			: v > big_int::zero()
				? big_int::sign_plus
				: big_int::sign_minus
			;
	}
	//
	// abs
	//
	SPRIG_INLINE big_int abs(big_int const& v) {
		return big_int(NTL::abs(v.get()));
	}
	SPRIG_INLINE void abs(big_int& d, big_int const& v) {
		NTL::abs(d.ref(), v.get());
	}
	//
	// pow
	//
	SPRIG_INLINE big_int pow(big_int const& v, big_int_detail::int_type e) {
		return big_int(NTL::power(v.get(), e));
	}
	SPRIG_INLINE void pow(big_int& d, big_int const& v, big_int_detail::int_type e) {
		NTL::power(d.ref(), v.get(), e);
	}
	//
	// gcd
	//
	SPRIG_INLINE big_int gcd(big_int const& v1, big_int const& v2) {
		big_int result;
		NTL::GCD(result.ref(), v1.get(), v2.get());
		return result;
	}
	SPRIG_INLINE void gcd(big_int& d, big_int const& v1, big_int const& v2) {
		NTL::GCD(d.ref(), v1.get(), v2.get());
	}
	//
	// max
	//
	SPRIG_INLINE big_int const& max(big_int const& v1, big_int const& v2) {
		return (std::max)(v1, v2);
	}
	SPRIG_INLINE void max(big_int& d, big_int const& v1, big_int const& v2) {
		d = (std::max)(v1, v2);
	}
	//
	// min
	//
	SPRIG_INLINE big_int const& min(big_int const& v1, big_int const& v2) {
		return (std::min)(v1, v2);
	}
	SPRIG_INLINE void min(big_int& d, big_int const& v1, big_int const& v2) {
		d = (std::min)(v1, v2);
	}

	//
	// big_int_cast
	//
	template<typename To>
	SPRIG_INLINE typename boost::enable_if<
		boost::mpl::or_<
			typename boost::is_same<typename boost::remove_const<To>::type, NTL::ZZ>::type,
			typename boost::is_same<typename boost::remove_const<To>::type, NTL::RR>::type,
			typename boost::is_same<typename boost::remove_const<To>::type, NTL::xdouble>::type,
			typename boost::is_same<typename boost::remove_const<To>::type, NTL::quad_float>::type,
			typename boost::is_arithmetic<To>::type
		>,
		To
	>::type
	big_int_cast(big_int const& target) {
		return from_ZZ<To>(target.get());
	}

	//
	// big_int_cast_converter_tag
	//
	struct big_int_cast_converter_tag {};
	//
	// specialization big_int_cast_converter_tag
	//
	template<typename Value>
	class cast_converter<big_int_cast_converter_tag, Value> {
	public:
		typedef big_int_cast_converter_tag tag_type;
		typedef Value value_type;
		typedef value_type& param_type;
	private:
		param_type param_;
	private:
		cast_converter();
	public:
		cast_converter(param_type param)
			: param_(param)
		{}
		template<typename T>
		operator T() {
			return big_int_cast<T>(param_);
		}
	};
}	// namespace sprig

namespace std {
	//
	// numeric_limits
	//
	template<>
	class numeric_limits<sprig::big_int> {
	public:
		static bool const is_specialized = true;
		static int const radix = numeric_limits<int>::radix;
		static int const digits = SPRIG_NTL_BIG_INT_DIGITS;
		static int const digits10 = SPRIG_NTL_BIG_INT_DIGITS10;
		static bool const is_signed = true;
		static bool const is_integer = true;
		static bool const is_exact = true;
		static bool const is_bounded = false;
		static bool const is_modulo = false;
		static bool const traps = false;
	public:
		//static sprig::big_int max();
		//static sprig::big_int min();
	};
}	// namespace std

#endif	// #ifndef SPRIG_NTL_BIG_INT_HPP
