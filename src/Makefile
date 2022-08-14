FLAGS = -std=c11 -Wall -Wextra -Werror

all: my_cat

clean: 
	rm -f my_cat my_cat.o

my_cat: my_cat.o
	gcc $(FLAGS) my_cat.o -o my_cat

my_cat.o:
	gcc $(FLAGS) -c my_cat.c -o my_cat.o
