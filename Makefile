CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET  = hopfield
SRCS    = main.cpp pattern.cpp hopfield.cpp
OBJS    = $(SRCS:.cpp=.o)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)