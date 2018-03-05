#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point(struct matrix * points, double x, double y, double z) {
	if (points->lastcol == points->cols) grow_matrix(points, points->cols * 20);
	points->lastcol ++;
	points->m[0][points->lastcol - 1] = x;
	points->m[1][points->lastcol - 1] = y;
	points->m[2][points->lastcol - 1] = z;
	points->m[3][points->lastcol - 1] = 1;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge(struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
	add_point(points, x0, y0, z0);
	add_point(points, x1, y1, z1);
}
/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines(struct matrix * points, screen s, color c) {
	int col;
	for (col = 0; col < points->lastcol; col += 2) {
		draw_line(points->m[0][col], points->m[1][col], points->m[0][col + 1], points->m[1][col + 1], s, c);
	}
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
	if (x0 == x1 && y0 == y1) {
		plot(s, c, x0, y1);
		return;
	}
	if (x0 == x1) { // Vertical line
		if (y0 < y1) {
			while (y0 <= y1) {
				plot(s, c, x0, y0);
				y0 ++;
			}
		}
		else draw_line(x1, y1, x0, y0, s, c);
		return;
	}
	if (y0 == y1) { // Horizontal line
		if (x0 < x1) {
			while (x0 <= x1) {
				plot(s, c, x0, y0);
				x0 ++;
			}
		}
		else draw_line(x1, y1, x0, y0, s, c);
		return;
	}
	int A = y1 - y0;
	int B = x0 - x1;
	int x = x0, y = y0;
	int d;
	double m = (y1 - y0) * 1.0 / (x1 - x0);
	if (m == 1) {
		if (x0 < x1) {
			while (x0 <= x1) {
				plot(s, c, x0, y0);
				x0 ++;
				y0 ++;
			}
		}
		else draw_line(x1, y1, x0, y0, s, c);
	}
	else if (m == -1) {
		if (x0 < x1) {
			while (x0 <= x1) {
				plot(s, c, x0, y0);
				x0 ++;
				y0 --;
			}
		}
		else draw_line(x1, y1, x0, y0, s, c);
	}
	else if (m > 0 && m < 1) {
		if (x0 < x1) { // Octant I
			d = 2 * A + B;
			while (x <= x1) {
				plot(s, c, x, y);
				if (d > 0) {
					y ++;
					d += 2 * B;
				}
				x ++;
				d += 2 * A;
			}
		}
		else draw_line(x1, y1, x0, y0, s, c); // Octant V
	}
	else if (m > 1) {
		if (x0 < x1) { // Octant II
			d = A + 2 * B;
			while (x <= x1) {
				plot(s, c, x, y);
				if (d < 0) {
					x ++;
					d += 2 * A;
				}
				y ++;
				d += 2 * B;
			}
		}
		else draw_line(x1, y1, x0, y0, s, c); // Octant VI
	}
	else if (m < 0 && m > -1) {
		if (x0 < x1) { // Octant VIII
			d = 2 * A - B;
			while (x <= x1) {
				plot(s, c, x, y);
				if (d < 0) {
					y --;
					d -= 2 * B;
				}
				x ++;
				d += 2 * A;
			}
		}
		else draw_line(x1, y1, x0, y0, s, c); // Octant IV
	}
	else if (m < -1) {
		if (x0 < x1) { // Octant VII
			d = A - 2 * B;
			while (x <= x1) {
				plot(s, c, x, y);
				if (d > 0) {
					x ++;
					d += 2 * A;
				}
				y --;
				d -= 2 * B;
			}
		}
		else draw_line(x1, y1, x0, y0, s, c); // Octant III
	}
}

void translate(struct matrix *edges, struct matrix *trans, screen s, color c, int x, int y) {
	trans->m[0][3] = x;
	trans->m[1][3] = y;
	matrix_mult(trans, edges);
	
	c.red = rand() % 256;
	c.blue = rand() % 256;
	c.green = rand() % 256;
	
	draw_lines(edges, s, c);
}
