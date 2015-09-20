# $Id: Makefile 53 2013-04-17 05:03:41Z zhongjunwei $

#CXX = /usr/bin/g++
CXXFLAGS = -std=gnu++0x $(FIR_COMPILE_OPT) -Wall -I../base -I../protocol -I../tbx -I../protocpp -I../base/hiredis -I../tbxcpp -Wall -D_GNU_SOURCE -D_REENTRANT `mysql_config --cflags` `xml2-config --cflags`
CXXLFLAGS = $(FIR_COMPILE_OPT) -Wall -L../tbxcpp -ltbx `mysql_config --libs_r` `xml2-config --libs` -llog4cxx -L../base -lfir -lhiredis -lencdec -lpthread -lprotobuf -lrt -lz -L../xml -lxml 
LIB_FIR = ../tbxcpp/libtbx.a ../base/libfir.a

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(SRCS:%.cpp=.%.d)

ALL_TARGETS = recordserver

all: $(ALL_TARGETS)

include $(DEPS)
$(DEPS): .%.d: %.cpp
	@$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -f $@.$$$$

$(OBJS): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(ALL_TARGETS): $(OBJS) $(LIB_FIR)
	$(CXX) $(OBJS) -o $@ $(CXXLFLAGS)

clean:
	@rm -rf *.o $(ALL_TARGETS) core *~ .*.d

