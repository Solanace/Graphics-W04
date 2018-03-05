#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main(int argc, char **argv) {
	screen s;
	color c;
	struct matrix *trans, *edges;
	trans = new_matrix(4, 4);
	edges = new_matrix(4, 1);

	if (argc == 2) parse_file(argv[1], trans, edges, s);
	else parse_file("stdin", trans, edges, s);
	
	free_matrix(trans);
	free_matrix(edges);
}  
