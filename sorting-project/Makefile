CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGET = sorting_project

SRC = src/main.cpp src/sorting.cpp src/data_generator.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe *.o
