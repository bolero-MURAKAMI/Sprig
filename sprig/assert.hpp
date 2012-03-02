
//
// SPRIG_ASSERT
//
#undef SPRIG_ASSERT

#if defined(SPRIG_DISABLE_ASSERTS)

#define SPRIG_ASSERT(expr) ((void)0)

#elif defined(SPRIG_ENABLE_ASSERT_HANDLER)

#include <boost/current_function.hpp>

namespace sprig {
	void assertion_failed(char const* expr, char const* function, char const* file, long line);
}	// namespace sprig

#define SPRIG_ASSERT(expr) ( \
	(expr) \
		? ((void)0) \
		: ::sprig::assertion_failed(#expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__) \
		)

#else

#include <boost/assert.hpp>

#define SPRIG_ASSERT(expr) BOOST_ASSERT(expr)

#endif

//
// SPRIG_VERIFY
//
#undef SPRIG_VERIFY

#if defined(SPRIG_DISABLE_ASSERTS) || (!defined(SPRIG_ENABLE_ASSERT_HANDLER) && defined(NDEBUG))

#define SPRIG_VERIFY(expr) ((void)(expr))

#else

#define SPRIG_VERIFY(expr) SPRIG_ASSERT(expr)

#endif
