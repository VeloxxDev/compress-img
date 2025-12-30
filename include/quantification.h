#ifndef QUANTIFICATION
#define QUANTIFICATION

#include "histo.h"


/*
 * @func
 * @param h: histogram
 * @param tab: output array with K most frequent 
 *             colors, size of K*3
 * @param K: numbers of colors to keep
 */

void quantification(histo_t h, int *tab, int K);

#endif