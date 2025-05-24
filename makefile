CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRCS = src/main.cpp src/UI.cpp src/Tracker.cpp src/Mistake.cpp src/FileHandler.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = mainApp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)