CPPFLAGS=
CXXFLAGS=-g -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 $(OPTIFLAG) $(SANFLAGS)
OPTIFLAG= -O2
LDFLAGS=$(SANFLAGS)
LIBS= -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

OBJECTS= glad.o Main.o

SANFLAGS=-fsanitize=address -fsanitize=leak -fsanitize=undefined 

.PHONY: all
all: g

g: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -rf *.o g


## MAKE MAKEFILE AUTOMATICALLY FIND HEADER FILES AND SUCH LIKE IN THE "Compiler" MAKEFILE ##