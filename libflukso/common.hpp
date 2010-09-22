#ifndef LIBFLUKSO_COMMON_HPP
#define LIBFLUKSO_COMMON_HPP 1

/* Include TR1 shared ptrs in a portable way. */
#include <cstddef> // for __GLIBCXX__
#ifdef __GLIBCXX__
#  include <tr1/memory>
#else
#  ifdef __IBMCPP__
#    define __IBMCPP_TR1__
#  endif
#  include <memory>
#endif

#endif /* LIBFLUKSO_COMMON_HPP */

