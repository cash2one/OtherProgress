# $Id: Makefile 67 2013-04-23 09:44:20Z pengqiangqiang $

#CXX = /usr/bin/g++
CXXFLAGS = -std=gnu++0x $(FIR_COMPILE_OPT) -Wall -g3 -I../base -I../base/curl -I../protocol -I../common -I../tbxcpp -I../base/EncDec -I../base/hiredis -I../protocpp -Wno-deprecated -Wall -D_GNU_SOURCE -D_REENTRANT `mysql_config --cflags` `xml2-config --cflags`
CXXLFLAGS = $(FIR_COMPILE_OPT) -Wall -L../tbxcpp -ltbx `mysql_config --libs_r` `xml2-config --libs` -llog4cxx -L../base -lfir -lencdec -lpthread -lrt  -ljson -lz -lcurl -lhiredis -lprotobuf -lproto -L../xml -lxml 
LIB_FIR = ../tbxcpp/libtbx.a ../base/libfir.a

.PHONY : clean

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(SRCS:%.cpp=.%.d)

ALL_TARGETS = sceneserver

all: $(ALL_TARGETS)

include $(DEPS)
$(DEPS): .%.d: %.cpp
	@$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -f $@.$$$$

$(OBJS): %.o: %.cpp 
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(ALL_TARGETS): $(OBJS) $(LIB_FIR)
	$(CXX) $(OBJS) -o $@ $(CXXLFLAGS)

clean:
	@rm -rf *.o .*.d $(ALL_TARGETS) core *~

