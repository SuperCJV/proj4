CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

TASK4_OBJS = proj4_driver.o

proj4_driver.x: $(TASK4_OBJS)
	$(CXX) $(CXXFLAGS) -o proj4_driver.x $(TASK4_OBJS)

proj4_driver.o: proj4_driver.cpp bet.h bet.hpp
	$(CXX) $(CXXFLAGS) -c proj4_driver.cpp

clean:
	rm -f *.o proj4_driver.x

.PHONY: all clean