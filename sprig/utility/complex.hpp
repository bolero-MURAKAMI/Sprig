#ifndef SPRIG_UTILITY_COMPLEX_HPP
#define SPRIG_UTILITY_COMPLEX_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <complex>
#include <iosfwd>
#include <boost/call_traits.hpp>
#include <sprig/reference_holder.hpp>
#include <sprig/split_literal.hpp>

namespace sprig {
	//
	// complex_io_wrapper
	//
	template<typename T, typename Complex = std::complex<T> >
	class complex_io_wrapper {
	public:
		typedef T element_type;
		typedef Complex value_type;
		typedef reference_holder<value_type> holder_type;
	private:
		holder_type target_;
	public:
		static typename boost::call_traits<element_type>::param_type element_zero() {
			static element_type const zero = element_type(0);
			return zero;
		}
	public:
		explicit complex_io_wrapper(value_type& target)
			: target_(target)
		{}
		value_type& get() {
			return target_;
		}
		value_type const& get() const {
			return target_;
		}
		value_type& operator*() {
			return *target_;
		}
		value_type const& operator*() const {
			return *target_;
		}
		value_type* operator->() {
			return target_.get_pointer();
		}
		value_type const* operator->() const {
			return target_.get_pointer();
		}
	};
	namespace complex_io_detail {
		SPRIG_SPLIT_LITERAL_CHAR_DECL(lp, '(');
		SPRIG_SPLIT_LITERAL_CHAR_DECL(rp, ')');
		SPRIG_SPLIT_LITERAL_CHAR_DECL(plus, '+');
		SPRIG_SPLIT_LITERAL_CHAR_DECL(i, 'i');
	}	// namespace complex_io_detail
	//
	// operator<<
	//
	template<typename Elem, typename Traits, typename T, typename Complex>
	SPRIG_INLINE std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& lhs,
		complex_io_wrapper<T, Complex> const& rhs
		)
	{
		typedef complex_io_wrapper<T, Complex> wrapper_type;
		if (rhs->real() != wrapper_type::element_zero()) {
			lhs
				<< sprig::apply_literal<complex_io_detail::lp, Elem>::value
				<< rhs->real()
				;
		}
		if (rhs->imag() != wrapper_type::element_zero()) {
			if (rhs->imag() > wrapper_type::element_zero()) {
				lhs
					<< sprig::apply_literal<complex_io_detail::plus, Elem>::value
					;
			}
			lhs
				<< rhs->imag()
				<< sprig::apply_literal<complex_io_detail::i, Elem>::value
				<< sprig::apply_literal<complex_io_detail::rp, Elem>::value
				;
		}
		return lhs;
	}

	//
	// io
	//
	template<typename T>
	SPRIG_INLINE complex_io_wrapper<T> io(std::complex<T>& target) {
		return complex_io_wrapper<T>(target);
	}
	template<typename T>
	SPRIG_INLINE complex_io_wrapper<T, std::complex<T> const> io(std::complex<T> const& target) {
		return complex_io_wrapper<T, std::complex<T> const>(target);
	}
} // namespace sprig

#endif	// #ifndef SPRIG_UTILITY_COMPLEX_HPP
