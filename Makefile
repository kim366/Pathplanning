# All credit for `rwildcard` to larskholte @ StackOverflow
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SRC := $(call rwildcard, src/, *.cpp)
OBJ_SRC := $(patsubst %.cpp, obj/%.o, $(SRC))
TST := $(call rwildcard, tst/, *.cpp)
OBJ_TST := $(patsubst %.cpp, obj/%.o, $(TST))
GUI := $(call rwildcard, gui/, *.cpp)
OBJ_GUI := $(patsubst %.cpp, obj/%.o, $(GUI))

SFML_LIB := -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all

all: $(OBJ_SRC) $(OBJ_TST) $(OBJ_GUI) bld/gui bld/test

$(OBJ_SRC): obj/%.o: %.cpp
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -Iinc $< -c -o $@

$(OBJ_TST): obj/%o: %cpp
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -Iinc -c $< -o $@

$(OBJ_GUI): obj/%o: %cpp
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -Iinc $< -c -o $@

bld/gui.exe: $(OBJ_SRC) $(OBJ_GUI)
	@$(CXX) $^ -o $@ $(SFML_LIB)

bld/test.exe: $(OBJ_SRC) $(OBJ_TST)
	@$(CXX) $^ -o $@ $(SFML_LIB)
