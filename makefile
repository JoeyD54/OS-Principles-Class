# Compiler variables
CCFLAGS = -ansi -Wall

# Rule to link object code files to create executable file
Assign4: assign4.o Process.o Queue.o 
	g++ $(CCFLAGS) -o Assign4 assign4.o Queue.o Process.o

# Rules to compile source code files to object code
assign4.o: assign4.cpp Queue.h Process.h Constants.h
	g++ $(CCFLAGS) -c assign4.cpp

Queue.o: Queue.cpp Queue.h
	g++ $(CCFLAGS) -c Queue.cpp

Process.o: Process.cpp Process.h
	g++ $(CCFLAGS) -c Process.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign4

