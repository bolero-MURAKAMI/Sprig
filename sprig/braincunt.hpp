#ifndef SPRIG_BRAINCUNT_HPP
#define SPRIG_BRAINCUNT_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <cstddef>
#include <cstring>
#include <cstdio>
#include <string>
#include <utility>
#include <deque>
#include <algorithm>
#include <iterator>
#include <functional>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/swap.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <sprig/assert.hpp>
#include <sprig/exception.hpp>
#include <sprig/type_traits/is_derived_basic_istream.hpp>
#include <sprig/serialization/boost/tuple.hpp>

namespace sprig {
	namespace braincunt {
		//
		// base_exception
		//
		SPRIG_EXCEPTION_DECL(base_exception);
		//
		// code_ended
		//
		SPRIG_EXCEPTION_INHERIT_DECL(code_ended, base_exception);
		//
		// open_paren_not_found
		// closed_paren_not_found
		//
		SPRIG_EXCEPTION_INHERIT_DECL(open_paren_not_found, base_exception);
		SPRIG_EXCEPTION_INHERIT_DECL(closed_paren_not_found, base_exception);
		//
		// engine
		//
		class engine {
		public:
			typedef char char_type;
			typedef unsigned char byte_type;
			typedef std::size_t size_type;
			typedef std::basic_string<char_type> pbuffer_type;
			typedef pbuffer_type::size_type ppointer_type;
			typedef std::deque<byte_type> dx_type;
			typedef std::pair<dx_type, size_type> dxbuffer_type;
			typedef dx_type::difference_type dxpointer_type;
			typedef std::deque<dxbuffer_type> dxy_type;
			typedef std::pair<dxy_type, size_type> dxybuffer_type;
			typedef dxy_type::difference_type dypointer_type;
			typedef std::deque<dxybuffer_type> dxyz_type;
			typedef std::pair<dxyz_type, size_type> dxyzbuffer_type;
			typedef dxyz_type::difference_type dzpointer_type;
			typedef dxyzbuffer_type dbuffer_type;
			typedef boost::tuple<
				dxpointer_type,
				dypointer_type,
				dzpointer_type
			> dpointer_type;
		public:
			enum axis_direction {
				x_axis_direction = 0,
				y_axis_direction = 1,
				z_axis_direction = 2
			};
			enum axis_index {
				x_axis = 0,
				y_axis = 1,
				z_axis = 2
			};
			typedef std::pair<axis_direction, bool> direction_type;
		public:
			class output_function
				: public std::unary_function<byte_type, void>
			{
			private:
				friend class boost::serialization::access;
				template<typename Archive>
				void serialize(
					Archive& ar,
					unsigned int const
					)
				{}
			public:
				virtual ~output_function() {}
				virtual void operator()(byte_type) const = 0;
			};
			class input_function
				: public std::unary_function<void, byte_type>
			{
			private:
				friend class boost::serialization::access;
				template<typename Archive>
				void serialize(
					Archive& ar,
					unsigned int const
					)
				{}
			public:
				virtual ~input_function() {}
				virtual byte_type operator()() const = 0;
			};
			typedef boost::shared_ptr<output_function> output_type;
			typedef boost::shared_ptr<input_function> input_type;
		public:
			class default_output
				: public output_function
			{
			private:
				friend class boost::serialization::access;
				template<typename Archive>
				void serialize(
					Archive& ar,
					unsigned int const
					)
				{
					ar
						& boost::serialization::make_nvp(
							"output_function",
							boost::serialization::base_object<output_function>(*this)
							)
						;
				}
			public:
				virtual void operator()(byte_type b) const {
					std::putchar(b);
				}
			};
			class default_input
				: public input_function
			{
			private:
				friend class boost::serialization::access;
				template<typename Archive>
				void serialize(
					Archive& ar,
					unsigned int const
					)
				{
					ar
						& boost::serialization::make_nvp(
							"input_function",
							boost::serialization::base_object<input_function>(*this)
							)
						;
				}
			public:
				virtual byte_type operator()() const {
					char c = 0;
					do {
						c = std::getchar();
					} while (c == '\n');
					return c;
				}
			};
		private:
			pbuffer_type pbuffer_;
			dbuffer_type dbuffer_;
			ppointer_type ppointer_;
			dpointer_type dpointer_;
			direction_type front_;
			direction_type head_;
			bool pure_;
			bool ext_bitwise_;
			bool ext_arithmetic_;
			bool ext_copyswap_;
			bool ext_axis_;
			bool ext_comment_;
			output_type output_;
			input_type input_;
		private:
			friend class boost::serialization::access;
			template<typename Archive>
			void serialize(
				Archive& ar,
				unsigned int const version
				)
			{
				ar
					& boost::serialization::make_nvp("pbuffer", pbuffer_)
					& boost::serialization::make_nvp("dbuffer", dbuffer_)
					& boost::serialization::make_nvp("ppointer", ppointer_)
					& boost::serialization::make_nvp("dpointer", dpointer_)
					& boost::serialization::make_nvp("front", front_)
					& boost::serialization::make_nvp("head", head_)
					& boost::serialization::make_nvp("pure", pure_)
					& boost::serialization::make_nvp("ext_bitwise", ext_bitwise_)
					& boost::serialization::make_nvp("ext_arithmetic", ext_arithmetic_)
					& boost::serialization::make_nvp("ext_copyswap", ext_copyswap_)
					& boost::serialization::make_nvp("ext_axis", ext_axis_)
					& boost::serialization::make_nvp("ext_comment", ext_comment_)
					;
				if (version >= 1) {
					ar
						& boost::serialization::make_nvp("output", output_)
						& boost::serialization::make_nvp("input", input_)
						;
				}
			}
		public:
			engine()
				: pbuffer_()
				, dbuffer_()
				, ppointer_()
				, dpointer_()
				, front_(x_axis_direction, false)
				, head_(z_axis_direction, false)
				, pure_(false)
				, ext_bitwise_(false)
				, ext_arithmetic_(false)
				, ext_copyswap_(false)
				, ext_axis_(false)
				, ext_comment_(false)
				, output_(boost::make_shared<engine::default_output>())
				, input_(boost::make_shared<engine::default_input>())
			{}
			engine& operator=(engine const& other) {
				engine temp(other);
				temp.swap(*this);
				return *this;
			}
			void swap(engine& other) {
				boost::swap(pbuffer_, other.pbuffer_);
				boost::swap(dbuffer_, other.dbuffer_);
				boost::swap(ppointer_, other.ppointer_);
				boost::swap(dpointer_, other.dpointer_);
				boost::swap(front_, other.front_);
				boost::swap(head_, other.head_);
				boost::swap(pure_, other.pure_);
				boost::swap(ext_bitwise_, other.ext_bitwise_);
				boost::swap(ext_arithmetic_, other.ext_arithmetic_);
				boost::swap(ext_copyswap_, other.ext_copyswap_);
				boost::swap(ext_axis_, other.ext_axis_);
				boost::swap(ext_comment_, other.ext_comment_);
				boost::swap(output_, other.output_);
				boost::swap(input_, other.input_);
			}
			//
			//	COMMENT: アクセス実装
			//
			char_type const& at(ppointer_type pp) const {
				return pbuffer_.at(pp);
			}
			char_type& at(ppointer_type pp) {
				return pbuffer_.at(pp);
			}
			byte_type const& at(dpointer_type const& dp) const {
				dxyzbuffer_type const& dxyzbuffer = dbuffer_;
				dxybuffer_type const& dxybuffer = dxyzbuffer.first.at(dp.get<z_axis>() + dxyzbuffer.second);
				dxbuffer_type const& dxbuffer = dxybuffer.first.at(dp.get<y_axis>() + dxybuffer.second);
				return dxbuffer.first.at(dp.get<x_axis>() + dxbuffer.second);
			}
			byte_type& at(dpointer_type const& dp) {
				dxyzbuffer_type& dxyzbuffer = dbuffer_;
				dxybuffer_type& dxybuffer = dxyzbuffer.first.at(dp.get<z_axis>() + dxyzbuffer.second);
				dxbuffer_type& dxbuffer = dxybuffer.first.at(dp.get<y_axis>() + dxybuffer.second);
				return dxbuffer.first.at(dp.get<x_axis>() + dxbuffer.second);
			}
			bool is_out_of_bounds_pbuffer(ppointer_type pp) const {
				return pp >= pbuffer_.size();
			}
			bool is_out_of_bounds_pbuffer() const {
				return is_out_of_bounds_pbuffer(ppointer_);
			}
			bool is_out_of_bounds_dbuffer(dpointer_type const& dp) const {
				dxyzbuffer_type const& dxyzbuffer = dbuffer_;
				if (dp.get<z_axis>() + dxyzbuffer.second >= dxyzbuffer.first.size()) {
					return true;
				}
				dxybuffer_type const& dxybuffer = dxyzbuffer.first.at(dp.get<z_axis>() + dxyzbuffer.second);
				if (dp.get<y_axis>() + dxybuffer.second >= dxybuffer.first.size()) {
					return true;
				}
				dxbuffer_type const& dxbuffer = dxybuffer.first.at(dp.get<y_axis>() + dxybuffer.second);
				if (dp.get<x_axis>() + dxbuffer.second >= dxbuffer.first.size()) {
					return true;
				}
				return false;
			}
			bool is_out_of_bounds_dbuffer() const {
				return is_out_of_bounds_dbuffer(dpointer_);
			}
			void expand_dbuffer(dpointer_type const& dp) {
				dxyzbuffer_type& dxyzbuffer = dbuffer_;
				dxyz_type& dxyz = dxyzbuffer.first;
				if (dp.get<z_axis>() >= 0) {
					if (dxyz.size() <= dxyzbuffer.second + dp.get<z_axis>()) {
						dxyz.insert(
							dxyz.end(),
							dxyzbuffer.second + dp.get<z_axis>() + 1 - dxyz.size(),
							dxyz_type::value_type()
							);
					}
				} else {
					if (dxyzbuffer.second < static_cast<size_type>(-dp.get<z_axis>())) {
						dxyz.insert(
							dxyz.begin(),
							-dp.get<z_axis>() - dxyzbuffer.second,
							dxyz_type::value_type()
							);
						dxyzbuffer.second = static_cast<size_type>(-dp.get<z_axis>());
					}
				}
				dxybuffer_type& dxybuffer = dxyz.at(dp.get<z_axis>() + dxyzbuffer.second);
				dxy_type& dxy = dxybuffer.first;
				if (dp.get<y_axis>() >= 0) {
					if (dxy.size() - dxybuffer.second <= static_cast<size_type>(dp.get<y_axis>())) {
						dxy.insert(
							dxy.end(),
							dxybuffer.second + dp.get<y_axis>() + 1 - dxy.size(),
							dxy_type::value_type()
							);
					}
				} else {
					if (dxybuffer.second < static_cast<size_type>(-dp.get<y_axis>())) {
						dxy.insert(
							dxy.begin(),
							-dp.get<y_axis>() - dxybuffer.second,
							dxy_type::value_type()
							);
						dxybuffer.second = static_cast<size_type>(-dp.get<y_axis>());
					}
				}
				dxbuffer_type& dxbuffer = dxy.at(dp.get<y_axis>() + dxybuffer.second);
				dx_type& dx = dxbuffer.first;
				if (dp.get<x_axis>() >= 0) {
					if (dx.size() - dxbuffer.second <= static_cast<size_type>(dp.get<x_axis>())) {
						dx.insert(
							dx.end(),
							dxbuffer.second + dp.get<x_axis>() + 1 - dx.size(),
							dx_type::value_type()
							);
					}
				} else {
					if (dxbuffer.second < static_cast<size_type>(-dp.get<x_axis>())) {
						dx.insert(
							dx.begin(),
							-dp.get<x_axis>() - dxbuffer.second,
							dx_type::value_type()
							);
						dxbuffer.second = static_cast<size_type>(-dp.get<x_axis>());
					}
				}
			}
			void expand_dbuffer() {
				expand_dbuffer(dpointer_);
			}
			//
			//	COMMENT: 処理実装
			//
			void dinc(dpointer_type& dp) const {
				switch (front_.first) {
				case x_axis_direction:
					front_.second
						? --dp.get<x_axis>()
						: ++dp.get<x_axis>()
						;
					break;
				case y_axis_direction:
					front_.second
						? --dp.get<y_axis>()
						: ++dp.get<y_axis>()
						;
					break;
				case z_axis_direction:
					front_.second
						? --dp.get<z_axis>()
						: ++dp.get<z_axis>()
						;
					break;
				}
			}
			void dinc() {
				dinc(dpointer_);
			}
			void ddec(dpointer_type& dp) const {
				switch (front_.first) {
				case x_axis_direction:
					front_.second
						? ++dp.get<x_axis>()
						: --dp.get<x_axis>()
						;
					break;
				case y_axis_direction:
					front_.second
						? ++dp.get<y_axis>()
						: --dp.get<y_axis>()
						;
					break;
				case z_axis_direction:
					front_.second
						? ++dp.get<z_axis>()
						: --dp.get<z_axis>()
						;
					break;
				}
			}
			void ddec() {
				ddec(dpointer_);
			}
			void inc(dpointer_type& dp) {
				expand_dbuffer(dp);
				++at(dp);
			}
			void inc() {
				inc(dpointer_);
			}
			void dec(dpointer_type& dp) {
				expand_dbuffer(dp);
				--at(dp);
			}
			void dec() {
				dec(dpointer_);
			}
			void out(dpointer_type& dp) {
				expand_dbuffer(dp);
				(*output_)(at(dp));
			}
			void out() {
				out(dpointer_);
			}
			void in(dpointer_type& dp) {
				expand_dbuffer(dp);
				at(dp) = (*input_)();
			}
			void in() {
				in(dpointer_);
			}
			void lparen(dpointer_type& dp) {
				expand_dbuffer(dp);
				if (!at(dp)) {
					ppointer_type ppointer = ppointer_;
					std::ptrdiff_t count = 1;
					do {
						if (ppointer + 1 >= pbuffer_.size()) {
							SPRIG_THROW_EXCEPTION(closed_paren_not_found("closed paren not found: on operator \'[\'"));
						}
						++ppointer;
						switch (pbuffer_[ppointer]) {
						case '[':
							++count;
							break;
						case ']':
							--count;
							break;
						}
					} while (count);
					ppointer_ = ppointer;
				}
			}
			void lparen() {
				lparen(dpointer_);
			}
			void rparen(dpointer_type& dp) {
				expand_dbuffer(dp);
				if (at(dp)) {
					ppointer_type ppointer = ppointer_;
					std::ptrdiff_t count = -1;
					do {
						if (ppointer <= 0) {
							SPRIG_THROW_EXCEPTION(open_paren_not_found("open paren not found: on operator \']\'"));
						}
						--ppointer;
						switch (pbuffer_[ppointer]) {
						case '[':
							++count;
							break;
						case ']':
							--count;
							break;
						}
					} while (count);
					ppointer_ = ppointer - 1;
				}
			}
			void rparen() {
				rparen(dpointer_);
			}
			void lroll() {
				switch (front_.first) {
				case x_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						SPRIG_ASSERT(0);
					case y_axis_direction:
						head_ = direction_type(z_axis_direction, head_.second);
						break;
					case z_axis_direction:
						head_ = direction_type(y_axis_direction, !head_.second);
						break;
					}
					break;
				case y_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						head_ = direction_type(z_axis_direction, !head_.second);
						break;
					case y_axis_direction:
						SPRIG_ASSERT(0);
					case z_axis_direction:
						head_ = direction_type(x_axis_direction, head_.second);
						break;
					}
					break;
				case z_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						head_ = direction_type(y_axis_direction, head_.second);
						break;
					case y_axis_direction:
						head_ = direction_type(x_axis_direction, !head_.second);
						break;
					case z_axis_direction:
						SPRIG_ASSERT(0);
					}
					break;
				}
			}
			void rroll() {
				switch (front_.first) {
				case x_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						SPRIG_ASSERT(0);
					case y_axis_direction:
						head_ = direction_type(z_axis_direction, !head_.second);
						break;
					case z_axis_direction:
						head_ = direction_type(y_axis_direction, head_.second);
						break;
					}
					break;
				case y_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						head_ = direction_type(z_axis_direction, head_.second);
						break;
					case y_axis_direction:
						SPRIG_ASSERT(0);
					case z_axis_direction:
						head_ = direction_type(x_axis_direction, !head_.second);
						break;
					}
					break;
				case z_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						head_ = direction_type(y_axis_direction, !head_.second);
						break;
					case y_axis_direction:
						head_ = direction_type(x_axis_direction, head_.second);
						break;
					case z_axis_direction:
						SPRIG_ASSERT(0);
					}
					break;
				}
			}
			void lyaw() {
				switch (front_.first) {
				case x_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						SPRIG_ASSERT(0);
					case y_axis_direction:
						front_ = direction_type(z_axis_direction, !front_.second);
						break;
					case z_axis_direction:
						front_ = direction_type(y_axis_direction, front_.second);
						break;
					}
					break;
				case y_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						front_ = direction_type(z_axis_direction, front_.second);
						break;
					case y_axis_direction:
						SPRIG_ASSERT(0);
					case z_axis_direction:
						front_ = direction_type(x_axis_direction, !front_.second);
						break;
					}
					break;
				case z_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						front_ = direction_type(y_axis_direction, !front_.second);
						break;
					case y_axis_direction:
						front_ = direction_type(x_axis_direction, front_.second);
						break;
					case z_axis_direction:
						SPRIG_ASSERT(0);
					}
					break;
				}
			}
			void ryaw() {
				switch (front_.first) {
				case x_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						SPRIG_ASSERT(0);
					case y_axis_direction:
						front_ = direction_type(z_axis_direction, front_.second);
						break;
					case z_axis_direction:
						front_ = direction_type(y_axis_direction, !front_.second);
						break;
					}
					break;
				case y_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						front_ = direction_type(z_axis_direction, !front_.second);
						break;
					case y_axis_direction:
						SPRIG_ASSERT(0);
					case z_axis_direction:
						front_ = direction_type(x_axis_direction, front_.second);
						break;
					}
					break;
				case z_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						front_ = direction_type(y_axis_direction, front_.second);
						break;
					case y_axis_direction:
						front_ = direction_type(x_axis_direction, !front_.second);
						break;
					case z_axis_direction:
						SPRIG_ASSERT(0);
					}
					break;
				}
			}
			void upitch() {
				bool front_second = front_.second;
				switch (front_.first) {
				case x_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						SPRIG_ASSERT(0);
					case y_axis_direction:
						front_ = direction_type(y_axis_direction, head_.second);
						head_ = direction_type(x_axis_direction, !front_second);
						break;
					case z_axis_direction:
						front_ = direction_type(z_axis_direction, head_.second);
						head_ = direction_type(x_axis_direction, !front_second);
						break;
					}
					break;
				case y_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						front_ = direction_type(x_axis_direction, head_.second);
						head_ = direction_type(y_axis_direction, !front_second);
						break;
					case y_axis_direction:
						SPRIG_ASSERT(0);
					case z_axis_direction:
						front_ = direction_type(z_axis_direction, head_.second);
						head_ = direction_type(y_axis_direction, !front_second);
						break;
					}
					break;
				case z_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						front_ = direction_type(x_axis_direction, head_.second);
						head_ = direction_type(z_axis_direction, !front_second);
						break;
					case y_axis_direction:
						front_ = direction_type(y_axis_direction, head_.second);
						head_ = direction_type(z_axis_direction, !front_second);
						break;
					case z_axis_direction:
						SPRIG_ASSERT(0);
					}
					break;
				}
			}
			void dpitch() {
				bool front_second = front_.second;
				switch (front_.first) {
				case x_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						SPRIG_ASSERT(0);
					case y_axis_direction:
						front_ = direction_type(y_axis_direction, !head_.second);
						head_ = direction_type(x_axis_direction, front_second);
						break;
					case z_axis_direction:
						front_ = direction_type(z_axis_direction, !head_.second);
						head_ = direction_type(x_axis_direction, front_second);
						break;
					}
					break;
				case y_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						front_ = direction_type(x_axis_direction, !head_.second);
						head_ = direction_type(y_axis_direction, front_second);
						break;
					case y_axis_direction:
						SPRIG_ASSERT(0);
					case z_axis_direction:
						front_ = direction_type(z_axis_direction, !head_.second);
						head_ = direction_type(y_axis_direction, front_second);
						break;
					}
					break;
				case z_axis_direction:
					switch (head_.first) {
					case x_axis_direction:
						front_ = direction_type(x_axis_direction, !head_.second);
						head_ = direction_type(z_axis_direction, front_second);
						break;
					case y_axis_direction:
						front_ = direction_type(y_axis_direction, !head_.second);
						head_ = direction_type(z_axis_direction, front_second);
						break;
					case z_axis_direction:
						SPRIG_ASSERT(0);
					}
					break;
				}
			}
			//
			//	COMMENT: 拡張処理実装（ビット演算）
			//
			void bit_or(dpointer_type& dp) {
				dpointer_type prev_dp = dp;
				dinc(dp);
				expand_dbuffer(dp);
				expand_dbuffer(prev_dp);
				at(dp) |= at(prev_dp);
			}
			void bit_or() {
				bit_or(dpointer_);
			}
			void bit_and(dpointer_type& dp) {
				dpointer_type prev_dp = dp;
				dinc(dp);
				expand_dbuffer(dp);
				expand_dbuffer(prev_dp);
				at(dp) &= at(prev_dp);
			}
			void bit_and() {
				bit_and(dpointer_);
			}
			void bit_xor(dpointer_type& dp) {
				dpointer_type prev_dp = dp;
				dinc(dp);
				expand_dbuffer(dp);
				expand_dbuffer(prev_dp);
				at(dp) ^= at(prev_dp);
			}
			void bit_xor() {
				bit_xor(dpointer_);
			}
			void bit_not(dpointer_type const& dp) {
				expand_dbuffer(dp);
				at(dp) = ~at(dp);
			}
			void bit_not() {
				bit_not(dpointer_);
			}
			//
			//	COMMENT: 拡張処理実装（算術演算）
			//
			void add(dpointer_type& dp) {
				dpointer_type prev_dp = dp;
				dinc(dp);
				expand_dbuffer(dp);
				expand_dbuffer(prev_dp);
				at(dp) += at(prev_dp);
			}
			void add() {
				add(dpointer_);
			}
			void sub(dpointer_type& dp) {
				dpointer_type prev_dp = dp;
				dinc(dp);
				expand_dbuffer(dp);
				expand_dbuffer(prev_dp);
				at(dp) -= at(prev_dp);
			}
			void sub() {
				sub(dpointer_);
			}
			void mul(dpointer_type& dp) {
				dpointer_type prev_dp = dp;
				dinc(dp);
				expand_dbuffer(dp);
				expand_dbuffer(prev_dp);
				at(dp) *= at(prev_dp);
			}
			void mul() {
				mul(dpointer_);
			}
			void div(dpointer_type& dp) {
				dpointer_type prev_dp = dp;
				dinc(dp);
				expand_dbuffer(dp);
				expand_dbuffer(prev_dp);
				at(dp) /= at(prev_dp);
			}
			void div() {
				div(dpointer_);
			}
			void mod(dpointer_type& dp) {
				dpointer_type prev_dp = dp;
				dinc(dp);
				expand_dbuffer(dp);
				expand_dbuffer(prev_dp);
				at(dp) %= at(prev_dp);
			}
			void mod() {
				mod(dpointer_);
			}
			//
			//	COMMENT: 拡張処理実装（コピー・交換）
			//
			void dcopy(dpointer_type& dp) {
				dpointer_type prev_dp = dp;
				dinc(dp);
				expand_dbuffer(dp);
				expand_dbuffer(prev_dp);
				at(dp) = at(prev_dp);
			}
			void dcopy() {
				dcopy(dpointer_);
			}
			void dswap(dpointer_type& dp) {
				using std::swap;
				dpointer_type prev_dp = dp;
				dinc(dp);
				expand_dbuffer(dp);
				expand_dbuffer(prev_dp);
				swap(at(dp), at(prev_dp));
			}
			void dswap() {
				dswap(dpointer_);
			}
			//
			//	COMMENT: 拡張処理実装（軸移動）
			//
			void x_dinc(dpointer_type& dp) const {
				++dp.get<x_axis>();
			}
			void x_dinc() {
				x_dinc(dpointer_);
			}
			void x_ddec(dpointer_type& dp) const {
				--dp.get<x_axis>();
			}
			void x_ddec() {
				x_ddec(dpointer_);
			}
			void y_dinc(dpointer_type& dp) const {
				++dp.get<y_axis>();
			}
			void y_dinc() {
				y_dinc(dpointer_);
			}
			void y_ddec(dpointer_type& dp) const {
				--dp.get<y_axis>();
			}
			void y_ddec() {
				y_ddec(dpointer_);
			}
			void z_dinc(dpointer_type& dp) const {
				++dp.get<z_axis>();
			}
			void z_dinc() {
				z_dinc(dpointer_);
			}
			void z_ddec(dpointer_type& dp) const {
				--dp.get<z_axis>();
			}
			void z_ddec() {
				z_ddec(dpointer_);
			}
			//
			//	COMMENT: 実行
			//
			bool is_code_end() const {
				return is_out_of_bounds_pbuffer();
			}
			bool is_basic_pure_command(byte_type command) const {
				return command == '>'
					|| command == '<'
					|| command == '+'
					|| command == '-'
					|| command == '.'
					|| command == ','
					|| command == '['
					|| command == ']'
					;
			}
			bool execute_basic_pure(byte_type command) {
				switch (command) {
				case '>':
					dinc();
					break;
				case '<':
					ddec();
					break;
				case '+':
					inc();
					break;
				case '-':
					dec();
					break;
				case '.':
					out();
					break;
				case ',':
					in();
					break;
				case '[':
					lparen();
					break;
				case ']':
					rparen();
					break;
				default:
					return false;
				}
				return true;
			}
			bool is_basic_no_pure_command(byte_type command) const {
				return command == 'r'
					|| command == 'R'
					|| command == 'y'
					|| command == 'Y'
					|| command == 'p'
					|| command == 'P'
					;
			}
			bool execute_basic_no_pure(byte_type command) {
				switch (command) {
				case 'r':
					lroll();
					break;
				case 'R':
					rroll();
					break;
				case 'y':
					lyaw();
					break;
				case 'Y':
					ryaw();
					break;
				case 'p':
					upitch();
					break;
				case 'P':
					dpitch();
					break;
				default:
					return false;
				}
				return true;
			}
			bool is_basic_command(byte_type command) const {
				return is_basic_pure_command(command)
					|| is_basic_no_pure_command(command)
					;
			}
			bool execute_basic(byte_type command) {
				return execute_basic_pure(command)
					|| execute_basic_no_pure(command)
					;
			}
			bool is_ext_bitwise_command(byte_type command) const {
				return command == '|'
					|| command == '&'
					|| command == '^'
					|| command == '~'
					;
			}
			bool execute_ext_bitwise(byte_type command) {
				switch (command) {
				case '|':
					bit_or();
					break;
				case '&':
					bit_and();
					break;
				case '^':
					bit_xor();
					break;
				case '~':
					bit_not();
					break;
				default:
					return false;
				}
				return true;
			}
			bool is_ext_arithmetic_command(byte_type command) const {
				return command == ':'
					|| command == ';'
					|| command == '*'
					|| command == '/'
					|| command == '%'
					;
			}
			bool execute_ext_arithmetic(byte_type command) {
				switch (command) {
				case ':':
					add();
					break;
				case ';':
					sub();
					break;
				case '*':
					mul();
					break;
				case '/':
					div();
					break;
				case '%':
					mod();
					break;
				default:
					return false;
				}
				return true;
			}
			bool is_ext_copyswap_command(byte_type command) const {
				return command == '='
					|| command == '`'
					;
			}
			bool execute_ext_copyswap(byte_type command) {
				switch (command) {
				case '=':
					dcopy();
					break;
				case '`':
					dswap();
					break;
				default:
					return false;
				}
				return true;
			}
			bool is_ext_axis_command(byte_type command) const {
				return command == 'a'
					|| command == 'A'
					|| command == 'b'
					|| command == 'B'
					|| command == 'c'
					|| command == 'C'
					;
			}
			bool execute_ext_axis(byte_type command) {
				switch (command) {
				case 'a':
					x_dinc();
					break;
				case 'A':
					x_ddec();
					break;
				case 'b':
					y_dinc();
					break;
				case 'B':
					y_ddec();
					break;
				case 'c':
					z_dinc();
					break;
				case 'C':
					z_ddec();
					break;
				default:
					return false;
				}
				return true;
			}
			bool is_command(byte_type command) const {
				return pure_
					? is_basic_pure_command(command)
					: is_basic_command(command)
					|| ext_bitwise_ && is_ext_bitwise_command(command)
					|| ext_arithmetic_ && is_ext_arithmetic_command(command)
					|| ext_copyswap_ && is_ext_copyswap_command(command)
					|| ext_axis_ && is_ext_axis_command(command)
					;
			}
			bool execute(byte_type command) {
				return pure_
					? execute_basic_pure(command)
					: execute_basic(command)
					|| ext_bitwise_ && execute_ext_bitwise(command)
					|| ext_arithmetic_ && execute_ext_arithmetic(command)
					|| ext_copyswap_ && execute_ext_copyswap(command)
					|| ext_axis_ && execute_ext_axis(command)
					;
			}
			bool is_command() const {
				if (is_code_end()) {
					SPRIG_THROW_EXCEPTION(code_ended("code ended: code ended"));
					return false;
				}
				return is_command(pbuffer_[ppointer_]);
			}
			bool execute() {
				if (is_code_end()) {
					SPRIG_THROW_EXCEPTION(code_ended("code ended: code ended"));
					return false;
				}
				bool result = execute(pbuffer_[ppointer_]);
				++ppointer_;
				return result;
			}
			//
			//	COMMENT: コード
			//
			void push_raw_code(char const* code) {
				pbuffer_.insert(
					pbuffer_.end(),
					code,
					code + std::strlen(code)
					);
			}
			template<typename Stream>
			void push_raw_code(
				Stream& code,
				typename boost::enable_if<
					sprig::is_derived_basic_istream<Stream>
				>::type* = 0
				)
			{
				pbuffer_.insert(
					pbuffer_.end(),
					std::istream_iterator<byte_type>(code),
					std::istream_iterator<byte_type>()
					);
			}
			template<typename Range>
			void push_raw_code(
				Range const& code,
				typename boost::disable_if<
					sprig::is_derived_basic_istream<Range>
				>::type* = 0
				)
			{
				pbuffer_.insert(
					pbuffer_.end(),
					boost::begin(code),
					boost::end(code)
					);
			}
			void push_code(char const* code) {
				if (ext_comment_) {
					pbuffer_type code2(
						code,
						code + std::strlen(code)
						);
					remove_comment(code2);
					push_raw_code(code2);
				} else {
					push_raw_code(code);
				}
			}
			void remove_comment(pbuffer_type& code) {
				pbuffer_type::iterator first = code.begin();
				pbuffer_type::iterator last = code.end();
				for (; ; ) {
					pbuffer_type::iterator sharp_pos = std::find(
						first,
						last,
						'#'
						);
					if (sharp_pos != last) {
						pbuffer_type::iterator eol_pos = std::find(
							sharp_pos,
							last,
							'\n'
							);
						first = code.erase(sharp_pos, eol_pos);
						last = code.end();
					} else {
						break;
					}
				}
			}
			template<typename Stream>
			void push_code(
				Stream& code,
				typename boost::enable_if<
					sprig::is_derived_basic_istream<Stream>
				>::type* = 0
				)
			{
				if (ext_comment_) {
					std::istream_iterator<byte_type> first(code);
					std::istream_iterator<byte_type> last;
					pbuffer_type code2(
						first,
						last
						);
					remove_comment(code2);
					push_raw_code(code2);
				} else {
					push_raw_code(code);
				}
			}
			template<typename Range>
			void push_code(
				Range const& code,
				typename boost::disable_if<
					sprig::is_derived_basic_istream<Range>
				>::type* = 0
				)
			{
				if (ext_comment_) {
					pbuffer_type code2(
						boost::begin(code),
						boost::end(code)
						);
					remove_comment(code2);
					push_raw_code(code2);
				} else {
					push_raw_code(code);
				}
			}
			//
			//	COMMENT: メンバアクセス
			//
			pbuffer_type const& pbuffer() const {
				return pbuffer_;
			}
			pbuffer_type& pbuffer() {
				return pbuffer_;
			}
			dbuffer_type const& dbuffer() const {
				return dbuffer_;
			}
			dbuffer_type& dbuffer() {
				return dbuffer_;
			}
			ppointer_type const& ppointer() const {
				return ppointer_;
			}
			ppointer_type& ppointer() {
				return ppointer_;
			}
			dpointer_type const& dpointer() const {
				return dpointer_;
			}
			dpointer_type& dpointer() {
				return dpointer_;
			}
			direction_type const& front() const {
				return front_;
			}
			direction_type& front() {
				return front_;
			}
			direction_type const& head() const {
				return head_;
			}
			direction_type& head() {
				return head_;
			}
			bool& pure() {
				return pure_;
			}
			bool const& pure() const {
				return pure_;
			}
			bool& ext_bitwise() {
				return ext_bitwise_;
			}
			bool const& ext_bitwise() const {
				return ext_bitwise_;
			}
			bool& ext_arithmetic() {
				return ext_arithmetic_;
			}
			bool const& ext_arithmetic() const {
				return ext_arithmetic_;
			}
			bool& ext_copyswap() {
				return ext_copyswap_;
			}
			bool const& ext_copyswap() const {
				return ext_copyswap_;
			}
			bool& ext_axis() {
				return ext_axis_;
			}
			bool const& ext_axis() const {
				return ext_axis_;
			}
			bool& ext_comment() {
				return ext_comment_;
			}
			bool const& ext_comment() const {
				return ext_comment_;
			}
			output_type const& output() const {
				return output_;
			}
			output_type& output() {
				return output_;
			}
			input_type const& input() const {
				return input_;
			}
			input_type& input() {
				return input_;
			}
		};
		namespace {
			//
			// swap
			//
			SPRIG_INLINE void swap(engine& lhs, engine& rhs) {
				lhs.swap(rhs);
			}
		}	// anonymous-namespace
	}	// namespace braincunt
}	// namespace sprig

BOOST_CLASS_VERSION(sprig::braincunt::engine, 1);
BOOST_CLASS_EXPORT(sprig::braincunt::engine::default_output);
BOOST_CLASS_EXPORT(sprig::braincunt::engine::default_input);

#endif	// #ifndef SPRIG_BRAINCUNT_HPP
