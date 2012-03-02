#ifndef SPRIG_UCK_FUN_FUN_MANAGER_HPP
#define SPRIG_UCK_FUN_FUN_MANAGER_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/optional/optional.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <sprig/singleton.hpp>
#include <sprig/utility/iterator.hpp>
#include <sprig/uck/traits.hpp>
#include <sprig/uck/types.hpp>
#include <sprig/uck/std/std_types.hpp>
#include <sprig/uck/fun/fun_types.hpp>

namespace sprig {
	namespace uck {
		//
		// fun_manager
		//
		template<typename Traits = traits<> >
		struct fun_manager
			: public sprig::singleton<fun_manager<Traits> >
		{
			SPRIG_FRIEND_SINGLETON(fun_manager<Traits>);
		public:
			typedef Traits traits_type;
			typedef types<traits_type> types_type;
			typedef std_types<traits_type> std_types_type;
			typedef fun_types<traits_type> fun_types_type;
		private:
			template<typename ArgIterator, typename NameIterator>
			static bool is_match_name(
				ArgIterator arg_first,
				ArgIterator arg_last,
				NameIterator name_first,
				NameIterator name_last
				)
			{
				typename boost::iterator_difference<ArgIterator>::type arg_diff
					= std::distance(arg_first, arg_last);
				typename boost::iterator_difference<NameIterator>::type name_diff
					= std::distance(name_first, name_last);
				return
					arg_diff < name_diff
					|| std::search(sprig::get_advance(arg_first, arg_diff - name_diff), arg_last, name_first, name_last) == arg_last
						? false
						: true
					;
			}
		private:
			typename fun_types_type::library_type library_;
			boost::optional<typename fun_types_type::function_type> function_;
			typename fun_types_type::arguments_type arguments_;
		private:
			fun_manager() {}
			~fun_manager() {}
		public:
			bool attach(
				typename fun_types_type::name_type const& name,
				typename fun_types_type::package_type::const_iterator first,
				typename fun_types_type::package_type::const_iterator last
				)
			{
				if (!library_.insert(typename fun_types_type::library_type::value_type(name, typename fun_types_type::package_type())).second) {
					return false;
				}
				typename fun_types_type::package_type& lib = library_[name];
				for (typename fun_types_type::package_type::const_iterator i = first; i != last; ++i) {
					lib[i->first] = i->second;
				}
				return true;
			}
			bool detach(typename fun_types_type::name_type const& name) {
				return library_.erase(name) != 0;
			}
			bool push(
				typename std_types_type::output_argument_type arg_first,
				typename std_types_type::output_argument_type arg_last,
				typename std_types_type::work_argument_type work_first,
				typename std_types_type::work_argument_type work_last
				)
			{
				if (function_) {
					arguments_.push_back(typename fun_types_type::argument_type(arg_first, arg_last));
				} else {
					BOOST_FOREACH(typename fun_types_type::library_type::value_type const& le, library_) {
						BOOST_FOREACH(typename fun_types_type::package_type::value_type const& e, le.second) {
							if (is_match_name(arg_first, arg_last, e.first.begin(), e.first.end())) {
								function_ = e.second;
								break;
							}
						}
						if (function_) {
							break;
						}
					}
					if (!function_) {
						return false;
					}
				}
				return true;
			}
			bool call(
				typename std_types_type::input_argument_type res_first,
				typename std_types_type::input_argument_type res_last,
				typename std_types_type::work_argument_type work_first,
				typename std_types_type::work_argument_type work_last
				)
			{
				if (!function_) {
					return false;
				}
				(*function_)(
					arguments_.begin(),
					arguments_.end(),
					res_first,
					res_last,
					work_first,
					work_last
					);
				function_.reset();
				arguments_.clear();
				return true;
			}
		};
	}	// namespace uck
}	// namespace sprig

#endif	// #ifndef SPRIG_UCK_FUN_FUN_MANAGER_HPP
