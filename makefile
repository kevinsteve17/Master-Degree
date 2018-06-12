# ITCR - Diego Herrera

SYSCDIR=/usr/local/systemc-2.3.2
LDFLAGS= -L$(SYSCDIR)/lib-linux -lsystemc -lm
CXXFLAGS=-Wno-deprecated -I$(SYSCDIR)/include

all:
	g++ $(CXXFLAGS) main.cpp sockit_owm.* $(LDFLAGS) -o sockit_owm.out

