CXX:=g++
CXXFLAGS:=-g -Wall -std=c++20

SRC:=./src
OBJ:=./obj

SRCS:=$(wildcard $(SRC)/*.cpp)
OBJS:=$(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
INCLUDE:=-I$(SRC)

APP:=compiler

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

.PHONY: all
all: $(APP)
$(APP): $(APP).cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $< $(OBJS)

test: $(APP)
	./$(APP)

clean:
	rm -rf $(APP) $(OBJS)
