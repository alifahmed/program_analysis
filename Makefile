.PHONY: all clean

BOOST_ROOT=$(HOME)/_installs/boost_1_58_inst

all:
	g++ -Wall -std=c++11 -O3 -g panalysis.cpp -o panalysis -I$(DYNINST_ROOT)/include -I$(BOOST_ROOT)/include -Wno-deprecated-declarations -L$(DYNINST_ROOT)/lib -ldyninstAPI

clean:
	rm -rf panalysis

