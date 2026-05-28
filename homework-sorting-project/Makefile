CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGET = sorting_project

SRC = src/main.cpp \
      src/insertion_sort.cpp \
      src/quick_sort.cpp \
      src/merge_sort.cpp \
      src/heap_sort.cpp \
      src/composite_sort.cpp \
      src/data_generator.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe *.o
