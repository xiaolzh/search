HEADS=Define.h MemoryBlock.h MemoryPool.h
SRCS=MemoryBlock.cpp MemoryPool.cpp example.cpp
OBJS=$(SRCS:%.cpp=%.o)
DEPS=$(SRCS:%.cpp=%.d)

all:example

example:${OBJS}
	g++ -g -o $@ $^

%.d:%.cpp
	set -e; rm -f $@;\
	g++ -g -MM $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$

sinclude ${DEPS}
clean:
	rm *.o *.d example

