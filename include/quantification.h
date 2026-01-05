/*
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/**
 * @author Iwan Clemente <iwan.clemente@ecole.ensicaen.fr>
 * @author Yann Moulin <yann.moulin@ecole.ensicaen.fr>
 * @version 1.5.7 - 05/01/2025
 */

/** 
 * @file quantification.h
 */

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