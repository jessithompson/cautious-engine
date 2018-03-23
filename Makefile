SOURCE = cmdnm.cpp \
         execute.cpp \
         main.cpp \
         pid.cpp \
         dash.cpp\
         systat.cpp
OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O -std=c++11 -c
CXXFLAGS = $(CFLAGS)

# Fill in special libraries needed here
LIBS = 

.PHONY: clean

# Targets include all, clean, debug, tar

all : dash

dash: $(OBJS)
	$(LINK) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.d core dash

debug: CXXFLAGS += -DDEBUG -g
debug: dash

tar:
	tar cvf dash_Tarball.tar *.cpp *.h Makefile

help:
	@echo "	make main  - same as make all"
	@echo "	make all   - builds the main target"
	@echo "	make       - same as make all"
	@echo "	make clean - remove .o .d core main"
	@echo "	make debug - make all with -g and -DDEBUG"
	@echo "	make tar   - make a tarball of .cpp and .h files"
	@echo "	make help  - this message"

%.d: %.cpp
	@set -e; /usr/bin/rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@

