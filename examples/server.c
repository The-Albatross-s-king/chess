#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "board.h"
#include "single_server.h"

int main(){
	server("2048", WHITE);
	return 0;
}
