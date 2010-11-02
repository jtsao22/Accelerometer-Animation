CXX            = g++
DEFINES        = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CXXFLAGS       = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH        = -I/usr/share/qtr/mkspecs/linux-g++ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I.
LFLAGS         = -Wl,-O1
LIBS           = $(SUBLIBS) -L/usr/lib -lCoin -lSoQt -lQtGui -lQtCore -lpthread
ex_write: ex_write.cpp
	$(CXX) $(CXXFLAGS) $(INCPATH) $(LFLAGS) $(LIBS) -o ex_write ex_write.cpp
ex_read: ex_read.cpp
	$(CXX) $(CXXFLAGS) $(INCPATH) $(LFLAGS) $(LIBS) -o ex_read ex_read.cpp
ex_sensor: ex_sensor.cpp
	$(CXX) $(CXXFLAGS) $(INCPATH) $(LFLAGS) $(LIBS) -o ex_sensor ex_sensor.cpp
ex_engine: ex_engine.cpp
	$(CXX) $(CXXFLAGS) $(INCPATH) $(LFLAGS) $(LIBS) -o ex_engine ex_engine.cpp
