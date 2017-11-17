# Compiler variables
CCFLAGS = -ansi -Wall

# Rule to link object code files to create executable file
Assign5: assign5.o Process.o Queue.o
	g++ $(CCFLAGS) -o Assign5 assign5.o Process.o Queue.o

# Rules to compile source code files to object code
assign5.o: assign5.cpp Process.h Queue.h
	g++ $(CCFLAGS) -c assign5.cpp

Queue.o: Queue.cpp Queue.h
	g++ $(CCFLAGS) -c Queue.cpp

Process.o: Process.cpp Process.h
	g++ $(CCFLAGS) -c Process.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign5

