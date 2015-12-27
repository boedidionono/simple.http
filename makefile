###############################################################
#
# Purpose: Makefile for "test"
# Author.: boedh
# Version: 0.1
# License: GPL
#
###############################################################

TARGET = test_server
INCLUDE_DIRS = -I/usr/local/include

CXX = g++
#CXXFLAGS += -O3 -DLINUX -Wall $(INCLUDE_DIRS)
CXXFLAGS += -O2 -DDEBUG -DLINUX -Wall $(INCLUDE_DIRS)
LFLAGS += -lpthread

#OPENCV_LIBRARY = -L"/usr/local/lib" -lopencv_core -lopencv_highgui -lopencv_imgproc

OBJECTS = main.o sServer.o confreader.o debug.o mimedictionary.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(OBJECTS) -o $(TARGET) $(OPENCV_LIBRARY)
	chmod 755 $(TARGET)
clean:
	rm -f *.a *.o $(TARGET) core *~ *.so *.lo
