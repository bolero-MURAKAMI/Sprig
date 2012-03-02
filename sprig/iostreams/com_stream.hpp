#ifndef SPRIG_IOSTREAMS_COM_STREAM_HPP
#define SPRIG_IOSTREAMS_COM_STREAM_HPP

#include <sprig/config/config.hpp>

#ifdef SPRIG_USING_PRAGMA_ONCE
#	pragma once
#endif	// #ifdef SPRIG_USING_PRAGMA_ONCE

#include <ios>
#include <algorithm>
#include <boost/assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/positioning.hpp>
#include <sprig/external/objidl.hpp>
#include <sprig/exception.hpp>
#include <sprig/type_traits/is_char_type.hpp>
#include <sprig/type_traits/is_wchar_type.hpp>
#include <sprig/com_ptr/unknown.hpp>

namespace sprig {
	namespace iostreams {
		//
		// com_stream_traits
		//
		template<
			typename To,
			typename From = To,
			typename Enable = void
		>
		class com_stream_traits {};
		template<
			typename To,
			typename From
		>
		class com_stream_traits<
			To,
			From,
			typename boost::enable_if<
				boost::mpl::or_<
					boost::mpl::and_<
						sprig::is_char_type<From>,
						sprig::is_char_type<To>
					>,
					boost::mpl::and_<
						sprig::is_wchar_type<From>,
						sprig::is_wchar_type<To>
					>
				>
			>::type
		> {
		public:
			typedef IStream stream_type;
			typedef From from_type;
			typedef To to_type;
		public:
			static std::streamsize read(
				to_type* s,
				std::streamsize n,
				stream_type* ptr,
				HRESULT* result = 0
				)
			{
				ULONG size = 0;
				HRESULT res = ptr->Read(s, n * sizeof(from_type), &size);
				if (result) {
					*result = res;
				}
				return res == S_OK
					? size / sizeof(from_type)
					: -1
					;
			}
			static std::streamsize write(
				to_type const* s,
				std::streamsize n,
				stream_type* ptr,
				HRESULT* result = 0
				)
			{
				ULONG size = 0;
				HRESULT res = ptr->Write(s, n * sizeof(from_type), &size);
				if (result) {
					*result = res;
				}
				return res == S_OK
					? size / sizeof(from_type)
					: -1
					;
			}
			static std::streampos seek(
				boost::iostreams::stream_offset off,
				std::ios_base::seekdir way,
				stream_type* ptr,
				HRESULT* result = 0
				)
			{
				ULARGE_INTEGER pos = 0;
				HRESULT res = S_OK;
				switch (way) {
				case std::ios_base::beg:
					res = ptr->Seek(off * sizeof(from_type), STREAM_SEEK_SET, &pos);
					break;
				case std::ios_base::cur:
					res = ptr->Seek(off * sizeof(from_type), STREAM_SEEK_CUR, &pos);
					break;
				case std::ios_base::end:
					res = ptr->Seek(off * sizeof(from_type), STREAM_SEEK_END, &pos);
					break;
				default:
					BOOST_ASSERT(0);
					res = E_FAIL;
				}
				if (result) {
					*result = res;
				}
				return pos;
			}
		};
		//
		// com_stream_device
		//
		template<
			typename To,
			typename From = To,
			typename Mode = boost::iostreams::seekable,
			typename Traits = com_stream_traits<To, From>
		>
		class com_stream_device {
		public:
			typedef To char_type;
			typedef Traits traits_type;
			typedef typename traits_type::stream_type stream_type;
			typedef typename traits_type::to_type to_type;
			typedef typename traits_type::from_type from_type;
			typedef sprig::com_ptr<stream_type> stream_ptr_type;
		public:
			struct category
				: public virtual boost::iostreams::device_tag
				, public virtual Mode
			{};
		private:
			stream_ptr_type ptr_;
		public:
			explicit com_stream_device(stream_ptr_type const& ptr)
				: ptr_(ptr)
			{
				if (!ptr_) {
					SPRIG_THROW_EXCEPTION(sprig::exception("null-pointer to IStream"));
				}
			}
			explicit com_stream_device(stream_type* stream, bool add_ref = true)
				: ptr_(stream, add_ref)
			{
				if (!ptr_) {
					SPRIG_THROW_EXCEPTION(sprig::exception("null-pointer to IStream"));
				}
			}
			virtual ~com_stream_device() throw() {}
			std::streamsize read(char_type* s, std::streamsize n) {
				HRESULT result = S_OK;
				std::streamsize size = traits_type::read(s, n, ptr_.get(), &result);
				if (FAILED(result)) {
					SPRIG_THROW_EXCEPTION(sprig::exception("error in IStream::Read()"));
				}
				return size;
			}
			std::streamsize write(char_type const* s, std::streamsize n) {
				HRESULT result = S_OK;
				std::streamsize size = traits_type::write(s, n, ptr_.get(), &result);
				if (FAILED(result)) {
					SPRIG_THROW_EXCEPTION(sprig::exception("error in IStream::Write()"));
				}
				return size;
			}
			std::streampos seek(boost::iostreams::stream_offset off, std::ios_base::seekdir way) {
				HRESULT result = S_OK;
				std::streampos pos = traits_type::seek(off, way, ptr_.get(), &result);
				if (FAILED(result)) {
					SPRIG_THROW_EXCEPTION(sprig::exception("error in IStream::Seek()"));
				}
				return pos;
			}
		};
		//
		// com_stream_source
		//
		template<
			typename To,
			typename From = To
		>
		class com_stream_source
			: public com_stream_device<To, From, boost::iostreams::input>
		{
		private:
			typedef com_stream_device<To, From, boost::iostreams::input> base_type;
		public:
			explicit com_stream_source(typename base_type::stream_ptr_type const& ptr)
				: base_type(ptr)
			{}
			explicit com_stream_source(typename base_type::stream_type* stream, bool add_ref = true)
				: base_type(stream, add_ref)
			{}
		};
		//
		// com_stream_sink
		//
		template<
			typename To,
			typename From = To
		>
		class com_stream_sink
			: public com_stream_device<To, From, boost::iostreams::output>
		{
		private:
			typedef com_stream_device<To, From, boost::iostreams::output> base_type;
		public:
			explicit com_stream_sink(typename base_type::stream_ptr_type const& ptr)
				: base_type(ptr)
			{}
			explicit com_stream_sink(typename base_type::stream_type* stream, bool add_ref = true)
				: base_type(stream, add_ref)
			{}
		};
	}	// namespace iostreams
}	// namespace sprig

#endif	// #ifndef SPRIG_IOSTREAMS_COM_STREAM_HPP
