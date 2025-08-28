# ***
# *** Do NOT modify this file
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR   = -Wvla -Werror
CFLAGS  = -std=c11 -g -O0 $(WARNING) $(ERROR)
CC     = gcc  

SRCS = hw5.c student.c
OBJS = $(SRCS:%.c=%.o)

hw5: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o hw5

# Pattern rule: build .o files with debug flags
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

testall: test1 test2 test3 test4

test1: hw5
	./hw5 testcases/input1 output_id1.txt output_name1.txt
	diff -w output_id1.txt expected/id1
	diff -w output_name1.txt expected/name1

test2: hw5
	./hw5 testcases/input2 output_id2.txt output_name2.txt
	diff -w output_id2.txt expected/id2
	diff -w output_name2.txt expected/name2

test3: hw5
	./hw5 testcases/input3 output_id3.txt output_name3.txt
	diff -w output_id3.txt expected/id3
	diff -w output_name3.txt expected/name3

test4: hw5
	./hw5 testcases/input4 output_id4.txt output_name4.txt
	diff -w output_id4.txt expected/id4
	diff -w output_name4.txt expected/name4

testmemory: hw5
	valgrind ./hw5 testcases/input4 output_id4.txt output_name4.txt

clean:
	rm -rf *.o hw5 *.txt
