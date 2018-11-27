#ifndef PTWARNINGS_H
#define PTWARNINGS_H

#define PT_DO_PRAGMA(text)                      _Pragma(#text)
#if defined(_MSC_VER) && _MSC_VER >= 1500
#  undef PT_DO_PRAGMA                           /* not needed */
#  define PT_WARNING_PUSH                       __pragma(warning(push))
#  define PT_WARNING_POP                        __pragma(warning(pop))
#  define PT_WARNING_DISABLE_MSVC(number)       __pragma(warning(disable: number))
#  define PT_WARNING_DISABLE_CLANG(text)
#  define PT_WARNING_DISABLE_GCC(text)
#elif defined(__clang__)
#  define PT_WARNING_PUSH                       PT_DO_PRAGMA(clang diagnostic push)
#  define PT_WARNING_POP                        PT_DO_PRAGMA(clang diagnostic pop)
#  define PT_WARNING_DISABLE_CLANG(text)        PT_DO_PRAGMA(clang diagnostic ignored text)
#  define PT_WARNING_DISABLE_GCC(text)
#  define PT_WARNING_DISABLE_MSVC(number)
#elif defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__ >= 406)
#  define PT_WARNING_PUSH                       PT_DO_PRAGMA(GCC diagnostic push)
#  define PT_WARNING_POP                        PT_DO_PRAGMA(GCC diagnostic pop)
#  define PT_WARNING_DISABLE_GCC(text)          PT_DO_PRAGMA(GCC diagnostic ignored text)
#  define PT_WARNING_DISABLE_CLANG(text)
#  define PT_WARNING_DISABLE_MSVC(number)
#else       // All other compilers, GCC < 4.6 and MSVC < 2008
#  define PT_WARNING_DISABLE_GCC(text)
#  define PT_WARNING_PUSH
#  define PT_WARNING_POP
#  define PT_WARNING_DISABLE_MSVC(number)
#  define PT_WARNING_DISABLE_CLANG(text)
#  define PT_WARNING_DISABLE_GCC(text)
#endif

#if defined(__clang__)
#  define PT_NO_OVERRIDE_WARNING      PT_WARNING_DISABLE_CLANG("-Winconsistent-missing-override")
#elif defined(__GNUC__) && __GNUC_MINOR__ >= 510
#  define PT_NO_OVERRIDE_WARNING      PT_WARNING_DISABLE_GCC("-Wsuggest-override")
#else
#  define PT_NO_OVERRIDE_WARNING
#endif

#endif // PTWARNINGS_H
