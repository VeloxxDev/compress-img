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
 * @file ppmhist.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "histo.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Il manque un argument");
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror("fopen errror");
        return 1;
    }

    Image* img = load_pnm(f);
    fclose(f);

    histo_t h = create_histo();
    init_histo(h,img);

    histo_iter it = create_histo_iter(h);
    if (!it) {
        printf("Error create_histo_iter\n");
        delete_histo(h);
        free_image(img);
        return 1;
    }

    int rgb[3];
    give_color_histo_iter(it, rgb);

    int R = rgb[0];
    int G = rgb[1];
    int B = rgb[2];
    int lum = (R + G + B) / 3;
    int freq = give_freq_histo(h, R, G, B);

    printf("%d %d %d %d %d\n", R, G, B, lum, freq);

    while (next_histo_iter(it, h)) {

        give_color_histo_iter(it, rgb);

        R = rgb[0];
        G = rgb[1];
        B = rgb[2];
        lum = (R + G + B) / 3;
        freq = give_freq_histo(h, R, G, B);

        printf("%d %d %d %d %d\n", R, G, B, lum, freq);
    }

    delete_histo_iter(it);
    delete_histo(h);
    free_image(img);

    return 0;
}
