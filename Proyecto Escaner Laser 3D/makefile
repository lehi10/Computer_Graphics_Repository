CC = g++
CFLAGS = -std=c++17 -g -Wall
SRCS = main.cpp
PROG = out

OPENCV = `pkg-config --cflags --libs opencv`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
	

