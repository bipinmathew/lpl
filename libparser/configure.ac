#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([lplparser], [0.1], [bipinmathew@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([parser.h])
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE([enable])

# Checks for programs.
AC_PROG_CC
AC_PROG_LEX
AC_PROG_RANLIB

AM_PROG_AR
# borrowed from a check for gnome in GNU gretl: def. a check for quantlib-config
AC_DEFUN([AC_PROG_LEMONPARSER], [AC_CHECK_PROG(LEMONPARSER,lemon,yes,no)])
AC_PROG_LEMONPARSER
if test "${LEMONPARSER}" == "no" ; then
  AC_MSG_ERROR([Please install lemon parser before trying to build lpllib.])
fi

AC_SUBST([YACC],lemon)

# Checks for libraries.
AC_CHECK_LIB(calg,trie_new)

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
libcol/Makefile
])

AC_CONFIG_SUBDIRS([libcol])
AC_OUTPUT
