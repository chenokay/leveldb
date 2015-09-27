VERSION = 0.2.1

CC = gcc
CPP = g++
AR = ar

THRIFT_SYS_DIR=/usr/local/include/thrift
BOOST_DIR=/usr/local/include/boost

OUTPUT_DIR = output/
LIB_DIR = /usr/local/domob/cpplib/
DOMOB_STL_LIB_DIR = $(LIB_DIR)/domob-stl/1.26.3
#DOMOB_STL_LIB_DIR = /home/chenzhen/git_workspace/domob-stl-cpp/output
THRIFT_DIR = $(LIB_DIR)/domob-thrift-interface/2.75.5/
DM303_DIR = /usr/local/domob/cpplib/dm303/1.0.0.0

APP_OUTPUT = $(OUTPUT_DIR)/bin/saildb

SYS_LIB_DIR = /usr/local/lib

LFLAGS = -L${SYS_LIB_DIR} \
	-lthrift -lcrypto -ldomoblib \
	-llog4cpp -lthriftnb\
	-levent

CFLAGS = ${CFLAGS_BASIC} 

CFLAGS_BASIC = -g -O2 -W -Wall -Wpointer-arith -fPIC \
	       -Wno-unused-parameter -Wunused-function -Wunused-variable \
	       -Wunused-value

INCLUDEDIR =  -I$(DOMOB_STL_LIB_DIR)/include -I$(DM303_DIR)/include -I$(THRIFT_DIR)/include/domob_thrift  -I$(THRIFT_DIR)/include -I$(THRIFT_SYS_DIR) -I$(BOOST_DIR) -I. 
BASE_LDLIB =  -ldomoblib -llog4cpp -lthrift -lboost_regex -lcurl -liconv -lcrypto -lm -lz -lpthread -lboost_filesystem -lrt -levent -ldomob_thrift_interface -ldm303 -lleveldb
LIBDIR = -L$(DOMOB_STL_LIB_DIR)/lib -L$(DM303_DIR)/lib -L$(THRIFT_DIR)/lib -L.

default: dir saildb

SRC=./
INTERFACE=./thrift_inerface/
SRC_CPPCLASS=$(wildcard $(SRC)/*.cpp)
SRC_CPPCLASS += $(wildcard $(INTERFACE)/*.cpp)
OBJS=$(SRC_CPPCLASS:.cpp=.o)

dir:
	mkdir -p output/include output/bin

saildb: $(OBJS) 
	$(CPP) ${CFLAGS} -o $(APP_OUTPUT) $(OBJS) ${LFLAGS} $(INCLUDEDIR) $(LIBDIR) $(BASE_LDLIB)

%.o : %.cpp
	$(CPP) -c -o $@ $< ${CFLAGS} $(INCLUDEDIR) $(LIBDIR) $(BASE_LDLIB) 



.PHONY: clean
clean:
	-rm -rf  output *.o 
