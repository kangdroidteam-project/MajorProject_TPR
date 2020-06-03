CC=g++-9
CFLAGS=-Wall -O3
TARGET=app.out
OBJS=Date.o \
	FileIO.o \
	Manager.o \
	Schedule.o \
	TimeCalculator.o \
	main.o
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -rf ./*.out ./*.o