CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET  = hopfield
SRCS    = main.cpp pattern.cpp hopfield.cpp
OBJS    = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)