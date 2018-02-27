include ../make.make

NAME := gtest

EXECUTABLE := gtest

LDFLAGS := -lpthread -lgtest -lgtest_main -L$(GTEST_PATH)/lib/ -lintervaltree -L../release/

INCLUDE := -I$(GTEST_PATH)/include/ -I../src/

CFLAGS := -c -Wall

SRCS := IntervalTreeTest.cc main.cc

OBJECTS := $(SRCS:.cc=.o)

all: $(SRCS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o: 
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

test: $(EXECUTABLE)
	./run_test.sh


