#!/bin/bash

if [ $# -ne 2 ]
then
	cat <<___
Usage: add_example.sh <action> <file>

<action> is one of: {add, remove}
<name> is the name of the one source example

If I have example1.cpp, and I want to be able to compile it easily,

./chg_make.sh add example1
make example1
___
	exit 1;
fi

case $1 in
add)
if [ ! -e Makefile ]
then
cat > Makefile <<___
CXX            = g++
DEFINES        = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CXXFLAGS       = -pipe -O2 -Wall -W -D_REENTRANT \$(DEFINES)
INCPATH        = -I/usr/share/qtr/mkspecs/linux-g++ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I.
LFLAGS         = -Wl,-O1
LIBS           = \$(SUBLIBS) -L/usr/lib -lCoin -lSoQt -lQtGui -lQtCore -lpthread
___
fi
cat >> Makefile <<___
$2: $2.cpp
	\$(CXX) \$(CXXFLAGS) \$(INCPATH) \$(LFLAGS) \$(LIBS) -o $2 $2.cpp
___
;;

remove)
cat Makefile | sed "/$2\.cpp/d" > temp
mv temp Makefile
;;

*)
   cat <<___
Usage: chg_make.sh <action> <file>

<action> is one of: {add, remove}
<name> is the name of the one source example

If I have example1.cpp, and I want to be able to compile it easily,

./add_example.sh add example1
make example1
___
   exit 1;
esac
