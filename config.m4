dnl $Id$
dnl config.m4 for extension HyperMobile

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(HyperMobile, for HyperMobile support,
Make sure that the comment is aligned:
[  --with-HyperMobile             Include HyperMobile support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(HyperMobile, whether to enable HyperMobile support,
dnl Make sure that the comment is aligned:
dnl [  --enable-HyperMobile           Enable HyperMobile support])

if test "$PHP_HYPERMOBILE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-HyperMobile -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/HyperMobile.h"  # you most likely want to change this
  dnl if test -r $PHP_HYPERMOBILE/$SEARCH_FOR; then # path given as parameter
  dnl   HYPERMOBILE_DIR=$PHP_HYPERMOBILE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for HyperMobile files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       HYPERMOBILE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$HYPERMOBILE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the HyperMobile distribution])
  dnl fi

  dnl # --with-HyperMobile -> add include path
  dnl PHP_ADD_INCLUDE($HYPERMOBILE_DIR/include)

  dnl # --with-HyperMobile -> check for lib and symbol presence
  dnl LIBNAME=HyperMobile # you may want to change this
  dnl LIBSYMBOL=HyperMobile # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $HYPERMOBILE_DIR/lib, HYPERMOBILE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_HYPERMOBILELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong HyperMobile lib version or lib not found])
  dnl ],[
  dnl   -L$HYPERMOBILE_DIR/lib -lm -ldl
  dnl ])
  dnl
  dnl PHP_SUBST(HYPERMOBILE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(HyperMobile, HyperMobile.c, $ext_shared)
fi
