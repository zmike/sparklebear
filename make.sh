gcc -Wall -g -ggdb3 -rdynamic $(pkg-config --cflags --libs elementary libxml-2.0) -o sparklebear main.c zrpc_functions.c
gcc -Wall -g -ggdb3 -rdynamic $(pkg-config --cflags --libs elementary libxml-2.0) -o zbind_example zbind_example.c zrpc_functions.c zrpc.c xml.c
