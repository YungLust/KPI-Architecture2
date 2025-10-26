# compiler and flags
CXX = g++                        
CXXFLAGS = -std=c++17 -Wall -Werror
LDLIBS =                         # libraries to link with, e.g. -lncurses
OUTPUT = calc
LIB = libcalculator.a

# targets
all: $(LIB) $(OUTPUT)

# Build static library
$(LIB): calculator.o
	ar rcs $(LIB) calculator.o

calculator.o: calculator.cpp calculator.h
	$(CXX) $(CXXFLAGS) -c calculator.cpp -o calculator.o

main.o: main.cpp calculator.cpp calculator.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

$(OUTPUT): calculator.o main.o
	$(CXX) $(CXXFLAGS) calculator.o main.o $(LDLIBS) -o $(OUTPUT)

check:
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.cpp

clean:
	rm -rf $(OUTPUT) $(LIB) *.o 

