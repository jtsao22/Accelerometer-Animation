CXX            = g++
DEFINES        = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CXXFLAGS       = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH        = -I/usr/share/qtr/mkspecs/linux-g++ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I.
LFLAGS         = -Wl,-O1
LIBS           = $(SUBLIBS) -L/usr/lib -lCoin -lSoQt -lQtGui -lQtCore -lpthread
sceneGenerator: main.cpp gen_scene.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $(LFLAGS) $(LIBS) -o sceneGenerator main.cpp
