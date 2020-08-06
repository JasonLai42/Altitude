# Altitude Makefile

CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -g
ALTITUDE_OBJ = altitude.o

#submission = 204995126.tar.gz
header_files = constants.hpp vector.hpp ray.hpp entity.hpp sphere.hpp entity_list.hpp camera.hpp
#submission_files = client.cpp server.cpp $(header_files) Makefile README

default: altitude

altitude: $(ALTITUDE_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

altitude.o: altitude.cpp constants.hpp vector.hpp ray.hpp sphere.hpp entity_list.hpp camera.hpp
	$(CXX) $(CXXFLAGS) -c altitude.cpp

#dist:
#	@tar -czf $(submission) $(submission_files)

clean:
	@rm -f altitude *.o

squeaky:
	@rm -f altitude *.o *.ppm
