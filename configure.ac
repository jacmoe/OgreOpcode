dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([ogreopcode], [0.1.3])

OPCODE_VERSION_INFO=1:0:0
AC_SUBST(OPCODE_VERSION_INFO)
OGREOPCODE_VERSION_INFO=0:1:0
AC_SUBST(OGREOPCODE_VERSION_INFO)


AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE

# Checks for programs.
AC_ISC_POSIX
AC_PROG_CXX
AM_PROG_CC_STDC
AC_PROG_LIBTOOL

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([float.h stdlib.h string.h stddef.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_TYPES([ptrdiff_t])
AC_C_CONST
AC_C_INLINE
AC_C_VOLATILE
AC_HEADER_STDBOOL
AC_STRUCT_TM
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([floor memmove memset sqrt strchr strstr])

PKG_CHECK_MODULES(OGRE, [OGRE >= 1.0.0])
AC_SUBST(OGRE_CFLAGS)
AC_SUBST(OGRE_LIBS)

AC_CONFIG_FILES([
Makefile
include/Makefile
include/Opcode/Ice/Makefile
include/Opcode/Makefile
src/Makefile
src/Opcode/Makefile
ogreopcode.pc
])

AC_OUTPUT
