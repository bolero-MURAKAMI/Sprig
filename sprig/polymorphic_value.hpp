#ifndef SPRIG_POLYMORPHIC_VALUE_HPP
#define SPRIG_POLYMORPHIC_VALUE_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <boost/type_traits/is_convertible.hpp>
#include <boost/cast.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/utility/enable_if.hpp>
#include <sprig/tag.hpp>

//
// SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_MAX
//
#ifndef SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_MAX
#	define SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_MAX 15
#endif

//
// SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM[_N]
//
#define SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM(GEN) \
	BOOST_PP_ENUM(SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_MAX, GEN, BOOST_PP_EMPTY())
#define SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM_N(N, GEN) \
	BOOST_PP_ENUM(N, GEN, BOOST_PP_EMPTY())

//
// SPRIG_MULTIPLE_POLYMORPHIC_VALUE_REPEAT[_N]
//
#define SPRIG_MULTIPLE_POLYMORPHIC_VALUE_REPEAT(GEN) \
	BOOST_PP_REPEAT(SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_MAX, GEN, BOOST_PP_EMPTY())
#define SPRIG_MULTIPLE_POLYMORPHIC_VALUE_REPEAT_N(N, GEN) \
	BOOST_PP_REPEAT(N, GEN, BOOST_PP_EMPTY())

//
// SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_GEN
// SPRIG_MULTIPLE_POLYMORPHIC_VALUE_TYPENAME_GEN
// SPRIG_MULTIPLE_POLYMORPHIC_VALUE_TYPENAME_VOID_GEN
// SPRIG_MULTIPLE_POLYMORPHIC_VALUE_EXTEND_GEN
// SPRIG_MULTIPLE_POLYMORPHIC_VALUE_BASE_GEN
//
#define SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_GEN(Z, N, D) VV##N
#define SPRIG_MULTIPLE_POLYMORPHIC_VALUE_TYPENAME_GEN(Z, N, D) typename VV##N
#define SPRIG_MULTIPLE_POLYMORPHIC_VALUE_TYPENAME_VOID_GEN(Z, N, D) typename VV##N = void
#define SPRIG_MULTIPLE_POLYMORPHIC_VALUE_EXTEND_GEN(Z, N, D) public boost::mpl::at_c<Sequence, N>::type
#define SPRIG_MULTIPLE_POLYMORPHIC_VALUE_BASE_GEN(Z, N, D) \
	template<typename Sequence> \
	class multiple_virtual_value_base< \
		Sequence, \
		typename boost::enable_if<multiple_virtual_value_base_overload_c<Sequence, BOOST_PP_INC(N)> >::type \
	> \
		: SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM_N(BOOST_PP_INC(N), SPRIG_MULTIPLE_POLYMORPHIC_VALUE_EXTEND_GEN) \
	{};

namespace sprig {
	//
	// polymorphic_value
	//
	class polymorphic_value {
	public:
		virtual ~polymorphic_value() {}
	};

	//
	// virtual_value_get_[value|pointer|const_pointer]_tag
	//
	struct virtual_value_get_value_tag {};
	struct virtual_value_get_pointer_tag {};
	struct virtual_value_get_const_pointer_tag {};

	//
	// virtual_value
	//
	template<typename T>
	class virtual_value
		: public polymorphic_value
	{
	public:
		typedef T value_type;
	public:
		virtual value_type operator()() = 0;
		virtual value_type operator()(virtual_value_get_value_tag) {
			return operator()();
		}
		virtual value_type* operator()(virtual_value_get_pointer_tag) {
			return 0;
		}
		virtual value_type const* operator()(virtual_value_get_const_pointer_tag) {
			return operator()(virtual_value_get_pointer_tag());
		}
	};

	//
	// tagged_virtual_value
	//
	template<typename T, typename Tag = T>
	class tagged_virtual_value
		: public virtual_value<T>
	{
	public:
		typedef Tag tag_type;
	};

	//
	// multiple_virtual_value_base_overload[_c]
	//
	template<typename Sequence, typename Size>
	struct multiple_virtual_value_base_overload
		: public boost::mpl::equal_to<
			typename boost::mpl::size<Sequence>::type,
			Size
		>::type
	{};
	template<typename Sequence, std::size_t N>
	struct multiple_virtual_value_base_overload_c
		: public multiple_virtual_value_base_overload<Sequence, boost::mpl::size_t<N> >
	{};

	//
	// multiple_virtual_value_base
	//
	template<typename Sequence, typename Enable = void>
	class multiple_virtual_value_base {};
	SPRIG_MULTIPLE_POLYMORPHIC_VALUE_REPEAT(SPRIG_MULTIPLE_POLYMORPHIC_VALUE_BASE_GEN);

	//
	// multiple_virtual_value_extend
	//
	template<SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM(SPRIG_MULTIPLE_POLYMORPHIC_VALUE_TYPENAME_GEN)>
	struct multiple_virtual_value_extend {
		typedef typename boost::mpl::remove<
			boost::mpl::vector<SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM(SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_GEN)>,
			void
		>::type sequence_type;
		typedef typename boost::mpl::at_c<sequence_type, 0>::type primary_type;
		typedef multiple_virtual_value_base<sequence_type> type;
	};

	//
	// multiple_virtual_value
	//
	template<SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM(SPRIG_MULTIPLE_POLYMORPHIC_VALUE_TYPENAME_VOID_GEN)>
	class multiple_virtual_value
		: public multiple_virtual_value_extend<
			SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM(SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_GEN)
		>::type
	{
	public:
		typename multiple_virtual_value_extend<
			SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM(SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_GEN)
		>::primary_type* upcast() {
			return this;
		}
	};

	//
	// multiple_virtual_value_tester
	//
	struct multiple_virtual_value_tester {
		template<SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM(SPRIG_MULTIPLE_POLYMORPHIC_VALUE_TYPENAME_GEN)>
		multiple_virtual_value_tester(
			multiple_virtual_value<
				SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ENUM(SPRIG_MULTIPLE_POLYMORPHIC_VALUE_ARGS_GEN)
			> const&
			);
	};

	//
	// is_multiple_virtual_value
	//
	template<typename T>
	struct is_multiple_virtual_value
		: public boost::is_convertible<T, multiple_virtual_value_tester>::type
	{};

	//
	// to_polymorphic_value
	//
	template<typename VV>
	SPRIG_INLINE typename boost::enable_if<is_multiple_virtual_value<VV>, polymorphic_value*>::type
	to_polymorphic_value(VV* vv) {
		return to_polymorphic_value(vv->upcast());
	}
	template<typename VV>
	SPRIG_INLINE typename boost::disable_if<is_multiple_virtual_value<VV>, polymorphic_value*>::type
	to_polymorphic_value(VV* vv) {
		return vv;
	}
	template<typename VV>
	SPRIG_INLINE typename boost::enable_if<is_multiple_virtual_value<VV>, polymorphic_value&>::type
	to_polymorphic_value(VV& vv) {
		return to_polymorphic_value(vv->upcast());
	}
	template<typename VV>
	SPRIG_INLINE typename boost::disable_if<is_multiple_virtual_value<VV>, polymorphic_value&>::type
	to_polymorphic_value(VV& vv) {
		return vv;
	}

	//
	// get
	//
	template<typename T>
	SPRIG_INLINE T get(polymorphic_value* pv) {
		return (*boost::polymorphic_cast<virtual_value<T>*>(pv))();
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T get(polymorphic_value* pv) {
		return (*boost::polymorphic_cast<tagged_virtual_value<T, Tag>*>(pv))();
	}
	template<typename T, int N>
	SPRIG_INLINE T get(polymorphic_value* pv) {
		return get<T, nth_tag<N> >(pv);
	}
	template<typename T>
	SPRIG_INLINE T get(polymorphic_value& pv) {
		return dynamic_cast<virtual_value<T>&>(pv)();
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T get(polymorphic_value& pv) {
		return dynamic_cast<tagged_virtual_value<T, Tag>&>(pv)();
	}
	template<typename T, int N>
	SPRIG_INLINE T get(polymorphic_value& pv) {
		return get<T, nth_tag<N> >(pv);
	}

	//
	// get_value
	//
	template<typename T>
	SPRIG_INLINE T get_value(polymorphic_value* pv) {
		return (*boost::polymorphic_cast<virtual_value<T>*>(pv))(virtual_value_get_value_tag());
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T get_value(polymorphic_value* pv) {
		return (*boost::polymorphic_cast<tagged_virtual_value<T, Tag>*>(pv))(virtual_value_get_value_tag());
	}
	template<typename T, int N>
	SPRIG_INLINE T get_value(polymorphic_value* pv) {
		return get_value<T, nth_tag<N> >(pv);
	}
	template<typename T>
	SPRIG_INLINE T get_value(polymorphic_value& pv) {
		return dynamic_cast<virtual_value<T>&>(pv)(virtual_value_get_value_tag());
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T get_value(polymorphic_value& pv) {
		return dynamic_cast<tagged_virtual_value<T, Tag>&>(pv)(virtual_value_get_value_tag());
	}
	template<typename T, int N>
	SPRIG_INLINE T get_value(polymorphic_value& pv) {
		return get_value<T, nth_tag<N> >(pv);
	}

	//
	// get_pointer
	//
	template<typename T>
	SPRIG_INLINE T* get_pointer(polymorphic_value* pv) {
		return (*boost::polymorphic_cast<virtual_value<T>*>(pv))(virtual_value_get_pointer_tag());
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T* get_pointer(polymorphic_value* pv) {
		return (*boost::polymorphic_cast<tagged_virtual_value<T, Tag>*>(pv))(virtual_value_get_pointer_tag());
	}
	template<typename T, int N>
	SPRIG_INLINE T* get_pointer(polymorphic_value* pv) {
		return get_pointer<T, nth_tag<N> >(pv);
	}
	template<typename T>
	SPRIG_INLINE T* get_pointer(polymorphic_value& pv) {
		return dynamic_cast<virtual_value<T>&>(pv)(virtual_value_get_pointer_tag());
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T* get_pointer(polymorphic_value& pv) {
		return dynamic_cast<tagged_virtual_value<T, Tag>&>(pv)(virtual_value_get_pointer_tag());
	}
	template<typename T, int N>
	SPRIG_INLINE T* get_pointer(polymorphic_value& pv) {
		return get_pointer<T, nth_tag<N> >(pv);
	}

	//
	// get_const_pointer
	//
	template<typename T>
	SPRIG_INLINE T const* get_const_pointer(polymorphic_value* pv) {
		return (*boost::polymorphic_cast<virtual_value<T>*>(pv))(virtual_value_get_const_pointer_tag());
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T const* get_const_pointer(polymorphic_value* pv) {
		return (*boost::polymorphic_cast<tagged_virtual_value<T, Tag>*>(pv))(virtual_value_get_const_pointer_tag());
	}
	template<typename T, int N>
	SPRIG_INLINE T const* get_const_pointer(polymorphic_value* pv) {
		return get_const_pointer<T, nth_tag<N> >(pv);
	}
	template<typename T>
	SPRIG_INLINE T const* get_const_pointer(polymorphic_value& pv) {
		return dynamic_cast<virtual_value<T>&>(pv)(virtual_value_get_const_pointer_tag());
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T const* get_const_pointer(polymorphic_value& pv) {
		return dynamic_cast<tagged_virtual_value<T, Tag>&>(pv)(virtual_value_get_const_pointer_tag());
	}
	template<typename T, int N>
	SPRIG_INLINE T const* get_const_pointer(polymorphic_value& pv) {
		return get_const_pointer<T, nth_tag<N> >(pv);
	}

	//
	// get_ref
	//
	template<typename T>
	SPRIG_INLINE T& get_ref(polymorphic_value* pv) {
		return *get_pointer<T>(pv);
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T& get_ref(polymorphic_value* pv) {
		return *get_pointer<T, Tag>(pv);
	}
	template<typename T, int N>
	SPRIG_INLINE T& get_ref(polymorphic_value* pv) {
		return get_ref<T, nth_tag<N> >(pv);
	}
	template<typename T>
	SPRIG_INLINE T& get_ref(polymorphic_value& pv) {
		return *get_pointer<T>(pv);
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T& get_ref(polymorphic_value& pv) {
		return *get_pointer<T, Tag>(pv);
	}
	template<typename T, int N>
	SPRIG_INLINE T& get_ref(polymorphic_value& pv) {
		return get_ref<T, nth_tag<N> >(pv);
	}

	//
	// get_cref
	//
	template<typename T>
	SPRIG_INLINE T const& get_cref(polymorphic_value* pv) {
		return *get_const_pointer<T>(pv);
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T const& get_cref(polymorphic_value* pv) {
		return *get_const_pointer<T, Tag>(pv);
	}
	template<typename T, int N>
	SPRIG_INLINE T const& get_cref(polymorphic_value* pv) {
		return get_cref<T, nth_tag<N> >(pv);
	}
	template<typename T>
	SPRIG_INLINE T const& get_cref(polymorphic_value& pv) {
		return *get_const_pointer<T>(pv);
	}
	template<typename T, typename Tag>
	SPRIG_INLINE T const& get_cref(polymorphic_value& pv) {
		return *get_const_pointer<T, Tag>(pv);
	}
	template<typename T, int N>
	SPRIG_INLINE T const& get_cref(polymorphic_value& pv) {
		return get_cref<T, nth_tag<N> >(pv);
	}
}	// namespace sprig

#endif	// #ifndef SPRIG_POLYMORPHIC_VALUE_HPP
