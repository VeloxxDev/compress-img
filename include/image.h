#ifndef FONCTIONS
#define FONCTIONS 

#include <stdio.h>


typedef struct Image Image;

struct Image {
    char magic[3];
    int height;
    int width;
    int max;
    unsigned char *pixels;
};

Image * init_image();

void load_header(FILE * fin, Image* image);


void load_pixels_ascii(FILE* fin, Image* image);

void load_pixels_binary(FILE* fin, Image* image);

void load_pixels(FILE* fin, Image* image); 

Image* load_pnm(char* filename); 

void free_image(Image* img);

typedef void (*pixel_loader_t)(FILE*, Image*);

#endif
