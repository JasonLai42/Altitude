# Altitude Makefile

CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -g
ALTITUDE_OBJ = altitude.o
HEADER_FILES = camera.hpp color.hpp entity_list.hpp sphere.hpp material.hpp

#submission = 204995126.tar.gz
#submission_files = client.cpp server.cpp $(HEADER_FILES) Makefile README

default: altitude

altitude: $(ALTITUDE_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

altitude.o: altitude.cpp $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) -c altitude.cpp

#dist:
#	@tar -czf $(submission) $(submission_files)

clean:
	@rm -f altitude *.o

squeaky:
	@rm -f altitude *.o *.ppm
