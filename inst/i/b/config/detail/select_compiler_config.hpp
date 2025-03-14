//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Martin Wille 2003.
//  (C) Copyright Guillaume Melquiond 2003.
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//   http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for most recent version.

// locate which compiler we are using and define
// BOOST_COMPILER_CONFIG as needed: 

#if defined __CUDACC__
//  NVIDIA CUDA C++ compiler for GPU
#   include "b/config/compiler/nvcc.hpp"

#endif

#if defined(__GCCXML__)
// GCC-XML emulates other compilers, it has to appear first here!
#   define BOOST_COMPILER_CONFIG "b/config/compiler/gcc_xml.hpp"

#elif defined(_CRAYC)
// EDG based Cray compiler:
#   define BOOST_COMPILER_CONFIG "b/config/compiler/cray.hpp"

#elif defined __COMO__
//  Comeau C++
#   define BOOST_COMPILER_CONFIG "b/config/compiler/comeau.hpp"

#elif defined(__PATHSCALE__) && (__PATHCC__ >= 4)
// PathScale EKOPath compiler (has to come before clang and gcc)
#   define BOOST_COMPILER_CONFIG "b/config/compiler/pathscale.hpp"

#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
//  Intel
#   define BOOST_COMPILER_CONFIG "b/config/compiler/intel.hpp"

#elif defined __clang__ && !defined(__ibmxl__) && !defined(__CODEGEARC__)
//  Clang C++ emulates GCC, so it has to appear early.
#   define BOOST_COMPILER_CONFIG "b/config/compiler/clang.hpp"

#elif defined __DMC__
//  Digital Mars C++
#   define BOOST_COMPILER_CONFIG "b/config/compiler/digitalmars.hpp"

#elif defined __DCC__
//  Wind River Diab C++
#   define BOOST_COMPILER_CONFIG "b/config/compiler/diab.hpp"

#elif defined(__PGI)
//  Portland Group Inc.
#   define BOOST_COMPILER_CONFIG "b/config/compiler/pgi.hpp"

# elif defined(__GNUC__) && !defined(__ibmxl__)
//  GNU C++:
#   define BOOST_COMPILER_CONFIG "b/config/compiler/gcc.hpp"

#elif defined __KCC
//  Kai C++
#   define BOOST_COMPILER_CONFIG "b/config/compiler/kai.hpp"

#elif defined __sgi
//  SGI MIPSpro C++
#   define BOOST_COMPILER_CONFIG "b/config/compiler/sgi_mipspro.hpp"

#elif defined __DECCXX
//  Compaq Tru64 Unix cxx
#   define BOOST_COMPILER_CONFIG "b/config/compiler/compaq_cxx.hpp"

#elif defined __ghs
//  Greenhills C++
#   define BOOST_COMPILER_CONFIG "b/config/compiler/greenhills.hpp"

#elif defined __CODEGEARC__
//  CodeGear - must be checked for before Borland
#   define BOOST_COMPILER_CONFIG "b/config/compiler/codegear.hpp"

#elif defined __BORLANDC__
//  Borland
#   define BOOST_COMPILER_CONFIG "b/config/compiler/borland.hpp"

#elif defined  __MWERKS__
//  Metrowerks CodeWarrior
#   define BOOST_COMPILER_CONFIG "b/config/compiler/metrowerks.hpp"

#elif defined  __SUNPRO_CC
//  Sun Workshop Compiler C++
#   define BOOST_COMPILER_CONFIG "b/config/compiler/sunpro_cc.hpp"

#elif defined __HP_aCC
//  HP aCC
#   define BOOST_COMPILER_CONFIG "b/config/compiler/hp_acc.hpp"

#elif defined(__MRC__) || defined(__SC__)
//  MPW MrCpp or SCpp
#   define BOOST_COMPILER_CONFIG "b/config/compiler/mpw.hpp"

#elif defined(__IBMCPP__) && defined(__COMPILER_VER__) && defined(__MVS__)
//  IBM z/OS XL C/C++
#   define BOOST_COMPILER_CONFIG "b/config/compiler/xlcpp_zos.hpp"

#elif defined(__ibmxl__)
//  IBM XL C/C++ for Linux (Little Endian)
#   define BOOST_COMPILER_CONFIG "b/config/compiler/xlcpp.hpp"

#elif defined(__IBMCPP__)
//  IBM Visual Age or IBM XL C/C++ for Linux (Big Endian)
#   define BOOST_COMPILER_CONFIG "b/config/compiler/vacpp.hpp"

#elif defined _MSC_VER
//  Microsoft Visual C++
//
//  Must remain the last #elif since some other vendors (Metrowerks, for
//  example) also #define _MSC_VER
#   define BOOST_COMPILER_CONFIG "b/config/compiler/visualc.hpp"

#elif defined (BOOST_ASSERT_CONFIG)
// this must come last - generate an error if we don't
// recognise the compiler:
#  error "Unknown compiler - please configure (http://www.boost.org/libs/config/config.htm#configuring) and report the results to the main boost mailing list (http://www.boost.org/more/mailing_lists.htm#main)"

#endif

#if 0
//
// This section allows dependency scanners to find all the headers we *might* include:
//
#include <b/config/compiler/gcc_xml.hpp>
#include <b/config/compiler/cray.hpp>
#include <b/config/compiler/comeau.hpp>
#include <b/config/compiler/pathscale.hpp>
#include <b/config/compiler/intel.hpp>
#include <b/config/compiler/clang.hpp>
#include <b/config/compiler/digitalmars.hpp>
#include <b/config/compiler/gcc.hpp>
#include <b/config/compiler/kai.hpp>
#include <b/config/compiler/sgi_mipspro.hpp>
#include <b/config/compiler/compaq_cxx.hpp>
#include <b/config/compiler/greenhills.hpp>
#include <b/config/compiler/codegear.hpp>
#include <b/config/compiler/borland.hpp>
#include <b/config/compiler/metrowerks.hpp>
#include <b/config/compiler/sunpro_cc.hpp>
#include <b/config/compiler/hp_acc.hpp>
#include <b/config/compiler/mpw.hpp>
#include <b/config/compiler/xlcpp_zos.hpp>
#include <b/config/compiler/xlcpp.hpp>
#include <b/config/compiler/vacpp.hpp>
#include <b/config/compiler/pgi.hpp>
#include <b/config/compiler/visualc.hpp>

#endif

