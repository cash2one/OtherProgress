# $Id: Makefile 53 2013-04-17 05:03:41Z zhongjunwei $

#CXX = /usr/bin/g++
CXXFLAGS = -std=gnu++0x $(FIR_COMPILE_OPT) -I../base -I../protocol -I../base/curl -I../base/hiredis -I../tbxcpp -I../protocpp -Wall -D_GNU_SOURCE -D_REENTRANT `mysql_config --cflags` `xml2-config --cflags`
CXXLFLAGS = $(FIR_COMPILE_OPT) -Wall -L../base -lfir -lcurl -ljson -lencdec -lhiredis -lpthread -lrt -lz -L../xml -lxml -L../tbxcpp -ltbx -lprotobuf -lproto `mysql_config --libs_r` `xml2-config --libs` -llog4cxx
LIB_FIR = ../base/libfir.a
LIB_CRYPTO = ../base/libcrypto.a

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(SRCS:%.cpp=.%.d)

ALL_TARGETS = allzoneserver

all: $(ALL_TARGETS)

include $(DEPS)
$(DEPS): .%.d: %.cpp
	@$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -f $@.$$$$

$(OBJS): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(ALL_TARGETS): $(OBJS) $(LIB_FIR) $(LIB_CRYPTO)
	$(CXX) $(OBJS) -o $@ $(CXXLFLAGS)

clean:
	@rm -rf *.o .*.d $(ALL_TARGETS) core *~

