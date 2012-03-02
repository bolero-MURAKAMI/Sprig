#ifndef SPRIG_STRING_PIECE_HPP
#define SPRIG_STRING_PIECE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <iosfwd>
#include <boost/utility/enable_if.hpp>
#include <sprig/type_traits/is_c_str.hpp>
#include <sprig/c_str.hpp>
#include <sprig/str_length.hpp>

namespace sprig {
	//
	// basic_string_piece
	//
	template<typename Elem, typename Traits = std::char_traits<Elem> >
	class basic_string_piece {
	public:
		typedef Elem value_type;
		typedef Traits traits_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type const* pointer;
		typedef value_type const* const_pointer;
		typedef pointer iterator;
		typedef const_pointer const_iterator;
	private:
		const_pointer ptr_;
		size_type length_;
	public:
		basic_string_piece(basic_string_piece const& other)
			: ptr_(other.ptr_)
			, length_(other.length_)
		{}
		template<typename T>
		explicit basic_string_piece(
			T str,
			typename boost::enable_if<
				sprig::is_c_str<T>
			>::type* = 0
			)
			: ptr_(sprig::c_str(str))
			, length_(traits_type::length(ptr_))
		{}
		template<typename T>
		explicit basic_string_piece(
			T const& str,
			typename boost::disable_if<
				sprig::is_c_str<T>
			>::type* = 0
			)
			: ptr_(sprig::c_str(str))
			, length_(sprig::str_length(ptr_))
		{}
		const_pointer get() const {
			return ptr_;
		}
		const_pointer c_str() const {
			return ptr_;
		}
		const_iterator begin() const {
			return ptr_;
		}
		const_iterator end() const {
			return ptr_ + size();
		}
		size_type size() const {
			return length_;
		}
	};
	//
	// operator<<
	//
	template<typename Elem, typename Traits>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		basic_string_piece<Elem, Traits> const& rhs
		)
	{
		return lhs << rhs.get();
	}
	//
	// c_str
	//
	template<typename Elem, typename Traits>
	SPRIG_INLINE typename basic_string_piece<Elem, Traits>::value_type const* c_str(
		basic_string_piece<Elem, Traits> const& str
		)
	{
		return str.c_str();
	}
	//
	// str_length
	//
	template<typename Elem, typename Traits>
	SPRIG_INLINE typename basic_string_piece<Elem, Traits>::size_type str_length(
		basic_string_piece<Elem, Traits> const& str
		)
	{
		return str.size();
	}
	//
	// string_piece
	// wstring_piece
	//
	typedef basic_string_piece<char> string_piece;
	typedef basic_string_piece<wchar_t> wstring_piece;

	//
	// basic_string_speck
	//
	template<typename Elem, typename Traits = std::char_traits<Elem> >
	class basic_string_speck {
	public:
		typedef Elem value_type;
		typedef Traits traits_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type const* pointer;
		typedef value_type const* const_pointer;
		typedef pointer iterator;
		typedef const_pointer const_iterator;
	private:
		const_pointer ptr_;
	public:
		basic_string_speck(basic_string_speck const& other)
			: ptr_(other.ptr_)
		{}
		template<typename T>
		explicit basic_string_speck(
			T str,
			typename boost::enable_if<
				sprig::is_c_str<T>
			>::type* = 0
			)
			: ptr_(sprig::c_str(str))
		{}
		template<typename T>
		explicit basic_string_speck(
			T const& str,
			typename boost::disable_if<
				sprig::is_c_str<T>
			>::type* = 0
			)
			: ptr_(sprig::c_str(str))
		{}
		const_pointer get() const {
			return ptr_;
		}
		const_pointer c_str() const {
			return ptr_;
		}
		const_iterator begin() const {
			return ptr_;
		}
		const_iterator end() const {
			return ptr_ + size();
		}
		size_type size() const {
			return traits_type::length(ptr_);
		}
	};
	//
	// operator<<
	//
	template<typename Elem, typename Traits>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		basic_string_speck<Elem, Traits> const& rhs
		)
	{
		return lhs << rhs.get();
	}
	//
	// c_str
	//
	template<typename Elem, typename Traits>
	SPRIG_INLINE typename basic_string_speck<Elem, Traits>::value_type const* c_str(
		basic_string_speck<Elem, Traits> const& str
		)
	{
		return str.c_str();
	}
	//
	// str_length
	//
	template<typename Elem, typename Traits>
	SPRIG_INLINE typename basic_string_speck<Elem, Traits>::size_type str_length(
		basic_string_speck<Elem, Traits> const& str
		)
	{
		return str.size();
	}
	//
	// string_speck
	// wstring_speck
	//
	typedef basic_string_speck<char> string_speck;
	typedef basic_string_speck<wchar_t> wstring_speck;
}	// namespace sprig

#endif	// #ifndef SPRIG_STRING_PIECE_HPP
