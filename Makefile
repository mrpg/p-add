CXX = clang++
LD = ld
CXXFLAGS = -Wall -O3 -s -std=gnu++0x -lgmp -lgmpxx -lpthread
INSTALL_PROGRAM = install
BINDIR = /usr/bin

all: p-add

clean:
		rm p-add

p-add: main.cpp
		$(CXX) $(CXXFLAGS) main.cpp -o p-add

install: p-add
		$(INSTALL_PROGRAM) p-add $(BINDIR)/p-add
