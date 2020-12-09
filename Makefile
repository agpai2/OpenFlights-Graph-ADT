EXENAME = main
OBJS = readFromFile.o main.o Graph.o Airport.o menu.o

# Use the cs225 makefile template:
include cs225/make/cs225.mk


CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp 

readFromFile.o: util/readFromFile.cpp util/readFromFile.hpp
	$(CXX) $(CXXFLAGS) util/readFromFile.cpp

menu.o: util/menu.cpp util/menu.hpp
	$(CXX) $(CXXFLAGS) util/menu.cpp
	
Graph.o: Graph.cpp Graph.h
	$(CXX) $(CXXFLAGS) Graph.cpp

Airport.o: Airport.cpp Airport.h
	$(CXX) $(CXXFLAGS) Airport.cpp

test: output_msg tests.o readFromFile.o Graph.o Airport.o
	$(LD) tests.o readFromFile.o Graph.o Airport.o $(LDFLAGS) -o test

tests.o: tests/tests.cpp catch/catch.hpp Graph.h Airport.h util/readFromFile.hpp
	$(CXX) $(CXXFLAGS) tests/tests.cpp



clean:
	-rm -f *.o $(EXENAME) test

.PHONY: all test clean output_msg