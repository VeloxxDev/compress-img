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
 * @file main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"
#include "../include/histo.h"
#include "../include/quantification.h"

int main(int argc, char **argv) {

    if (argc != 3) {
        printf("Nombre d'arguments incorect");
        return 1;
    }

    int K = atoi(argv[1]);
    if (K <= 0) {
        fprintf(stderr, "K doit être strictement positif.\n");
        return 1;
    }

    FILE *f = fopen(argv[2], "r");
    if (!f) {
        perror("Erreur fopen input");
        return 1;
    }

    Image *input = load_pnm(f);
    fclose(f);

    if (!input) {
        fprintf(stderr, "Erreur load_pnm\n");
        return 1;
    }

    histo_t h = create_histo();
    if (!h) {
        fprintf(stderr, "Erreur create_histo\n");
        free_image(input);
        return 1;
    }

    init_histo(h, input);

    int *tab = malloc(K * 3 * sizeof(int));
    if (!tab) {
        fprintf(stderr, "Erreur malloc tab\n");
        delete_histo(h);
        free_image(input);
        return 1;
    }

    quantification(h, tab, K);

    Image *output = create_image(input->width, input->height);
    if (!output) {
        fprintf(stderr, "Erreur create_image\n");
        free(tab);
        delete_histo(h);
        free_image(input);
        return 1;
    }

    mapping(input, output, tab, K);

    FILE *out = fopen("output.ppm", "w");
    if (!out) {
        perror("Erreur fopen output");
        free(tab);
        delete_histo(h);
        free_image(input);
        free_image(output);
        return 1;
    }

    save_pnm(output, out);
    fclose(out);

    free(tab);
    delete_histo(h);
    free_image(input);
    free_image(output);

    printf("Image quantifiée sauvegardée dans output.ppm\n");
    return 0;
}