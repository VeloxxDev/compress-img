#ifndef FONCTIONS
#define FONCTIONS 

#include <stdio.h>


/**
 * @brief Pointer to Image structure
 */
typedef struct Image Image;

/**
 * @brief Image structure for PPM format
 */
struct Image {
    char magic[3]; /*!< PPM magic number (P5 or P6) */
    int height; /*!< Image height in pixels */
    int width; /*!< Image width in pixels */
    int max; /*!< Maximum color value (usually 255) */
    unsigned char *pixels; /*!< Pixel data array (RGB or grayscale) */
};

/**
 * @brief initializes an empty image structure
 * @param none
 * @return pointer to the new image
 */
Image * init_image();

/**
 * @brief loads PPM header information
 * @param fin is the input file pointer
 * @param image is the image structure to fill
 * @return void
 */
void load_header(FILE * fin, Image* image);


/**
 * @brief loads pixels in ASCII format
 * @param fin is the input file pointer
 * @param image is the image structure with header already loaded
 * @return void
 */
void load_pixels_ascii(FILE* fin, Image* image);

/**
 * @brief loads pixels in binary format
 * @param fin is the input file pointer
 * @param image is the image structure with header already loaded
 * @return void
 */
void load_pixels_binary(FILE* fin, Image* image);

/**
 * @brief loads pixels from file based on format
 * @param fin is the input file pointer
 * @param image is the image structure with header already loaded
 * @return void
 */
void load_pixels(FILE* fin, Image* image); 

/**
 * @brief loads a complete PNM image from file
 * @param fin is the input file pointer
 * @return pointer to the loaded image
 */
Image* load_pnm(FILE* fin); 

/**
 * @brief frees all memory allocated for an image
 * @param img is the image to free
 * @return void
 */
void free_image(Image* img);

/**
 * @brief Function pointer type for pixel loading functions
 */
typedef void (*pixel_loader_t)(FILE*, Image*);

/**
 * @brief saves an image to PNM format
 * @param img is the image to save
 * @param fout is the output file pointer
 * @return 0 on success, non-zero on error
 */
int save_pnm(const Image* img, FILE* fout);

/**
 * @brief creates a new image with allocated pixel buffer
 * @param width is the image width
 * @param height is the image height
 * @return pointer to the new image
 */
Image* create_image(int width, int height);

#endif
