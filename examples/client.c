#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "board.h"
#include "client.h"

int main(){
	client("localhost", "2048", BLACK);
	return 0;
}
