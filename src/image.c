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
 * @file image.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/image.h"

Image* init_image() {
    Image* image = malloc(sizeof(Image));
    if (image == NULL) {
        perror("Erreur malloc");
        return NULL;
    }
    return image;
}

Image* create_image(int width, int height) {
    Image* img = malloc(sizeof(Image));
    if (!img) return NULL;

    strcpy(img->magic, "P6");
    img->width = width;
    img->height = height;
    img->max = 255;

    size_t count = width * height * 3;
    img->pixels = calloc(count, 1);

    return img;
}

void load_header(FILE* fin, Image* image) {
    char line[256];

    do { 
        if (!fgets(line, sizeof(line), fin)) {
            perror("Can't read magic number");
            exit(EXIT_FAILURE);
        }
    } while (line[0] == '#' || line[0] == '\n');
    sscanf(line, "%2s", image -> magic);
    
    do {
        if (!fgets(line, sizeof(line), fin)) {
            perror("Can't read height and wdth");
            exit(EXIT_FAILURE);
        }
    } while (line[0] == '#' || line[0] == '\n');
    sscanf(line, "%d %d", &image -> width, &image -> height);

    do {
        if (!fgets(line, sizeof(line), fin)) {
            perror("Can't read max value");
            exit(EXIT_FAILURE);
        }
    } while (line[0] == '#' || line[0] == '\n');
    sscanf(line, "%d", &image -> max);

    image -> pixels = NULL;
}

void load_pixels_ascii(FILE* fin, Image* image) {
    int channels = (strcmp(image->magic, "P2") == 0) ? 1 : 3;
    size_t count = image->width * image->height * channels;

    image->pixels = malloc(count);
    if (!image->pixels) exit(EXIT_FAILURE);

    for (size_t i = 0; i < count; i++) {
        int v;
        fscanf(fin, "%d", &v);
        image->pixels[i] = (unsigned char)v;
    }
}

void load_pixels_binary(FILE* fin, Image* image) {
    int channels = (strcmp(image->magic, "P5") == 0) ? 1 : 3;
    size_t count = image->width * image->height * channels;

    image->pixels = malloc(count);
    if (!image->pixels) exit(EXIT_FAILURE);

    fread(image->pixels, 1, count, fin);
}

pixel_loader_t get_loader(const char* magic) {
    if (strcmp(magic, "P2") == 0 || strcmp(magic, "P3") == 0)
        return load_pixels_ascii;

    if (strcmp(magic, "P5") == 0 || strcmp(magic, "P6") == 0)
        return load_pixels_binary;

    return NULL;
}

void load_pixels(FILE* fin, Image* image) {
    size_t pixel_count;

    if (strcmp(image->magic, "P5") == 0) {
        pixel_count = image->width * image->height;
    } else if (strcmp(image->magic, "P6") == 0) {
        pixel_count = image->width * image->height * 3;
    } else {
        fprintf(stderr, "Format non supporté : %s\n", image->magic);
        exit(EXIT_FAILURE);
    }

    image->pixels = malloc(pixel_count);
    if (!image->pixels) {
        perror("Échec de l'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    size_t read = fread(image->pixels, 1, pixel_count, fin);
    if (read != pixel_count) {
        perror("Échec de la lecture des pixels");
        free(image->pixels);
        image->pixels = NULL;
        exit(EXIT_FAILURE);
    }
}

Image* load_pnm(FILE* fin) {
    if (!fin) return NULL;

    Image* image = init_image();
    load_header(fin, image);

    pixel_loader_t loader = get_loader(image->magic);
    if (!loader) {
        fprintf(stderr, "Format non supporté : %s\n", image->magic);
        exit(EXIT_FAILURE);
    }

    loader(fin, image); 

    return image;
}

void free_image(Image* img) {
    if (!img)  
        return;
    free(img->pixels);
    free(img);
}

int save_pnm(const Image* img, FILE* fout) {
    if (!img || !fout) {
        fprintf(stderr, "save_pnm : paramètres invalides\n");
        return -1;
    }

    /* --- Écriture de l'en-tête --- */
    fprintf(fout, "%s\n", img->magic);
    fprintf(fout, "%d %d\n", img->width, img->height);
    fprintf(fout, "%d\n", img->max);

    int channels = 0;

    if (strcmp(img->magic, "P2") == 0 || strcmp(img->magic, "P5") == 0)
        channels = 1;   // PGM
    else if (strcmp(img->magic, "P3") == 0 || strcmp(img->magic, "P6") == 0)
        channels = 3;   // PPM
    else {
        fprintf(stderr, "save_pnm : format non supporté (%s)\n", img->magic);
        return -1;
    }

    size_t count = img->width * img->height * channels;

    /* --- ASCII --- */
    if (strcmp(img->magic, "P2") == 0 || strcmp(img->magic, "P3") == 0) {
        for (size_t i = 0; i < count; i++) {
            fprintf(fout, "%d ", img->pixels[i]);
            if ((i + 1) % (img->width * channels) == 0)
                fprintf(fout, "\n");
        }
    }

    /* --- Binaire --- */
    else if (strcmp(img->magic, "P5") == 0 || strcmp(img->magic, "P6") == 0) {
        fwrite(img->pixels, 1, count, fout);
    }

    return 0;
}