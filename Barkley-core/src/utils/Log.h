#pragma once

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>

//#include <Windows.h>
#include <barkley_types.h>

#define BARKLEY_LOG_LEVEL_FATAL 0
#define BARKLEY_LOG_LEVEL_ERROR 1
#define BARKLEY_LOG_LEVEL_WARN  2
#define BARKLEY_LOG_LEVEL_INFO  3

namespace std
{
	template <typename T>
	string to_string(const T& t)
	{
		return std::string("[Unsupported type (") + typeid(T).name() + std::string(")!] (to_string)");
	}
}

//
// Work in progress!
//
// -------------------------------
//			TODO: 
// -------------------------------
//	- Better container type logging
//	- Better platform support
//	- Logging to other destinations (eg. files)
//	- Include (almost) ALL BARKLEY class types
//	- More...
namespace barkley { namespace internal {

		static char to_string_buffer[1024 * 10];

		void PlatformLogMessage(uint level, const char* messge);

		template <class T>
		struct has_iterator
		{
			template<class U> static char(&test(typename U::iterator const*))[1];
			template<class U> static char(&test(...))[2];
			static const bool value = (sizeof(test<T>(0)) == 1);
		};


		template <typename T>
		static const char* to_string(const T& t)
		{
			return to_string_internal<T>(t, std::integral_constant<bool, has_iterator<T>::value>());
		}

		template <>
		static const char* to_string<char>(char const & t)
		{
			return &t;
		}

		template <>
		static const char* to_string<char*>(char* const & t)
		{
			return t;
		}

		template <>
		static const char* to_string<unsigned char const*>(unsigned char const* const & t)
		{
			return (const char*)t;
		}

		template <>
		static const char* to_string<char const*>(char const * const & t)
		{
			return t;
		}

		template <>
		static const char* to_string<std::string>(std::string const & t)
		{
			return t.c_str();
		}

		template <typename T>
		static std::string format_iterators(T& begin, T& end)
		{
			std::string result;
			bool first = true;
			while (begin != end)
			{
				if (!first)
					result += ", ";
				result += to_string(*begin);
				first = false;
				begin++;
			}
			return result;
		}

		//
		//template <typename T> const char* container_to_string_internal(const std::vector<T>& v)
		//{
		//	static char buffer[1024];
		//	sprintf(buffer, "Vector of %s - size: %d, contents: %s", typeid(T).name(), v.size(), format_iterators(v.begin(), v.end()).c_str());
		//	return buffer;
		//}
		//
		//template <typename T> const char* container_to_string_internal(const std::list<T>& v)
		//{
		//	static char buffer[1024];
		//	sprintf(buffer, "List of %s - size: %d, contents: %s", typeid(T).name(), v.size(), format_iterators(v.begin(), v.end()).c_str());
		//	return buffer;
		//}

		template <typename T>
		static const char* to_string_internal(const T& v, const std::true_type& ignored)
		{
			sprintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
			return to_string_buffer;
		}

		template <typename T>
		static const char* to_string_internal(const T& t, const std::false_type& ignored)
		{
			auto x = std::to_string(t);
			return strcpy(to_string_buffer, x.c_str());
		}

		template<typename X, typename Y>
		static const char* to_string(const std::pair<typename X, typename Y>& v)
		{
			sprintf(to_string_buffer, "(Key: %s, Value: %s)", to_string(v.first), to_string(v.second));
			return to_string_buffer;
		}

		template<>
		static const char* to_string_internal<const char*>(const char* const& v, const std::false_type& ignored)
		{
			return v;
		}

		template <typename First>
		static void print_log_internal(char* buffer, int& position, First&& first)
		{
			const char* formatted = to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void print_log_internal(char* buffer, int& position, First&& first, Args&&... args)
		{
			const char* formatted = to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
			if (sizeof...(Args))
				print_log_internal(buffer, position, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void log_message(int level, bool newline, Args... args)
		{
			char buffer[1024 * 10];
			int position = 0;
			print_log_internal(buffer, position, std::forward<Args>(args)...);

			if (newline)
				buffer[position++] = '\n';

			buffer[position] = 0;

			PlatformLogMessage(level, buffer);
		}
}}



#ifndef BARKLEY_LOG_LEVEL
#define BARKLEY_LOG_LEVEL BARKLEY_LOG_LEVEL_INFO
#endif

#if BARKLEY_LOG_LEVEL >= BARKLEY_LOG_LEVEL_FATAL
#define BARKLEY_FATAL(...) barkley::internal::log_message(BARKLEY_LOG_LEVEL_FATAL, true, "BARKLEY:    ", __VA_ARGS__)
#define _BARKLEY_FATAL(...) barkley::internal::log_message(BARKLEY_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define BARKLEY_FATAL(...)
#endif

#if BARKLEY_LOG_LEVEL >= BARKLEY_LOG_LEVEL_ERROR
#define BARKLEY_ERROR(...) barkley::internal::log_message(BARKLEY_LOG_LEVEL_ERROR, true, "BARKLEY:    ", __VA_ARGS__)
#else
#define BARKLEY_ERROR(...)
#endif

#if BARKLEY_LOG_LEVEL >= BARKLEY_LOG_LEVEL_WARN
#define BARKLEY_WARN(...) barkley::internal::log_message(BARKLEY_LOG_LEVEL_WARN, true, "BARKLEY:    ", __VA_ARGS__)
#else
#define BARKLEY_WARN(...)
#endif

#if BARKLEY_LOG_LEVEL >= BARKLEY_LOG_LEVEL_INFO
#define BARKLEY_INFO(...) barkley::internal::log_message(BARKLEY_LOG_LEVEL_INFO, true, "BARKLEY:    ", __VA_ARGS__)
#else
#define BARKLEY_INFO(...)
#endif

#define BARKLEY_ASSERT(x, ...) \
	do { \
	if (!(x)) \
						{ \
		char* file = __FILE__; \
		unsigned int last = 0; \
		char* c; \
		for (c = file; *c != '\0'; c++) \
												{ \
			if (*c == '\\' || *c == '/') \
				last = c - file; \
												} \
		BARKLEY_FATAL(""); \
		BARKLEY_FATAL("*************************"); \
		BARKLEY_FATAL("    ASSERTION FAILED!    "); \
		BARKLEY_FATAL("*************************"); \
		BARKLEY_FATAL(#x); \
		BARKLEY_FATAL(__VA_ARGS__); \
		_BARKLEY_FATAL("-> "); \
		for (int i = last + 1; i < c - file; i++) \
			_BARKLEY_FATAL(file[i]); \
		_BARKLEY_FATAL(":", __LINE__, "\n"); \
		*(int*)NULL = 8; \
						} \
					} while(0)