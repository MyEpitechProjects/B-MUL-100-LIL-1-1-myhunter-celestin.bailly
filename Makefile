##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## makefile my_printf manager
##

all:
	gcc -o my_hunter src/*.c -Iinclude -lcsfml-window -lcsfml-graphics -lcsfml-audio -lcsfml-system -lm

clean:
	rm -f src/*.o

fclean:
	rm -f my_hunter

re:
	make all
	make clean
