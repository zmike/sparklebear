gcc -Wall -g -ggdb3 -rdynamic $(pkg-config --cflags --libs elementary libxml-2.0) -o sparklebear main.c
