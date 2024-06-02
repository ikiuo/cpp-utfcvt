/*
 * utfcvt.hpp
 */
#pragma once

#include <algorithm>
#include <cstdint>
#include <cwchar>
#include <limits>
#include <string>

#ifdef _MSC_VER
#  include <intrin.h>
#endif

/*
 * C++XX
 */

#if __cplusplus >= 201103L
#  define utfcvt_compiler_cxx11  1
#else  /* C++11 */
#  define utfcvt_compiler_cxx11  0
#endif

#if __cplusplus >= 202002L
#  define utfcvt_compiler_cxx20  1
#else  /* C++20 */
#  define utfcvt_compiler_cxx20  0
#endif

/*
 * char / wchar / char8_t / char16_t / char32_t
 */
#define utfcvt_compiler_cxx_char  1
#define utfcvt_compiler_cxx_wchar  1

#if __cpp_char8_t >= 201811L
#  define utfcvt_compiler_cxx_char8  1
#else
#  define utfcvt_compiler_cxx_char8  0
#endif

#if (utfcvt_compiler_cxx11 ||                     \
     (defined(_MSC_VER) && _MSC_VER >= 1900) ||   \
     defined(__clang__) ||                        \
     0)
#  define utfcvt_compiler_cxx_char16  1
#  define utfcvt_compiler_cxx_char32  1
#else
#  define utfcvt_compiler_cxx_char16  0
#  define utfcvt_compiler_cxx_char32  0
#endif

#ifndef utfcvt_compiler_char
#  define utfcvt_compiler_char  utfcvt_compiler_cxx_char
#endif
#ifndef utfcvt_compiler_wchar
#  define utfcvt_compiler_wchar  utfcvt_compiler_cxx_wchar
#endif
#ifndef utfcvt_compiler_char8
#  define utfcvt_compiler_char8  utfcvt_compiler_cxx_char8
#endif
#ifndef utfcvt_compiler_char16
#  define utfcvt_compiler_char16  utfcvt_compiler_cxx_char16
#endif
#ifndef utfcvt_compiler_char32
#  define utfcvt_compiler_char32  utfcvt_compiler_cxx_char16
#endif

#define utfcvt_compiler_cxx_string  utfcvt_compiler_cxx_char
#define utfcvt_compiler_cxx_wstring  utfcvt_compiler_cxx_wchar
#define utfcvt_compiler_cxx_u8string  utfcvt_compiler_cxx_char8
#define utfcvt_compiler_cxx_u16string  utfcvt_compiler_cxx_char16
#define utfcvt_compiler_cxx_u32string  utfcvt_compiler_cxx_char32

#ifndef utfcvt_compiler_string
#  define utfcvt_compiler_string  utfcvt_compiler_cxx_string
#endif
#ifndef utfcvt_compiler_wstring
#  define utfcvt_compiler_wstring  utfcvt_compiler_cxx_wstring
#endif
#ifndef utfcvt_compiler_u8string
#  define utfcvt_compiler_u8string  utfcvt_compiler_cxx_u8string
#endif
#ifndef utfcvt_compiler_u16string
#  define utfcvt_compiler_u16string  utfcvt_compiler_cxx_u16string
#endif
#ifndef utfcvt_compiler_u32string
#  define utfcvt_compiler_u32string  utfcvt_compiler_cxx_u32string
#endif

/*
 * clz
 */
#ifndef utfcvt_compiler_clz
#  if utfcvt_compiler_cxx20
#    include <bit>
#    define utfcvt_compiler_clz 1
#  else
#    if defined(__has_builtin)
#      if __has_builtin(__builtin_clz)
#        define utfcvt_compiler_builtin_clz  1
#      endif
#      if __has_builtin(__builtin_ia32_lzcnt_u32)
#        define utfcvt_compiler_builtin_ia32_lzcnt_u32  1
#      endif
#    endif /* __has_builtin */
#    ifdef _MSC_VER
#      define utfcvt_compiler_bsr  1
#    endif /* VC++ */
#    if (0 ||                                                 \
         defined(utfcvt_compiler_builtin_clz) ||              \
         defined(utfcvt_compiler_builtin_ia32_lzcnt_u32) ||   \
         defined(utfcvt_compiler_bsr) ||                      \
         0)
#      define utfcvt_compiler_clz  1
#    endif
#  endif
#endif
#ifndef utfcvt_compiler_clz
#  define utfcvt_compiler_clz  0
#endif

/*
 * utf8::putcodelen
 */
#ifndef utfcvt_utf8_putcodelen_mode
#  if !utfcvt_compiler_clz
#    define utfcvt_utf8_putcodelen_mode  0
#  else
#    define utfcvt_utf8_putcodelen_mode  1
#  endif
#endif

/*
 * Declaration
 */
namespace utfcvt
{
    typedef std::uint32_t utf32_t;

    /*
     *
     */

    std::uint8_t replace_u8c();
    std::uint16_t replace_u16c();
    std::uint32_t replace_u32c();

    template <typename sT> size_t utflen(sT* s);

#if utfcvt_compiler_string
    template <typename sT> std::string to_string(sT s);
    template <typename iT> std::string to_string(iT s, iT e);
    template <typename sT> std::string to_string(sT* s, size_t n);
#endif

#if utfcvt_compiler_wstring
    template <typename sT> std::wstring to_wstring(sT s);
    template <typename iT> std::wstring to_wstring(iT s, iT e);
    template <typename sT> std::wstring to_wstring(sT* s, size_t n);
#endif

#if utfcvt_compiler_u8string
    template <typename sT> std::u8string to_u8string(sT s);
    template <typename iT> std::u8string to_u8string(iT s, iT e);
    template <typename sT> std::u8string to_u8string(sT* s, size_t n);
#endif

#if utfcvt_compiler_u16string
    template <typename sT> std::u16string to_u16string(sT s);
    template <typename iT> std::u16string to_u16string(iT s, iT e);
    template <typename sT> std::u16string to_u16string(sT* s, size_t n);
#endif

#if utfcvt_compiler_u32string
    template <typename sT> std::u32string to_u32string(sT s);
    template <typename iT> std::u32string to_u32string(iT s, iT e);
    template <typename sT> std::u32string to_u32string(sT* s, size_t n);
#endif

    /*
     *
     */

    struct utfcvt_getcres
    {
        bool success;
        std::uint8_t size;
        utf32_t code;

        utfcvt_getcres(size_t s, utf32_t c, bool b = true);
    };

    struct utfcvt_result
    {
        bool success;
        size_t read;
        size_t write;

        utfcvt_result(size_t r, size_t w, bool b = true);
    };

    template <typename T>
    class utfcvt_buffer
    {
    public:
        typedef T value_type;

        T *start;
        T *end;
        T *pointer;
        bool error;

    public:
        utfcvt_buffer(T* p, T* e);
        utfcvt_buffer(T* p, size_t n);

        void push_back(T c);
    };

    class utf_common
    {
    public:
        template <typename sT>
        static size_t len(sT* s);

        template <typename sT>
        static size_t length(sT* s);

    protected:
        template <typename dU, typename sU, typename dT, typename iT>
        static utfcvt_result append(dT& d, iT s, iT e);

        template <typename dT, typename iT>
        static utfcvt_result copy(dT& d, iT s, iT e);

        template <typename dU, typename dT, typename iT>
        static utfcvt_result degrade(dT& d, iT s, iT e);

        template <typename dU, typename sU, typename dT, typename iT>
        static utfcvt_result convert(dT& d, iT s, iT e);

        template <typename dU, typename sU, typename iT>
        static utfcvt_result count(iT s, iT e);

        template <typename dU, typename sU, typename iT>
        static utfcvt_result cvtlen(iT s, iT e);
    };

    class utf8 : public utf_common
    {
    public:
        enum { code_size = 1 };

        /* replacement_character */

        static std::uint8_t replacement_character();

        /* getcodelen */

        template <typename cT>
        static size_t getcodelen(cT c);

        /* getcode */

        template <typename iT>
        static utfcvt_getcres getcode(iT s, iT e);

        template <typename sT>
        static utfcvt_getcres getcode(sT* s, size_t n);

        template <typename sT>
        static utfcvt_getcres getcode(sT& s);

        template <typename sT>
        static utfcvt_getcres getcode(sT* s);

        /* putcodelen */

        template <typename cT>
        static size_t putcodelen(cT c);

        /* putcode */

        template <typename dT, typename cT>
        static size_t putcode(dT& d, cT c);

        /* to_utf8len */

        template <typename iT>
        static utfcvt_result to_utf8len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf8len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf8len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf8len(sT* s);

        /* to_utf16len */

        template <typename iT>
        static utfcvt_result to_utf16len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf16len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf16len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf16len(sT* s);

        /* to_utf32len */

        template <typename iT>
        static utfcvt_result to_utf32len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf32len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf32len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf32len(sT* s);

        /* to_utf8 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf8(dT& d, iT s, iT e);

        template <typename dT, typename iT>
        static utfcvt_result to_utf8(dT& d, iT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT* s);

        /* to_utf16 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf16(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT* s);

        /* to_utf32 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf32(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT* s);

    protected:
        template <typename cT> static size_t getcodelen32(cT c);
        template <typename cT> static size_t getcodelen64(cT c);
        template <typename cT> static size_t putcodelen32(cT c);
        template <typename cT> static size_t putcodelen64(cT c);
    };

    class utf16 : public utf_common
    {
    public:
        enum { code_size = 2 };

        /* replacement_character */

        static std::uint16_t replacement_character();

        /* getcodelen */

        template <typename cT>
        static size_t getcodelen(cT c);

        /* getcode */

        template <typename iT>
        static utfcvt_getcres getcode(iT s, iT e);

        template <typename sT>
        static utfcvt_getcres getcode(sT* s, size_t n);

        template <typename sT>
        static utfcvt_getcres getcode(sT& s);

        template <typename sT>
        static utfcvt_getcres getcode(sT* s);

        /* putcodelen */

        template <typename cT>
        static size_t putcodelen(cT c);

        /* putcode */

        template <typename dT, typename cT>
        static size_t putcode(dT& d, cT c);

        /* to_utf8len */

        template <typename iT>
        static utfcvt_result to_utf8len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf8len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf8len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf8len(sT* s);

        /* to_utf16len */

        template <typename iT>
        static utfcvt_result to_utf16len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf16len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf16len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf16len(sT* s);

        /* to_utf32len */

        template <typename iT>
        static utfcvt_result to_utf32len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf32len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf32len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf32len(sT* s);

        /* to_utf8 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf8(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT* s);

        /* to_utf16 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf16(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT* s);

        /* to_utf32 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf32(dT& d, iT s, iT e);

        template <typename dT, typename iT>
        static utfcvt_result to_utf32(dT& d, iT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT* s);

    protected:
        template <typename cT> static size_t getcodelen32(cT c);
        template <typename cT> static size_t getcodelen64(cT c);
        template <typename cT> static size_t putcodelen32(cT c);
        template <typename cT> static size_t putcodelen64(cT c);
    };

    class utf32 : public utf_common
    {
    public:
        enum { code_size = 4 };

        /* replacement_character */

        static std::uint32_t replacement_character();

        /* getcodelen */

        template <typename cT>
        static size_t getcodelen(cT c);

        /* getcode */

        template <typename iT>
        static utfcvt_getcres getcode(iT s, iT e);

        template <typename sT>
        static utfcvt_getcres getcode(sT* s, size_t n);

        template <typename sT>
        static utfcvt_getcres getcode(sT& s);

        template <typename sT>
        static utfcvt_getcres getcode(sT* s);

        /* putcodelen */

        template <typename cT>
        static size_t putcodelen(cT c);

        /* putcode */

        template <typename dT, typename cT>
        static size_t putcode(dT& d, cT c);

        /* to_utf8len */

        template <typename iT>
        static utfcvt_result to_utf8len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf8len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf8len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf8len(sT* s);

        /* to_utf16len */

        template <typename iT>
        static utfcvt_result to_utf16len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf16len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf16len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf16len(sT* s);

        /* to_utf32len */

        template <typename iT>
        static utfcvt_result to_utf32len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf32len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf32len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf32len(sT* s);

        /* to_utf8 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf8(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT* s);

        /* to_utf16 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf16(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT* s);

        /* to_utf32 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf32(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT* s);

    protected:
        template <typename cT> static size_t getcodelen32(cT c);
        template <typename cT> static size_t getcodelen64(cT c);
        template <typename cT> static size_t putcodelen32(cT c);
        template <typename cT> static size_t putcodelen64(cT c);
    };

    class utf : public utf_common
    {
    public:
        /* getcodelen */

        template <typename cT>
        static size_t getcodelen(cT c);

        /* getcode */

        template <typename iT>
        static utfcvt_getcres getcode(iT s, iT e);

        template <typename sT>
        static utfcvt_getcres getcode(sT* s, size_t n);

        template <typename sT>
        static utfcvt_getcres getcode(sT& s);

        template <typename sT>
        static utfcvt_getcres getcode(sT* s);

        /* putcodelen */

        template <typename cT>
        inline static size_t putcodelen(cT c);

        /* putcode */

        template <typename dT, typename cT>
        static size_t putcode(dT& d, cT c);

        /* to_utf8len */

        template <typename iT>
        static utfcvt_result to_utf8len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf8len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf8len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf8len(sT* s);

        /* to_utf16len */

        template <typename iT>
        static utfcvt_result to_utf16len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf16len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf16len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf16len(sT* s);

        /* to_utf32len */

        template <typename iT>
        static utfcvt_result to_utf32len(iT s, iT e);

        template <typename sT>
        static utfcvt_result to_utf32len(sT* s, size_t n);

        template <typename sT>
        static utfcvt_result to_utf32len(sT& s);

        template <typename sT>
        static utfcvt_result to_utf32len(sT* s);

        /* to_utf8 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf8(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf8(dT& d, sT* s);

        /* to_utf16 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf16(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf16(dT& d, sT* s);

        /* to_utf32 */

        template <typename dT, typename iT>
        static utfcvt_result to_utf32(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result to_utf32(dT& d, sT* s);

        /* cvtlen */

        template <typename dT, typename iT>
        static utfcvt_result cvtlen(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result cvtlen(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result cvtlen(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result cvtlen(dT& d, sT* s);

        /* cvt */

        template <typename dT, typename iT>
        static utfcvt_result cvt(dT& d, iT s, iT e);

        template <typename dT, typename sT>
        static utfcvt_result cvt(dT& d, sT* s, size_t n);

        template <typename dT, typename sT>
        static utfcvt_result cvt(dT& d, sT& s);

        template <typename dT, typename sT>
        static utfcvt_result cvt(dT& d, sT* s);
    };

    /*
     *
     */

    namespace utfcvtimpl
    {
        template <typename T> int clzN(T x);
        template <typename T> int clz32(T t);

        template <typename T>
        struct binary_type
        {
            typedef T value_type;
            enum { size = sizeof(T) };
        };

        template <typename T> struct data_type;

#if utfcvt_compiler_cxx_char
        template <> struct data_type<char> : binary_type<char> {};
#endif
#if utfcvt_compiler_cxx_wchar
        template <> struct data_type<wchar_t> : binary_type<wchar_t> {};
#endif
#if utfcvt_compiler_cxx_char8
        template <> struct data_type<char8_t> : binary_type<char8_t> {};
#endif
#if utfcvt_compiler_cxx_char16
        template <> struct data_type<char16_t> : binary_type<char16_t> {};
#endif
#if utfcvt_compiler_cxx_char32
        template <> struct data_type<char32_t> : binary_type<char32_t> {};
#endif

        template <> struct data_type<signed char> : binary_type<signed char> {};
        template <> struct data_type<signed short> : binary_type<signed short> {};
        template <> struct data_type<signed int> : binary_type<signed int> {};
        template <> struct data_type<signed long> : binary_type<signed long> {};
        template <> struct data_type<signed long long> : binary_type<signed long long> {};

        template <> struct data_type<unsigned char> : binary_type<unsigned char> {};
        template <> struct data_type<unsigned short> : binary_type<unsigned short> {};
        template <> struct data_type<unsigned int> : binary_type<unsigned int> {};
        template <> struct data_type<unsigned long> : binary_type<unsigned long> {};
        template <> struct data_type<unsigned long long> : binary_type<unsigned long long> {};

        template <typename T> struct data_type<T*> : binary_type<T> {};

        template <typename T>
        struct data_type
        {
            typedef typename T::value_type value_type;
            enum { size = sizeof(value_type) };
        };

        template <typename T>
        struct code_type
        {
            typedef data_type<T> data_type;

            enum { size = data_type::size };

            template <int N>
            struct size_type;

            template <>
            struct size_type<1>
            {
                typedef std::uint8_t char_t;
                typedef std::uint32_t comp_t;
            };

            template <>
            struct size_type<2>
            {
                typedef std::uint16_t char_t;
                typedef std::uint32_t comp_t;
            };

            template <>
            struct size_type<4>
            {
                typedef std::uint32_t char_t;
                typedef std::uint32_t comp_t;
            };

            template <>
            struct size_type<8>
            {
                typedef std::uint64_t char_t;
                typedef std::uint64_t comp_t;
            };

            typedef size_type<size> type_data;
            typedef typename type_data::char_t char_t;
            typedef typename type_data::comp_t comp_t;
        };

        template <typename T>
        struct utf_selector
        {
            typedef code_type<T> code_type;
            enum { size = code_type::size };

            template <int N> struct size_type;
            template <> struct size_type<1> { typedef utf8 type; };
            template <> struct size_type<2> { typedef utf16 type; };
            template <> struct size_type<4> { typedef utf32 type; };
            template <> struct size_type<8> { typedef utf32 type; };

            typedef typename size_type<size>::type utf_type;
        };

        template <typename T> struct utf_class : utf_selector<T>::utf_type {};

        template <typename dT>
        struct cvt_utf8
        {
            template <typename iT>
            static utfcvt_result cvtlen(iT s, iT e);

            template <typename iT>
            static utfcvt_result cvt(dT& d, iT s, iT e);
        };

        template <typename dT>
        struct cvt_utf16
        {
            template <typename iT>
            static utfcvt_result cvtlen(iT s, iT e);

            template <typename iT>
            static utfcvt_result cvt(dT& d, iT s, iT e);
        };

        template <typename dT>
        struct cvt_utf32
        {
            template <typename iT>
            static utfcvt_result cvtlen(iT s, iT e);

            template <typename iT>
            static utfcvt_result cvt(dT& d, iT s, iT e);
        };

        template <typename dT>
        struct cvt_type
        {
            template <int N> struct size_type;
            template <> struct size_type<1> : cvt_utf8<dT> {};
            template <> struct size_type<2> : cvt_utf16<dT> {};
            template <> struct size_type<4> : cvt_utf32<dT> {};
            template <> struct size_type<8> : cvt_utf32<dT> {};
            typedef size_type<code_type<dT>::size> type;
        };

        template <typename dT> struct converter : cvt_type<dT>::type {};

    } // utfcvtimpl

} // utfcvt

/*
 * Implementation
 */
namespace utfcvt
{
    /*
     *
     */

    inline std::uint8_t replace_u8c()
    {
        return 0x3f;  // '?'
    }

    inline std::uint16_t replace_u16c()
    {
        return 0xfffd;
    }

    inline std::uint32_t replace_u32c()
    {
        return replace_u16c();
    }

    template <typename sT>
    inline size_t utflen(sT* s)
    {
        return utf::length(s);
    }

#if utfcvt_compiler_string

    template <typename sT>
    inline std::string to_string(sT s)
    {
        std::string d;

        utf::cvt(d, s);
        return d;
    }

    template <typename iT>
    inline std::string to_string(iT s, iT e)
    {
        std::string d;

        utf::cvt(d, s, e);
        return d;
    }

    template <typename sT>
    inline std::string to_string(sT* s, size_t n)
    {
        std::string d;

        utf::cvt(d, s, n);
        return d;
    }

#endif /* utfcvt_compiler_string */
#if utfcvt_compiler_wstring

    template <typename sT>
    inline std::wstring to_wstring(sT s)
    {
        std::wstring d;

        utf::cvt(d, s);
        return d;
    }

    template <typename iT>
    inline std::wstring to_wstring(iT s, iT e)
    {
        std::wstring d;

        utf::cvt(d, s, e);
        return d;
    }

    template <typename sT>
    inline std::wstring to_wstring(sT* s, size_t n)
    {
        std::wstring d;

        utf::cvt(d, s, n);
        return d;
    }

#endif /* utfcvt_compiler_wstring */
#if utfcvt_compiler_u8string

    template <typename sT>
    inline std::u8string to_u8string(sT s)
    {
        std::u8string d;

        utf::cvt(d, s);
        return d;
    }

    template <typename iT>
    inline std::u8string to_u8string(iT s, iT e)
    {
        std::u8string d;

        utf::cvt(d, s, e);
        return d;
    }

    template <typename sT>
    inline std::u8string to_u8string(sT* s, size_t n)
    {
        std::u8string d;

        utf::cvt(d, s, n);
        return d;
    }

#endif /* utfcvt_compiler_u8string */
#if utfcvt_compiler_u16string

    template <typename sT>
    inline std::u16string to_u16string(sT s)
    {
        std::u16string d;

        utf::cvt(d, s);
        return d;
    }

    template <typename iT>
    inline std::u16string to_u16string(iT s, iT e)
    {
        std::u16string d;

        utf::cvt(d, s, e);
        return d;
    }

    template <typename sT>
    inline std::u16string to_u16string(sT* s, size_t n)
    {
        std::u16string d;

        utf::cvt(d, s, n);
        return d;
    }

#endif /* utfcvt_compiler_u16string */
#if utfcvt_compiler_u32string

    template <typename sT>
    inline std::u32string to_u32string(sT s)
    {
        std::u32string d;

        utf::cvt(d, s);
        return d;
    }

    template <typename iT>
    inline std::u32string to_u32string(iT s, iT e)
    {
        std::u32string d;

        utf::cvt(d, s, e);
        return d;
    }

    template <typename sT>
    inline std::u32string to_u32string(sT* s, size_t n)
    {
        std::u32string d;

        utf::cvt(d, s, n);
        return d;
    }

#endif /* utfcvt_compiler_u32string */

    /*
     * utfcvt_getcres
     */

    inline utfcvt_getcres::utfcvt_getcres(size_t s, utf32_t c, bool b)
        : success(b)
        , size(std::uint8_t(s))
        , code(c)
    {
        /*NOOP*/
    }

    /*
     * utfcvt_result
     */

    inline utfcvt_result::utfcvt_result(size_t r, size_t w, bool b)
        : success(b)
        , read(r)
        , write(w)
    {
        /*NOOP*/
    }

    /*
     * utfcvt_buffer
     */

    template <typename T>
    inline utfcvt_buffer<T>::utfcvt_buffer(T* p, T* e)
        : start(p)
        , end(e)
        , pointer(p)
        , error(false)
    {
        /*NOOP*/
    }

    template <typename T>
    inline utfcvt_buffer<T>::utfcvt_buffer(T* p, size_t n)
        : start(p)
        , end(p + n)
        , pointer(p)
        , error(false)
    {
        /*NOOP*/
    }

    template <typename T>
    inline void utfcvt_buffer<T>::push_back(T c)
    {
        error = (pointer >= end);
        if (!error)
            *pointer++ = c;
    }

    /*
     * utf_common
     */

    template <typename sT>
    inline size_t utf_common::len(sT* s)
    {
        return length(s);
    }

    template <typename sT>
    inline size_t utf_common::length(sT* s)
    {
        sT* p = s;

        while (*p)
            ++p;
        return p - s;
    }

    template <typename dU, typename sU, typename dT, typename iT>
    inline utfcvt_result utf_common::append(dT& d, iT s, iT e)
    {
        typedef utfcvtimpl::template code_type<dT> code_dtype;
        typedef utfcvtimpl::template code_type<iT> code_stype;

        if (int(dU::code_size) != int(sU::code_size))
            return convert<dU, sU, dT, iT>(d, s, e);
        if (int(code_dtype::size) < int(code_stype::size))
            return degrade<dU, dT, iT>(d, s, e);
        return copy(d, s, e);
    }

    template <typename dT, typename iT>
    inline utfcvt_result utf_common::copy(dT& d, iT s, iT e)
    {
        typedef typename dT::value_type push_t;
        size_t n = e - s;

        for (iT p = s; p != e; ++p)
            d.push_back(push_t(*p));
        return utfcvt_result(n, n);
    }

    template <typename dU, typename dT, typename iT>
    inline utfcvt_result utf_common::degrade(dT& d, iT s, iT e)
    {
        typedef typename dT::value_type push_t;
        typedef typename utfcvtimpl::template code_type<dT>::char_t dchar_t;
        typedef typename utfcvtimpl::template code_type<iT>::char_t schar_t;

        schar_t dmax = schar_t(std::numeric_limits<dchar_t>::max());
        size_t n = e - s;
        bool b = true;

        for (iT p = s; p != e; ++p)
        {
            schar_t c = *p;

            if (c > dmax)
            {
                dchar_t r = dU::replacement_character();

                c = schar_t(sizeof(push_t) < 2 ? replace_u8c() : r);
                b = false;
            }
            d.push_back(push_t(c));
        }
        return utfcvt_result(n, n, b);
    }

    template <typename dU, typename sU, typename dT, typename iT>
    utfcvt_result utf_common::convert(dT& d, iT s, iT e)
    {
        size_t r = 0, w = 0;
        bool b = true;

        for (iT p = s; p != e;)
        {
            utfcvt_getcres res = sU::getcode(p, e);
            utf32_t code = res.success ? res.code : dU::replacement_character();

            b &= res.success;
            r += res.size;
            p += res.size;

            w += dU::putcode(d, code);
        }
        return utfcvt_result(r, w, b);
    }

    template <typename dU, typename sU, typename iT>
    inline utfcvt_result utf_common::count(iT s, iT e)
    {
        if (int(dU::code_size) == int(sU::code_size))
            return utfcvt_result(e - s, e - s);
        return cvtlen<dU, sU, iT>(s, e);
    }

    template <typename dU, typename sU, typename iT>
    utfcvt_result utf_common::cvtlen(iT s, iT e)
    {
        size_t r = 0, w = 0;
        bool b = true;

        for (iT p = s; p != e;)
        {
            utfcvt_getcres res = sU::getcode(p, e);
            utf32_t code = res.success ? res.code : dU::replacement_character();

            b &= res.success;
            r += res.size;
            p += res.size;

            w += std::max(size_t(1), dU::putcodelen(code));
        }
        return utfcvt_result(r, w, b);
    }

    /*
     * utf8
     */

    /* replacement_character */

    inline std::uint8_t utf8::replacement_character()
    {
        return replace_u8c();
    }

    /* getcodelen */

#if !utfcvt_compiler_clz

    template <typename cT>
    size_t utf8::getcodelen(cT c_)
    {
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;

        char_t c = char_t(c_);

        if (c < 0x80) return 1;
        if (c < 0xc0) return 0;  // error
        if (c < 0xe0) return 2;
        if (c < 0xf0) return 3;
        if (c < 0xf8) return 4;
        if (c < 0xfc) return 5;
        if (c < 0xfe) return 6;
        return 0;  // error
    }

    template <typename cT>
    inline size_t utf8::getcodelen32(cT c)
    {
        return getcodelen(c);
    }

    template <typename cT>
    inline size_t utf8::getcodelen64(cT c)
    {
        return getcodelen(c);
    }

#else  /* utfcvt_compiler_clz */

    template <typename cT>
    inline size_t utf8::getcodelen(cT c_)
    {
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;

        char_t c = char_t(c_);

        return sizeof(cT) <= 4 ? getcodelen32(c) : getcodelen64(c);
    }

    template <typename cT>
    inline size_t utf8::getcodelen32(cT c_)
    {
        utf32_t c = utf32_t(c_);

        if (c < 0x80) return 1;
        return (06543201 >> ((utfcvtimpl::clz32(c ^ 0xff) - 24) * 3)) & 7;
    }

    template <typename cT>
    inline size_t utf8::getcodelen64(cT c_)
    {
        std::uint64_t c = std::uint64_t(c_);

        return ((c >> 32) == 0) ? getcodelen32(utf32_t(c)) : 0;
    }

#endif /* utfcvt_compiler_clz */

    /* getcode */

    template <typename iT>
    utfcvt_getcres utf8::getcode(iT s, iT e)
    {
        typedef typename utfcvtimpl::template code_type<iT>::char_t char_t;

        iT p = s;

        if (p == e)
            return utfcvt_getcres(0, 0);

        char_t c = *p++;
        size_t l = getcodelen(c);

        if (l < 2)
            return utfcvt_getcres(1, c, l != 0);

        utf32_t w = c & (0x7f >> l);

        size_t t = 1;
        while (p != e)
        {
            c = *p++;
            if (!(0x80 <= c && c <= 0xbf))
                break;
            w = (w << 6) | (c & 0x3f);
            ++t;
        }
        return utfcvt_getcres(t, w, l == t);
    }

    template <typename sT>
    inline utfcvt_getcres utf8::getcode(sT* s, size_t n)
    {
        return getcode(s, s + n);
    }

    template <typename sT>
    inline utfcvt_getcres utf8::getcode(sT& s)
    {
        return getcode(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_getcres utf8::getcode(sT* s)
    {
        return getcode(s, length(s));
    }

    /* putcodelen */

    template <typename cT>
    inline size_t utf8::putcodelen(cT c)
    {
        return sizeof(cT) <= 4 ? putcodelen32(c) : putcodelen64(c);
    }

#if utfcvt_utf8_putcodelen_mode == 0

    template <typename cT>
    size_t utf8::putcodelen32(cT c_)
    {
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;
        typedef typename utfcvtimpl::template code_type<cT>::comp_t comp_t;

        comp_t c = char_t(c_);

        if (c < (1U << +7)) return 1;
        if (c < (1U << 11)) return 2;
        if (c < (1U << 16)) return 3;
        if (c < (1U << 21)) return 4;
        if (c < (1U << 26)) return 5;
        if (c < (1U << 31)) return 6;
        return 0; // error
    }

#elif utfcvt_utf8_putcodelen_mode == 1

    template <typename cT>
    inline size_t utf8::putcodelen32(cT c)
    {
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;

        static const std::uint8_t table[32+1] = {
            0,
            6, 6, 6, 6, 6,
            5, 5, 5, 5, 5,
            4, 4, 4, 4, 4,
            3, 3, 3, 3, 3,
            2, 2, 2, 2,
            1, 1, 1, 1, 1, 1, 1,
            1,
        };

        return table[utfcvtimpl::clz32(char_t(c))];
    }

#elif utfcvt_utf8_putcodelen_mode == 2

    template <typename cT>
    inline size_t utf8::putcodelen32(cT c)
    {
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;

        int n = clz32(char_t(c));

        if (!n--) return 0;  // error

        // 11111111 2222 3333 3 444 44 55 555 6 6666
        // 11111111 0000 1111/1 000/00 11/111 0/0000 = FF0F83E0
        // 00000000 1111 1111/1 000/00 00/000 1/1111 = 00FF801F
        // 00000000 0000 0000/0 111/11 11/111 1/1111 = 00007FFF
        std::uint_least32_t b0 = 1 & (0xFF0F83E0 >> n);
        std::uint_least32_t b1 = 1 & (0x00FF801F >> n);
        std::uint_least32_t b2 = 1 & (0x00007FFF >> n);

        return size_t((b0 << 0) | (b1 << 1) | (b2 << 2));
    }

#endif /* utfcvt_utf8_putcodelen_mode */

    template <typename cT>
    inline size_t utf8::putcodelen64(cT c_)
    {
        std::uint64_t c = std::uint64_t(c_);

        return (c >> 32) == 0 ? putcodelen32(utf32_t(c)) : 0;
    }

    /* putcode */

    template <typename dT, typename cT>
    size_t utf8::putcode(dT& d, cT c_)
    {
        typedef typename dT::value_type push_t;
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;

        char_t c = char_t(c_);
        size_t l = utf8::putcodelen(c);

        int b = int(l) - 1;

        if (b < 1)
        {
            if (b < 0)
                c = utf8::replacement_character();
            d.push_back(char_t(c));
            return 1;
        }

        int s = b * 6;

        d.push_back(push_t((0xff & (int(~0x7f) >> b)) |
                           ((c >> s) & (0x3f >> b))));
        do
        {
            s -= 6;
            d.push_back(push_t(0x80 | ((c >> s) & 0x3f)));
        } while (s > 0);

        return l;
    }

    /* to_utf8len */

    template <typename iT>
    inline utfcvt_result utf8::to_utf8len(iT s, iT e)
    {
        return count<utf8, utf8, iT>(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf8::to_utf8len(sT* s, size_t n)
    {
        return to_utf8len(s, s + n);
    }

    template <typename sT>
    inline utfcvt_result utf8::to_utf8len(sT& s)
    {
        return to_utf8len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf8::to_utf8len(sT* s)
    {
        return to_utf8len(s, length(s));
    }

    /* to_utf16len */

    template <typename iT>
    inline utfcvt_result utf8::to_utf16len(iT s, iT e)
    {
        return count<utf16, utf8, iT>(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf8::to_utf16len(sT* s, size_t n)
    {
        return to_utf16len(s, s + n);
    }

    template <typename sT>
    inline utfcvt_result utf8::to_utf16len(sT& s)
    {
        return to_utf16len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf8::to_utf16len(sT* s)
    {
        return to_utf16len(s, length(s));
    }

    /* to_utf32len */

    template <typename iT>
    inline utfcvt_result utf8::to_utf32len(iT s, iT e)
    {
        return count<utf32, utf8, iT>(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf8::to_utf32len(sT* s, size_t n)
    {
        return to_utf32len(s, s + n);
    }

    template <typename sT>
    inline utfcvt_result utf8::to_utf32len(sT& s)
    {
        return to_utf32len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf8::to_utf32len(sT* s)
    {
        return to_utf32len(s, length(s));
    }

    /* to_utf8 */

    template <typename dT, typename iT>
    inline utfcvt_result utf8::to_utf8(dT& d, iT s, iT e)
    {
        return append<utf8, utf8, dT, iT>(d, s, e);
    }

    template <typename dT, typename iT>
    inline utfcvt_result utf8::to_utf8(dT& d, iT* s, size_t n)
    {
        return to_utf8(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf8::to_utf8(dT& d, sT& s)
    {
        return to_utf8(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf8::to_utf8(dT& d, sT* s)
    {
        return to_utf8(d, s, length(s));
    }

    /* to_utf16 */

    template <typename dT, typename iT>
    inline utfcvt_result utf8::to_utf16(dT& d, iT s, iT e)
    {
        return append<utf16, utf8, dT, iT>(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf8::to_utf16(dT& d, sT* s, size_t n)
    {
        return to_utf16(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf8::to_utf16(dT& d, sT& s)
    {
        return to_utf16(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf8::to_utf16(dT& d, sT* s)
    {
        return to_utf16(d, s, length(s));
    }

    /* to_utf32 */

    template <typename dT, typename iT>
    inline utfcvt_result utf8::to_utf32(dT& d, iT s, iT e)
    {
        return append<utf32, utf8, dT, iT>(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf8::to_utf32(dT& d, sT* s, size_t n)
    {
        return to_utf32(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf8::to_utf32(dT& d, sT& s)
    {
        return to_utf32(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf8::to_utf32(dT& d, sT* s)
    {
        return to_utf32(d, s, length(s));
    }

    /*
     * utf16
     */

    /* replacement_character */

    inline std::uint16_t utf16::replacement_character()
    {
        return replace_u16c();
    }

    /* getcodelen */

    template <typename cT>
    size_t utf16::getcodelen(cT c_)
    {
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;
        typedef typename utfcvtimpl::template code_type<cT>::comp_t comp_t;

        comp_t c = char_t(c_);

        if (c < 0x0d800) return 1;
        if (c < 0x0dc00) return 2;
        if (c < 0x0e000) return 0;  // error
        if (c < 0x10000) return 1;
        return 0;  // error
    }

    template <typename cT>
    inline size_t utf16::getcodelen32(cT c)
    {
        return getcodelen(c);
    }

    template <typename cT>
    inline size_t utf16::getcodelen64(cT c)
    {
        return getcodelen(c);
    }

    /* getcode */

    template <typename iT>
    inline utfcvt_getcres utf16::getcode(iT s, iT e)
    {
        typedef typename utfcvtimpl::template code_type<iT>::char_t char_t;

        iT p = s;

        if (p == e)
            return utfcvt_getcres(0, 0);

        char_t c = *p++;
        size_t l = getcodelen(c);

        switch (l)
        {
        default: return utfcvt_getcres(1, c, false);
        case 1: return utfcvt_getcres(1, c);
        case 2: break;
        }

        if (p == e)
            return utfcvt_getcres(1, c, false);

        char_t d = *p;

        if (!(0xdc00 <= d && d <= 0xdfff))
            return utfcvt_getcres(1, c, false);

        utf32_t u = 0x10000 + ((c & 0x03ff) << 10) + (d & 0x03ff);

        return utfcvt_getcres(2, u);
    }

    template <typename sT>
    inline utfcvt_getcres utf16::getcode(sT* s, size_t n)
    {
        return getcode(s, s + n);
    }

    template <typename sT>
    inline utfcvt_getcres utf16::getcode(sT& s)
    {
        return getcode(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_getcres utf16::getcode(sT* s)
    {
        return getcode(s, length(s));
    }

    /* putcodelen */

    template <typename cT>
    inline size_t utf16::putcodelen(cT c_)
    {
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;
        typedef typename utfcvtimpl::template code_type<cT>::comp_t comp_t;

        comp_t c = char_t(c_);

        if (c < 0x010000) return 1;
        if (c < 0x110000) return 2;
        return 0;  // error
    }

    template <typename cT>
    inline size_t utf16::putcodelen32(cT c)
    {
        return putcodelen(c);
    }

    template <typename cT>
    inline size_t utf16::putcodelen64(cT c)
    {
        return putcodelen(c);
    }

    /* putcode */

    template <typename dT, typename cT>
    inline size_t utf16::putcode(dT& d, cT c_)
    {
        typedef typename dT::value_type push_t;
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;

        char_t c = char_t(c_);

        if (int(utfcvtimpl::template data_type<dT>::size) < 2)
        {
            if (c > 0xff)
                c = utf8::replacement_character();
            d.push_back(push_t(c));
            return 1;
        }

        size_t l = utf16::putcodelen(c);

        if (l < 2)
        {
            if (!l)
                c = char_t(utf16::replacement_character());
            d.push_back(push_t(c));
            return 1;
        }
        else
        {
            d.push_back(push_t(0xd800 | ((c - 0x10000) >> 10)));
            d.push_back(push_t(0xdc00 | (c & 0x03ff)));
            return 2;
        }
    }

    /* to_utf8len */

    template <typename iT>
    inline utfcvt_result utf16::to_utf8len(iT s, iT e)
    {
        return count<utf8, utf16, iT>(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf16::to_utf8len(sT* s, size_t n)
    {
        return to_utf8len(s, s + n);
    }

    template <typename sT>
    inline utfcvt_result utf16::to_utf8len(sT& s)
    {
        return to_utf8len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf16::to_utf8len(sT* s)
    {
        return to_utf8len(s, length(s));
    }

    /* to_utf16len */

    template <typename iT>
    inline utfcvt_result utf16::to_utf16len(iT s, iT e)
    {
        return count<utf16, utf16, iT>(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf16::to_utf16len(sT* s, size_t n)
    {
        return to_utf16len(s, s + n);
    }

    template <typename sT>
    inline utfcvt_result utf16::to_utf16len(sT& s)
    {
        return to_utf16len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf16::to_utf16len(sT* s)
    {
        return to_utf16len(s, length(s));
    }

    /* to_utf32len */

    template <typename iT>
    inline utfcvt_result utf16::to_utf32len(iT s, iT e)
    {
        return count<utf32, utf16, iT>(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf16::to_utf32len(sT* s, size_t n)
    {
        return to_utf32len(s, s + n);
    }

    template <typename sT>
    inline utfcvt_result utf16::to_utf32len(sT& s)
    {
        return to_utf32len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf16::to_utf32len(sT* s)
    {
        return to_utf32len(s, length(s));
    }

    /* to_utf8 */

    template <typename dT, typename iT>
    inline utfcvt_result utf16::to_utf8(dT& d, iT s, iT e)
    {
        return append<utf8, utf16, dT, iT>(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf16::to_utf8(dT& d, sT* s, size_t n)
    {
        return to_utf8(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf16::to_utf8(dT& d, sT& s)
    {
        return to_utf8(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf16::to_utf8(dT& d, sT* s)
    {
        return to_utf8(d, s, length(s));
    }

    /* to_utf16 */

    template <typename dT, typename iT>
    inline utfcvt_result utf16::to_utf16(dT& d, iT s, iT e)
    {
        return append<utf16, utf16, dT, iT>(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf16::to_utf16(dT& d, sT* s, size_t n)
    {
        return to_utf16(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf16::to_utf16(dT& d, sT& s)
    {
        return to_utf16(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf16::to_utf16(dT& d, sT* s)
    {
        return to_utf16(d, s, length(s));
    }

    /* to_utf32 */

    template <typename dT, typename iT>
    inline utfcvt_result utf16::to_utf32(dT& d, iT s, iT e)
    {
        return append<utf32, utf16, dT, iT>(d, s, e);
    }

    template <typename dT, typename iT>
    inline utfcvt_result utf16::to_utf32(dT& d, iT* s, size_t n)
    {
        return to_utf32(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf16::to_utf32(dT& d, sT& s)
    {
        return to_utf32(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf16::to_utf32(dT& d, sT* s)
    {
        return to_utf32(d, s, length(s));
    }

    /*
     * utf32
     */

    /* replacement_character */

    inline std::uint32_t utf32::replacement_character()
    {
        return replace_u32c();
    }

    /* getcodelen */

    template <typename cT>
    inline size_t utf32::getcodelen(cT c_)
    {
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;
        typedef typename utfcvtimpl::template code_type<cT>::comp_t comp_t;

        comp_t c = char_t(c_);

        return c <= 0xffffffffU ? 1 : 0;
    }

    /* getcode */

    template <typename T>
    inline utfcvt_getcres utf32::getcode(T s, T e)
    {
        typedef typename utfcvtimpl::template code_type<T>::char_t char_t;

        if (s == e)
            return utfcvt_getcres(0, 0);

        char_t c = char_t(*s);

        return utfcvt_getcres(1, c, getcodelen(c) != 0);
    }

    template <typename sT>
    inline utfcvt_getcres utf32::getcode(sT* s, size_t n)
    {
        return getcode(s, s + n);
    }

    template <typename sT>
    inline utfcvt_getcres utf32::getcode(sT& s)
    {
        return getcode(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_getcres utf32::getcode(sT* s)
    {
        return getcode(s, length(s));
    }

    /* putcodelen */

    template <typename cT>
    inline size_t utf32::putcodelen(cT c_)
    {
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;
        typedef typename utfcvtimpl::template code_type<cT>::comp_t comp_t;

        comp_t c = char_t(c_);

        return c <= UINT32_C(0xffffffff) ? 1 : 0;
    }

    /* putcode */

    template <typename dT, typename cT>
    inline size_t utf32::putcode(dT& d, cT c_)
    {
        typedef typename dT::value_type push_t;
        typedef typename utfcvtimpl::template code_type<cT>::char_t char_t;
        typedef typename utfcvtimpl::template code_type<cT>::comp_t comp_t;

        comp_t c = char_t(c_);

        switch (int(utfcvtimpl::template code_type<dT>::size))
        {
        case 1:
            if (c > 0xff)
                c = utf8::replacement_character();
            break;
        case 2:
            if (c > 0xffff)
                c = utf16::replacement_character();
            break;
        default:
            if (!putcodelen(c))
                c = utf32::replacement_character();
            break;
        }
        d.push_back(push_t(c));
        return 1;
    }

    /* to_utf8len */

    template <typename iT>
    inline utfcvt_result utf32::to_utf8len(iT s, iT e)
    {
        return count<utf8, utf32, iT>(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf32::to_utf8len(sT* s, size_t n)
    {
        return to_utf8len(s, s + n);
    }

    template <typename sT>
    inline utfcvt_result utf32::to_utf8len(sT& s)
    {
        return to_utf8len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf32::to_utf8len(sT* s)
    {
        return to_utf8len(s, length(s));
    }

    /* to_utf16len */

    template <typename iT>
    inline utfcvt_result utf32::to_utf16len(iT s, iT e)
    {
        return count<utf16, utf32, iT>(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf32::to_utf16len(sT* s, size_t n)
    {
        return to_utf16len(s, s + n);
    }

    template <typename sT>
    inline utfcvt_result utf32::to_utf16len(sT& s)
    {
        return to_utf16len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf32::to_utf16len(sT* s)
    {
        return to_utf16len(s, length(s));
    }

    /* to_utf32len */

    template <typename iT>
    inline utfcvt_result utf32::to_utf32len(iT s, iT e)
    {
        return count<utf32, utf32, iT>(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf32::to_utf32len(sT* s, size_t n)
    {
        return to_utf32len(s, s + n);
    }

    template <typename sT>
    inline utfcvt_result utf32::to_utf32len(sT& s)
    {
        return to_utf32len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf32::to_utf32len(sT* s)
    {
        return to_utf32len(s, length(s));
    }

    /* to_utf8 */

    template <typename dT, typename iT>
    inline utfcvt_result utf32::to_utf8(dT& d, iT s, iT e)
    {
        return append<utf8, utf32, dT, iT>(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf32::to_utf8(dT& d, sT* s, size_t n)
    {
        return to_utf8(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf32::to_utf8(dT& d, sT& s)
    {
        return to_utf8(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf32::to_utf8(dT& d, sT* s)
    {
        return to_utf8(d, s, length(s));
    }

    /* to_utf16 */

    template <typename dT, typename iT>
    inline utfcvt_result utf32::to_utf16(dT& d, iT s, iT e)
    {
        return append<utf16, utf32, dT, iT>(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf32::to_utf16(dT& d, sT* s, size_t n)
    {
        return to_utf16(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf32::to_utf16(dT& d, sT& s)
    {
        return to_utf16(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf32::to_utf16(dT& d, sT* s)
    {
        return to_utf16(d, s, length(s));
    }

    /* to_utf32 */

    template <typename dT, typename iT>
    inline utfcvt_result utf32::to_utf32(dT& d, iT s, iT e)
    {
        return append<utf32, utf32, dT, iT>(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf32::to_utf32(dT& d, sT* s, size_t n)
    {
        return to_utf32(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf32::to_utf32(dT& d, sT& s)
    {
        return to_utf32(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf32::to_utf32(dT& d, sT* s)
    {
        return to_utf32(d, s, length(s));
    }

    /*
     * utf
     */

    /* getcodelen */

    template <typename cT>
    inline size_t utf::getcodelen(cT c)
    {
        return utfcvtimpl::template utf_class<cT>::getcodelen(c);
    }

    /* getcode */

    template <typename iT>
    inline utfcvt_getcres utf::getcode(iT s, iT e)
    {
        return utfcvtimpl::template utf_class<iT>::getcode(s, e);
    }

    template <typename sT>
    inline utfcvt_getcres utf::getcode(sT* s, size_t n)
    {
        return getcode(s, s + n);
    }

    template <typename sT>
    inline utfcvt_getcres utf::getcode(sT& s)
    {
        return getcode(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_getcres utf::getcode(sT* s)
    {
        return getcode(s, length(s));
    }

    /* putcodelen */

    template <typename cT>
    inline size_t utf::putcodelen(cT c)
    {
        return utfcvtimpl::template utf_class<cT>::putcodelen(c);
    }

    /* putcode */

    template <typename dT, typename cT>
    inline size_t utf::putcode(dT& d, cT c)
    {
        return utfcvtimpl::template utf_class<dT>::putcode(d, c);
    }

    /* to_utf8len */

    template <typename iT>
    inline utfcvt_result utf::to_utf8len(iT s, iT e)
    {
        return utfcvtimpl::template utf_class<iT>::to_utf8len(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf::to_utf8len(sT* s, size_t n)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf8len(s, n);
    }

    template <typename sT>
    inline utfcvt_result utf::to_utf8len(sT& s)
    {
        return to_utf8len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf::to_utf8len(sT* s)
    {
        return to_utf8len(s, length(s));
    }

    /* to_utf16len */

    template <typename iT>
    inline utfcvt_result utf::to_utf16len(iT s, iT e)
    {
        return utfcvtimpl::template utf_class<iT>::to_utf16len(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf::to_utf16len(sT* s, size_t n)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf16len(s, n);
    }

    template <typename sT>
    inline utfcvt_result utf::to_utf16len(sT& s)
    {
        return to_utf16len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf::to_utf16len(sT* s)
    {
        return to_utf16len(s, length(s));
    }

    /* to_utf32len */

    template <typename iT>
    inline utfcvt_result utf::to_utf32len(iT s, iT e)
    {
        return utfcvtimpl::template utf_class<iT>::to_utf32len(s, e);
    }

    template <typename sT>
    inline utfcvt_result utf::to_utf32len(sT* s, size_t n)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf32len(s, n);
    }

    template <typename sT>
    inline utfcvt_result utf::to_utf32len(sT& s)
    {
        return to_utf32len(s.begin(), s.end());
    }

    template <typename sT>
    inline utfcvt_result utf::to_utf32len(sT* s)
    {
        return to_utf32len(s, length(s));
    }

    /* to_utf8 */

    template <typename dT, typename iT>
    inline utfcvt_result utf::to_utf8(dT& d, iT s, iT e)
    {
        return utfcvtimpl::template utf_class<iT>::to_utf8(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::to_utf8(dT& d, sT* s, size_t n)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf8(d, s, n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::to_utf8(dT& d, sT& s)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf8(d, s);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::to_utf8(dT& d, sT* s)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf8(d, s);
    }

    /* to_utf16 */

    template <typename dT, typename iT>
    inline utfcvt_result utf::to_utf16(dT& d, iT s, iT e)
    {
        return utfcvtimpl::template utf_class<iT>::to_utf16(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::to_utf16(dT& d, sT* s, size_t n)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf16(d, s, n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::to_utf16(dT& d, sT& s)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf16(d, s);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::to_utf16(dT& d, sT* s)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf16(d, s);
    }

    /* to_utf32 */

    template <typename dT, typename iT>
    inline utfcvt_result utf::to_utf32(dT& d, iT s, iT e)
    {
        return utfcvtimpl::template utf_class<iT>::to_utf32(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::to_utf32(dT& d, sT* s, size_t n)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf32(d, s, n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::to_utf32(dT& d, sT& s)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf32(d, s);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::to_utf32(dT& d, sT* s)
    {
        return utfcvtimpl::template utf_class<sT>::to_utf32(d, s);
    }

    /* cvtlen */

    template <typename dT, typename iT>
    inline utfcvt_result utf::cvtlen(dT& d, iT s, iT e)
    {
        (void)d;
        return utfcvtimpl::template converter<dT>::cvtlen(s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::cvtlen(dT& d, sT* s, size_t n)
    {
        return cvtlen(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::cvtlen(dT& d, sT& s)
    {
        return cvtlen(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::cvtlen(dT& d, sT* s)
    {
        return cvtlen(d, s, length(s));
    }

    /* cvt */

    template <typename dT, typename iT>
    inline utfcvt_result utf::cvt(dT& d, iT s, iT e)
    {
        return utfcvtimpl::template converter<dT>::cvt(d, s, e);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::cvt(dT& d, sT* s, size_t n)
    {
        return cvt(d, s, s + n);
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::cvt(dT& d, sT& s)
    {
        return cvt(d, s.begin(), s.end());
    }

    template <typename dT, typename sT>
    inline utfcvt_result utf::cvt(dT& d, sT* s)
    {
        return cvt(d, s, length(s));
    }

    namespace utfcvtimpl
    {
        /*
         *
         */

        template <typename T>
        int clzN(T x)
        {
            int b = sizeof(T) << 3;
            int r = 1;
            T y = 0;

            if ((b >>= 1)) { if (!(y = x >> b)) r += b; else x = y; }
            if ((b >>= 1)) { if (!(y = x >> b)) r += b; else x = y; }
            if ((b >>= 1)) { if (!(y = x >> b)) r += b; else x = y; }
            if ((b >>= 1)) { if (!(y = x >> b)) r += b; else x = y; }
            if ((b >>= 1)) { if (!(y = x >> b)) r += b; else x = y; }
            if ((b >>= 1)) { if (!(y = x >> b)) r += b; else x = y; }
            return r - x;
        }

        template <typename T>
        inline int clz32(T t)
        {
            std::uint32_t x(t);
#if utfcvt_compiler_cxx20
            return std::countl_zero(x);
#elif utfcvt_compiler_builtin_ia32_lzcnt_u32
            int r = __builtin_ia32_lzcnt_u32(x);
            return x ? r : 32;
#elif utfcvt_compiler_builtin_clz
            int r = __builtin_clz(x);
            return x ? r : 32;
#elif utfcvt_compiler_bsr
            unsigned long r;
            return _BitScanReverse(&r, x) ? 31 - r : 32;
#else /* !utfcvt_compiler_clz */
            return clzN(x);
#endif
        }

        /*
         * cvt_utf8
         */

        template <typename dT>
        template <typename iT>
        inline utfcvt_result cvt_utf8<dT>::cvtlen(iT s, iT e)
        {
            return utf_class<iT>::to_utf8len(s, e);
        }

        template <typename dT>
        template <typename iT>
        inline utfcvt_result cvt_utf8<dT>::cvt(dT& d, iT s, iT e)
        {
            return utf_class<iT>::to_utf8(d, s, e);
        }

        /*
         * cvt_utf16
         */

        template <typename dT>
        template <typename iT>
        inline utfcvt_result cvt_utf16<dT>::cvtlen(iT s, iT e)
        {
            return utf_class<iT>::to_utf16len(s, e);
        }

        template <typename dT>
        template <typename iT>
        inline utfcvt_result cvt_utf16<dT>::cvt(dT& d, iT s, iT e)
        {
            return utf_class<iT>::to_utf16(d, s, e);
        }

        /*
         * cvt_utf32
         */

        template <typename dT>
        template <typename iT>
        inline utfcvt_result cvt_utf32<dT>::cvtlen(iT s, iT e)
        {
            return utf_class<iT>::to_utf32len(s, e);
        }

        template <typename dT>
        template <typename iT>
        inline utfcvt_result cvt_utf32<dT>::cvt(dT& d, iT s, iT e)
        {
            return utf_class<iT>::to_utf32(d, s, e);
        }

    } //utfcvtimpl
} // utfcvt

///////////////////
// Local Variables:
// c-basic-offset: 4
// indent-tabs-mode: nil
// tab-width: 4
// End:
///////
