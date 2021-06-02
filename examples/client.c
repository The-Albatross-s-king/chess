#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include "board.h"
#include "client.h"

int main(){
	client("172.26.118.100", "2048");
	return 0;
}
