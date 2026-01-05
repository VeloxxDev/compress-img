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

/*
 * @func initializes an empty image structure
 * @param none
 * @ret pointer to the new image
 */
Image * init_image();

/*
 * @func loads PPM header information
 * @param fin is the input file pointer
 * @param image is the image structure to fill
 * @ret void
 */
void load_header(FILE * fin, Image* image);


/*
 * @func loads pixels in ASCII format
 * @param fin is the input file pointer
 * @param image is the image structure with header already loaded
 * @ret void
 */
void load_pixels_ascii(FILE* fin, Image* image);

/*
 * @func loads pixels in binary format
 * @param fin is the input file pointer
 * @param image is the image structure with header already loaded
 * @ret void
 */
void load_pixels_binary(FILE* fin, Image* image);

/*
 * @func loads pixels from file based on format
 * @param fin is the input file pointer
 * @param image is the image structure with header already loaded
 * @ret void
 */
void load_pixels(FILE* fin, Image* image); 

/*
 * @func loads a complete PNM image from file
 * @param fin is the input file pointer
 * @ret pointer to the loaded image
 */
Image* load_pnm(FILE* fin); 

/*
 * @func frees all memory allocated for an image
 * @param img is the image to free
 * @ret void
 */
void free_image(Image* img);

typedef void (*pixel_loader_t)(FILE*, Image*);

/*
 * @func saves an image to PNM format
 * @param img is the image to save
 * @param fout is the output file pointer
 * @ret 0 on success, non-zero on error
 */
int save_pnm(const Image* img, FILE* fout);

/*
 * @func creates a new image with allocated pixel buffer
 * @param width is the image width
 * @param height is the image height
 * @ret pointer to the new image
 */
Image* create_image(int width, int height);

#endif
