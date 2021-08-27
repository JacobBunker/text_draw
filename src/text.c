#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include "text.h"


int thickness_index[4] = {1,4,4,4};
int thickness_coords[26] = {0,0,	1,0,	-1,0,	0,1,	0,-1,	1,1,	1,-1,	-1,1,	-1,-1,	-2,0,	2,0,	0,-2,	0,2};

void draw_line(unsigned char *pixels, int width, int height, int size, int orig_x, int orig_y, int start_x, int start_y, int end_x, int end_y, int thickness, unsigned char *color, float rotation) {	
	
	int thickness_counter;
	int y_t, x_t;
	int i_x, i_y, xy;
	float norm_x, norm_y;
	float length = sqrt(((end_x - start_x) * (end_x - start_x)) + ((end_y - start_y) * (end_y - start_y)));
	float rot_start_x, rot_start_y;
	float rot_end_x, rot_end_y;
	
	int center_x = orig_x + (size/2);
	int center_y = orig_y + (size/2);
	
	rot_start_x = ((start_x - center_x) * cos(rotation)) - ((start_y - center_y) * sin(rotation)) + center_x;
	rot_start_y = ((start_x - center_x) * sin(rotation)) + ((start_y - center_y) * cos(rotation)) + center_y;
	
	rot_end_x = ((end_x - center_x) * cos(rotation)) - ((end_y - center_y) * sin(rotation)) + center_x;
	rot_end_y = ((end_x - center_x) * sin(rotation)) + ((end_y - center_y) * cos(rotation)) + center_y;
	
	norm_x = (rot_end_x - rot_start_x) / length;
	norm_y = (rot_end_y - rot_start_y) / length;
		
	printf("length %.3f, norm %.2f %.2f\n", length, norm_x, norm_y);
	for(int i = 0; i < length; ++i) {
		x_t = rot_start_x + (norm_x * i);
		y_t = rot_start_y + (norm_y * i);
		
		thickness_counter = 0;
		for(int t = 0; t <= thickness; ++t) {
			for(int ti = 0; ti < thickness_index[t]; ++ti) {
				i_x = (x_t + thickness_coords[((thickness_counter+ti)*2) + 0]) * 3;
				i_y = (y_t + thickness_coords[((thickness_counter+ti)*2) + 1]) * 3 * width;
				xy = i_x + i_y;
				
				pixels[xy + 0] = color[0];
				pixels[xy + 1] = color[1];
				pixels[xy + 2] = color[2];
			}
			thickness_counter += thickness_index[t];
		}
	}
}


void draw_letter(unsigned char *pixels, int width, int height, int posx, int posy, char l, int size, unsigned char *color, int thickness, float rotation) {	
	printf("drawing letter %c at position %d %d with size %d color %d %d %d thickness %d rotation %.3f\n", l, posx, posy, size, color[0], color[1], color[2], thickness, rotation);
			
	//should reorganize this by most common letters to speed it up
	switch(l) {
		case 'a':
		case 'A':
			draw_line(pixels, width, height, size, posx, posy, posx + (size/2), posy + size, posx, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx + (size/2), posy + size, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx + (size/4), posy + (size/2), posx + (3*size/4), posy + (size/2), thickness, color, rotation);
			break;
		case 'b':
		case 'B':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy+(size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/4), posx, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(3*size/4), posx, posy+size, thickness, color, rotation);
			break;
		case 'c':
		case 'C':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/4), posx, posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/4), posx+(size/4), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(3*size/4), posx+(size/4), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+size, posx+size, posy+size, thickness, color, rotation);
			break;
		case 'd':
		case 'D':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+(3*size/4), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+(3*size/4), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(3*size/4), posy+size, posx+size, posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(3*size/4), posy, posx+size, posy+(size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/4), posx+size, posy+(3*size/4), thickness, color, rotation);
			break;
		case 'e':
		case 'E':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			break;
		case 'f':
		case 'F':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			break;
		case 'g':
		case 'G':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/4), posx, posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/4), posx+(size/4), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(3*size/4), posx+(size/4), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/2), posx+(3*size/4), posy+(size/2), thickness, color, rotation);
			break;
		case 'h':
		case 'H':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			break;
		case 'i':
		case 'I':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy, posx+(size/2), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			break;
		case 'j':
		case 'J':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+size, posx+(3*size/4), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+size, posx+(size/2), posy+(size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/4), posx+(size/3), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/3), posy, posx+(size/5), posy+(size/4), thickness, color, rotation);
			break;
		case 'k':
		case 'K':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy, thickness, color, rotation);			
			break;
		case 'l':
		case 'L':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			break;
		case 'm':
		case 'M':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+(size/2), posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+size, posx+(size/2), posy+(size/2), thickness, color, rotation);
			break;
		case 'n':
		case 'N':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy, thickness, color, rotation);
			break;
		case 'o':
		case 'O':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			break;
		case 'p':
		case 'P':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(3*size/4), thickness, color, rotation);
			break;
		case 'q':
		case 'Q':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/5), posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/5), posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/5), posx+size, posy+(size/5), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/5), posx+(3*size/4), posy, thickness, color, rotation);
			break;
		case 'r':
		case 'R':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+size, posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/2), posx, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+(size/2), posx+size, posy, thickness, color, rotation);
			break;
		case 's':
		case 'S':
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+size, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/2), posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx, posy, thickness, color, rotation);
			break;
		case 't':
		case 'T':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+size, posx+(size/2), posy, thickness, color, rotation);
			break;
		case 'u':
		case 'U':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+size, thickness, color, rotation);
			break;
		case 'v':
		case 'V':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy, posx, posy+size, thickness, color, rotation);
			break;
		case 'w':
		case 'W':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+(size/4), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy, posx+(size/2), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+size, posx+(3*size/4), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(3*size/4), posy, posx+size, posy+size, thickness, color, rotation);
			break;
		case 'x':
		case 'X':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy, thickness, color, rotation);
			break;
		case 'y':
		case 'Y':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy, posx+(size/2), posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/2), posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/2), posx, posy+size, thickness, color, rotation);
			break;
		case 'z':
		case 'Z':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			break;
		case '0':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy+size, thickness, color, rotation);
			break;
		case '1':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy, posx+(3*size/4), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy, posx+(size/2), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+size, posx+(size/4), posy+(3*size/4), thickness, color, rotation);
			break;
		case '2':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+size, posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/2), posx, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			break;
		case '3':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			break;
		case '4':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+size, posx+size, posy, thickness, color, rotation);
			break;
		case '5':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/2), posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx, posy, thickness, color, rotation);
			break;
		case '6':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+(size/2), thickness, color, rotation);
			break;
		case '7':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+size, posx+(size/4), posy, thickness, color, rotation);
			break;
		case '8':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+size, thickness, color, rotation);
			break;
		case '9':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+size, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx, posy, thickness, color, rotation);
			break;
		case '-':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			break;
		case ' ':
		case '\n':
			break;
		case '(':
		case '{':
		case '[':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+size, posx+(3*size/4), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy, posx+(3*size/4), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy, posx+(size/4), posy+size, thickness, color, rotation);
			break;
		case ')':
		case '}':
		case ']':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+size, posx+(3*size/4), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy, posx+(3*size/4), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(3*size/4), posy, posx+(3*size/4), posy+size, thickness, color, rotation);
			break;
		case '.':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/4), posx+(size/2), posy+(size/5), 4, color, rotation);
			break;
		case ',':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/4), posx+(size/2), posy+(size/5), 4, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/4), posx+(2*size/5), posy, 2, color, rotation);
			break;
		case '/':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy+size, thickness, color, rotation);
			break;
		case '_':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			break;
		case '+':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/4), posx+(size/2), posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+(size/2), posx+(3*size/4), posy+(size/2), thickness, color, rotation);
			break;
		case '!':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/3), posx+(size/2), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/6), posx+(size/2), posy, thickness, color, rotation);
			break;
		case '@':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+size, posx+size, posy+(size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/4), posx+(size/4), posy+(size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+(size/4), posx+(size/4), posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+(3*size/4), posx+size, posy+(3*size/4), thickness, color, rotation);
			break;
		case '#':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+(3*size/4), posx+(9*size/10), posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/6), posy+(size/4), posx+(3*size/4), posy+(size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy, posx+(size/2), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy, posx+(3*size/4), posy+size, thickness, color, rotation);
			break;
		case '$':
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(3*size/4), posx, posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(3*size/4), posx, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/2), posx+size, posy+(size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/4), posx, posy+(size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy, posx+(size/4), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(3*size/4), posy, posx+(3*size/4), posy+size, thickness, color, rotation);
			break;
		case '%':
			draw_line(pixels, width, height, size, posx, posy, posx, posy, posx+size, posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+(size/3), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx, posy+(2*size/3), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/3), posy+(2*size/3), posx, posy+(2*size/3), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/3), posy+(2*size/3), posx+(size/3), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+(2*size/3), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy, posx+size, posy+(size/3), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(2*size/3), posy+(size/3), posx+size, posy+(size/3), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(2*size/3), posy+(size/3), posx+(2*size/3), posy, thickness, color, rotation);
			break;
		case '^':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+(3*size/4), posx+(size/2), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(3*size/4), posy+(3*size/4), posx+(size/2), posy+size, thickness, color, rotation);
			break;
		case '&': 
			draw_line(pixels, width, height, size, posx, posy, posx+(size/5), posy+size, posx+(size/2), posy+size, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/5), posy+size, posx+(size/5), posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/5), posy+(3*size/4), posx, posy+(size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/4), posx+(size/4), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy, posx+(size/2), posy, thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy, posx+(3*size/4), posy+(2*size/5), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+size, posx+(2*size/5), posy+(5*size/6), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(2*size/5), posy+(5*size/6), posx+(size/4), posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(3*size/4), posx+size, posy, thickness, color, rotation);
			break;
		case '*':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+(size/4), posx+(3*size/4), posy+(3*size/4), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/4), posy+(3*size/4), posx+(3*size/4), posy+(size/4), thickness, color, rotation);
			break;
		case '~':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+(size/3), posy+(2*size/3), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/3), posy+(2*size/3), posx+(2*size/3), posy+(size/2), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(2*size/3), posy+(size/2), posx+size, posy+(2*size/3), thickness, color, rotation);
			break;
		case '<':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(4*size/5), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/2), posx+size, posy+(size/5), thickness, color, rotation);
			break;
		case '>':
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/2), posx, posy+(4*size/5), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+size, posy+(size/2), posx, posy+(size/5), thickness, color, rotation);
			break;
		case '=':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(size/3), posx+size, posy+(size/3), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx, posy+(2*size/3), posx+size, posy+(2*size/3), thickness, color, rotation);
			break;
		case ';':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/4), posx+(size/2), posy+(size/5), 4, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(size/4), posx+(2*size/5), posy, 2, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(3*size/4), posx+(size/2), posy+(4*size/5), 4, color, rotation);
			break;
		case ':':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+(3*size/4), posx+(size/2), posy+(4*size/5), 4, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy, posx+(size/2), posy+(size/4), 4, color, rotation);
			break;
		case '\'':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+size, posx+(size/2), posy+(2*size/3), thickness, color, rotation);
			break;
		case '\"':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/3), posy+size, posx+(size/3), posy+(2*size/3), thickness, color, rotation);
			draw_line(pixels, width, height, size, posx, posy, posx+(2*size/3), posy+size, posx+(2*size/3), posy+(2*size/3), thickness, color, rotation);
			break;
		case '\\':
			draw_line(pixels, width, height, size, posx, posy, posx, posy+size, posx+size, posy, thickness, color, rotation);
			break;
		case '|':
			draw_line(pixels, width, height, size, posx, posy, posx+(size/2), posy+size, posx+(size/2), posy, thickness, color, rotation);
			break;
		default:
			printf("invalid character %c\n", l);
			break;
			
	}
	//"abcdefghijklmnopqrstuvwxyz1234567890 -()[]{}.,/_+!@#$%^&*~<>=:;\'\"\\|";
}

int draw_text(unsigned char *pixels, int width, int height, int posx, int posy, char *text, int len, int *sizes, unsigned char **colors, int spacing, float *rotations, int *thicknesses) {
	int curr_x = posx;
	int curr_y = posy;
	
	
	for(int i = 0; i < len; ++i) {
		draw_letter(pixels, width, height, curr_x, curr_y, text[i], sizes[i], colors[i], thicknesses[i], rotations[i]);
		curr_x += sizes[i] + spacing;
		if(text[i] == '\n') {
			curr_y -= sizes[i] + (spacing * 2);
			curr_x = posx;
		}
	}
	
	return 0;
}









