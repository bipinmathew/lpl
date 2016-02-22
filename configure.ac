AC_INIT([lpl],[0.1])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign])
AM_MAINTAINER_MODE([disable])
AC_CONFIG_SRCDIR([src])

# Check for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LEX
AC_PROG_RANLIB

AM_PROG_AR


# Checks for libraries.
AC_CHECK_LIB(calg,trie_new)

# borrowed from a check for gnome in GNU gretl: def. a check for quantlib-config
AC_DEFUN([AC_PROG_LEMONPARSER], [AC_CHECK_PROG(LEMONPARSER,lemon,yes,no)])
AC_PROG_LEMONPARSER
if test "${LEMONPARSER}" == "no" ; then
  AC_MSG_ERROR([Please install lemon parser before trying to build lpllib.])
fi

AC_SUBST([YACC],lemon)


AC_CONFIG_FILES([Makefile
src/Makefile
libparser/Makefile
])

AC_OUTPUT
