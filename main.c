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
	struct matrix *edges, *trans, *temp;

	clear_screen(s);
	c.red = 200;
	c.blue = 75;
	c.green = 20;
	edges = new_matrix(4, 1);
	trans = new_matrix(4, 4);
	ident(trans);

	temp = make_translate(-100, -100, 0);
	matrix_mult(temp, trans);
	print_matrix(temp);
	print_matrix(trans);
	/*
	temp = make_scale(2, 2, 1);
	matrix_mult(temp, trans);
	temp = make_translate(100, 100, 0);
	matrix_mult(temp, trans);
	*/

	// Square
	add_edge(edges, 100, 100, 0, 150, 100, 0);
	add_edge(edges, 150, 150, 0, 150, 100, 0);
	add_edge(edges, 100, 150, 0, 150, 150, 0);
	add_edge(edges, 100, 100, 0, 100, 150, 0);

	draw_lines(edges, s, c);
	
	c.red = 100;
	matrix_mult(trans, edges);
	draw_lines(edges, s, c);
	display(s);

	free_matrix(edges);
	free_matrix(trans);
	free_matrix(temp);
}  
