////////////////////////////////////////////////////////////
//
// typesafe-db
// Copyright (C) 2012-2013 Tom Knapen (tom@failproof.be)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef FP_CONFIG_HPP
#define FP_CONFIG_HPP

////////////////////////////////////////////////////////////
// Define the library version
////////////////////////////////////////////////////////////
#define FP_VERSION_MAJOR 0
#define FP_VERSION_MINOR 1

////////////////////////////////////////////////////////////
// Identify the operating system
////////////////////////////////////////////////////////////
#if (defined(_WIN32) || defined(__WIN32__))
    // Windows
    #define FP_SYSTEM_WINDOWS
    // Prevent MIN / MAX preprocessor macros
    #ifndef NOMINMAX
    #define NOMINMAX
    #endif
#elif (defined(linux) || defined(__linux))
    // Linux
    #define FP_SYSTEM_LINUX
#elif (defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh))
    // MacOS
    #define FP_SYSTEM_MACOS
#elif (defined(__FreeBSD__) || defined(__FreeBSD_kernel__))
    // FreeBSD
    #define FP_SYSTEM_FREEBSD
#else
    // Unsupported system
    #error This operating system is unsupported by typesafe-db
#endif

#if defined(__GNUC__)
    #if defined(__clang)
        #define FP_COMPILER_CLANG
    #elif defined(__INTEL_COMPILER)
        #define FP_COMPILER_INTEL
    #else
        #define FP_COMPILER_GCC
    #endif
#elif defined(__COMO__)
    #define FP_COMPILER_COMEAU
#elif defined(__llvm__)
    #define FP_COMPILER_LLVM
#elif defined(__MWERKS__)
    #define FP_COMPILER_METROWERKS
#elif defined(_MSC_VER)
    #define FP_COMPILER_MSVC
#elif defined(__MINGW32__)
    #define FP_COMPILER_MINGW
#endif

////////////////////////////////////////////////////////////
// Define a portable debug macro
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)
    #define FP_DEBUG
#endif

////////////////////////////////////////////////////////////
// Define a portable constexpr macro
////////////////////////////////////////////////////////////
#if defined(__GXX_EXPERIMENTAL_CXX0X) || (__cplusplus >= 201103L)
    #define CONSTEXPR constexpr
#else
    #define CONSTEXPR
#endif

#if defined(__GNUC__) && (__GNUC__ >= 4)
    #define FP_UNREACHABLE      __builtin_unreachable();
#else
    #define FP_UNREACHABLE
#endif

#if defined(FP_COMPILER_GCC)
    #define FP_DEPRECATED(fn, msg)  fn __attribute__((deprecated(msg)))
#elif defined(FP_COMPILER_MSVC)
    #define FP_DEPRECATED(fn, msg)  __declspec(deprecated(msg)) fn
#else
    #define FP_DEPRECATED(fn, msg)  fn
#endif

////////////////////////////////////////////////////////////
// Define helpers to create portable import / export macros for each module
////////////////////////////////////////////////////////////
#if !defined(FP_STATIC)
    #if defined(FP_SYSTEM_WINDOWS)
        // Windows compilers need specific (and different) keywords for export and import
        #define FP_API_EXPORT   __declspec(dllexport)
        #define FP_API_IMPORT   __declspec(dllimport)
        #define FP_API_LOCAL
    #else // Linux, FreeBSD, Mac OS X
        #if (__GNUC__ >= 4)
            // GCC 4 has special keywords for showing/hiding symbols,
            // the same keyword is used for both importing and exporting
            #define FP_API_EXPORT   __attribute__ ((__visibility__ ("default")))
            #define FP_API_IMPORT   __attribute__ ((__visibility__ ("default")))
            #define FP_API_LOCAL    __attribute__ ((__visibility__ ("hidden")))
        #else
            // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
            #define FP_API_EXPORT
            #define FP_API_IMPORT
            #define FP_API_LOCAL
        #endif
    #endif
#else
    // Static build doesn't need import/export macros
    #define FP_API_EXPORT
    #define FP_API_IMPORT
    #define FP_API_LOCAL
#endif


////////////////////////////////////////////////////////////
// Define portable fixed-size types
////////////////////////////////////////////////////////////
namespace fp {
    // All "common" platforms use the same size for char, short and int
    // (basically there are 3 types for 3 sizes, so no other match is possible),
    // we can use them without doing any kind of check

    // 8 bits integer types
    typedef signed char int8;
    typedef unsigned char uint8;

    // 16 bits integer types
    typedef signed short int16;
    typedef unsigned short uint16;

    // 32 bits integer types
    typedef signed int int32;
    typedef unsigned int uint32;

    // 64 bits integer types
#if defined(FP_COMPILER_MSVC)
    typedef signed __int64 int64;
    typedef unsigned __int64 uin64;
#else
    typedef signed long long int64;
    typedef unsigned long long uint64;
#endif

} // namespace fp
#endif  // FP_CONFIG_HPP