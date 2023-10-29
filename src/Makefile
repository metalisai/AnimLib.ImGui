CC=gcc
CXX=g++
CXXFLAGS=-Wall -fPIC -ggdb -Og -I../imgui
LIBS=
TARGET=libimgui_animlib.so
SRC=$(wildcard imgui_*.cpp) $(wildcard ../imgui/imgui*.cpp)
OBJ=$(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(LIBS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ)
