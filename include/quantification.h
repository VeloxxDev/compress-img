#ifndef QUANTIFICATION
#define QUANTIFICATION

#include "histo.h"


/**
 * @brief performs color quantification to find K most frequent colors
 * @param h: histogram
 * @param tab: output array with K most frequent 
 *             colors, size of K*3
 * @param K: numbers of colors to keep
 */

void quantification(histo_t h, int *tab, int K);

/**
 * @brief maps colors from input image to palette colors in output image
 * @param in is the input image
 * @param out is the output image
 * @param tab is the color palette array of K*3 colors
 * @param K is the number of colors in the palette
 * @return void
 */
void mapping(Image *in, Image *out, int* tab, int K);

#endif