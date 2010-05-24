dir="$(dirname $(readlink -f $0))"
cd "$dir"
gcc -Wall -g -ggdb3 -rdynamic $(pkg-config --cflags --libs elementary libxml-2.0) -o sparklebear \
	change.c create.c list_ops.c main.c panel.c random.c user_actions.c view.c vm_actions.c xml.c zinfo.c zlogin.c zmain.c zrpc.c zrpc_functions.c
gcc -Wall -g -ggdb3 -rdynamic $(pkg-config --cflags --libs elementary libxml-2.0) -o zbind_example zbind_example.c zrpc_functions.c zrpc.c xml.c
cd - &> /dev/null
