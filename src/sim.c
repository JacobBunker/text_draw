#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include "sim.h"
#include "text.h"
#include "gifenc.h"


#define PRINT_LEVEL 0

int main(int argc, char** argv) {
	printf("FACTORIES SIMULATOR  \n");
		
	printf("creating graph image...\n");
	
	int width = 800;
	int height = 600;
	
	
    ge_GIF *gif = ge_new_gif(
        "output.gif",  /* file name */
        width, height,           /* canvas size */
        (uint8_t []) {  /* palette */
            0x00, 0x00, 0x00, /* 0 -> black */
            0xFF, 0x00, 0x00, /* 1 -> red */
            0x00, 0xFF, 0x00, /* 2 -> green */
            0x00, 0x00, 0xFF, /* 3 -> blue */
        },
        2,              /* palette depth == log2(# of colors) */
        -1,             /* transparency: -1 for none */
        0               /* infinite loop */
    );
	
	
		
	
	unsigned char *pixels = malloc(sizeof(unsigned char) * 3 * width * height);
	for(int i = 0; i < width*height*3; ++i) { //zero out
		pixels[i] = 0;
	}
	
	unsigned char *red = malloc(sizeof(unsigned char) * 3);
	red[0] = 255;
	red[1] = 0;
	red[2] = 0;
	
	unsigned char *blue = malloc(sizeof(unsigned char) * 3);
	blue[0] = 0;
	blue[1] = 0;
	blue[2] = 255;
	
	unsigned char *green = malloc(sizeof(unsigned char) * 3);
	green[0] = 0;
	green[1] = 255;
	green[2] = 0;
	
	char message[] = "henlo !1111!!! \n\n "; //"        !!!!11!\n :))))))\n";
		//"Hello friends, I have created a custom text drawing program in c\n This allows me to write text onto any pixel matrix,\n it's quite versatile!";
	//"abcdefghijklmnopqrstuvwxyz1234567890 -()[]{}.,/_+!@#$%^&*~<>=:;\'\"\\|";
	size_t len = strlen(message);

	unsigned char **colors = malloc(sizeof(unsigned char *) * len);	
	int *sizes = malloc(sizeof(int) * len);
	int *thicknesses = malloc(sizeof(int) * len);	
	float *rotations = malloc(sizeof(float) * len);	
	//draw_text(pixels, width, height, 0 + 30, 0 + (2*height / 3), message, len, sizes, colors, 4, rotations, thicknesses);
	//int draw_text(unsigned char *pixels, int width, int height, int posx, int posy, char *text, int len, int *sizes, unsigned char **colors, int spacing);
	
	int xpos = 0;
	int frames = 120;
	int frame = 0;
	while(frame < frames) {
		for(int i = 0; i < width*height*3; ++i) { //zero out
			pixels[i] = 0;
		}
		
		for(int i = 0; i < len; ++i) {
		
		
			int r_color = rand() % 3;
			if(r_color == 0) {
				colors[i] = red;
			} else if(r_color == 1){
				colors[i] = blue;
			} else {
				colors[i] = green;
			}
		
			sizes[i] = ((i%5)*2)+10;//+((frame%12)*2.5);
			thicknesses[i] = 1;
			
			if(frame < 45) {
				rotations[i] = -0.1*frame*5;
			} else {
				rotations[i] = 0.0;   
			}
		}
		
		if(frame < 45) {
			xpos = frame * 6.666666666666667;
		} else {
			xpos = 300;
		}
		
		draw_text(pixels, width, height, 0 + xpos, 0 + (2*height / 3), message, len, sizes, colors, 4, rotations, thicknesses);
		int color_target = 0;
		
		for(int i = 0; i < height; ++i) { //y
			for(int ii = 0; ii < width; ++ii) { //x
				if(pixels[(i*width*3)+(ii*3)+0] == red[0] &&
				   pixels[(i*width*3)+(ii*3)+1] == red[1] &&
				   pixels[(i*width*3)+(ii*3)+2] == red[2]) {
					   color_target = 1;
				} else if(pixels[(i*width*3)+(ii*3)+0] == green[0] &&
						  pixels[(i*width*3)+(ii*3)+1] == green[1] &&
				   		  pixels[(i*width*3)+(ii*3)+2] == green[2]) {
					color_target = 2;
				} else if(pixels[(i*width*3)+(ii*3)+0] == blue[0] &&
						  pixels[(i*width*3)+(ii*3)+1] == blue[1] &&
				   		  pixels[(i*width*3)+(ii*3)+2] == blue[2]) {
					   color_target = 3;
				} else {
					color_target = 0;
				}
				
				gif->frame[((height - i - 1) * width) + ii] = color_target;
			}
		}
	
		ge_add_frame(gif, 6);
		
		frame++;
	}
	
	ge_close_gif(gif);
	
	
	
	
	FILE *f = fopen("./img_out/all_out.ppm", "wb");
	fprintf(f, "P6\n%i %i 255\n", width, height);
	for (int y=height - 1; y>=0; y--) {
	    for (int x=0; x<width; x++) {
			//printf("x:%d y:%d r->%f\n", x,y,pixels[(y * width * 3) + (x * 3) + 0]);
	        fputc(pixels[(y * width * 3) + (x * 3) + 0], f);   // 0 .. 255
	        fputc(pixels[(y * width * 3) + (x * 3) + 1], f); // 0 .. 255
	        fputc(pixels[(y * width * 3) + (x * 3) + 2], f);  // 0 .. 255
	    }
	}
	fclose(f);
	
	
	return 0;
}












