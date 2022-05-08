#simple makefile
path=./obj
p.o=$(path)/player.o
w.o=$(path)/wheel.o

all: main

main: main.c $(w.o) $(p.o)
	gcc -o main main.c $(w.o) $(p.o)

tests: tests.c $(w.o) $(p.o)
	gcc -o tests tests.c $(w.o) $(p.o)

$(w.o): wheel.c wheel.h 
	gcc -o $(w.o) -c wheel.c 

$(p.o): player.c player.h
	gcc -o $(p.o) -c player.c

clean:
	rm -rf tests $(path)/*.o
