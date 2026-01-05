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
 * @file histo.h
 */

#ifndef HISTO
#define HISTO

#include <stdio.h>
#include "image.h"

/**
 * @brief Cell for histogram list
 */
typedef struct cell_s cell_t;
struct cell_s {
    unsigned char B; /*!< Blue value of the color */
    int freq; /*!< Frequency of this color in the histogram */
    struct cell_s *next; /*!< Pointer to the next cell in the list */
};


/**
 * @brief 2D histogram structure (256x256 array of cell pointers)
 */
typedef cell_t*** histo_t;


/**
 * @brief Iterator for histogram traversal
 */
typedef struct histo_iter_s {
    int R; /*!< Red coordinate in the histogram */
    int G; /*!< Green coordinate in the histogram */
    cell_t *current; /*!< Current cell in the traversal */
} histo_iter_s;

/**
 * @brief Pointer to histogram iterator
 */
typedef histo_iter_s* histo_iter;

/**
 * @brief Boolean type for true/false values
 */
typedef enum {false,true} boolean;


/**
 *  @brief This function creates a new cell
 *  @param B is a int wich represents the value for blue in 
 *   the cell
 *  @return a pointer to the new cell
 */
cell_t* create_cell(int B, cell_t *next);

/**
 * @brief inserts a cell in sorted order, or increments frequency if exists
 * @param head is the address of the head of the list
 * @param B is the blue value to insert
 * @return void
 */
void insert_cell(cell_t **head, int B);


/**
 * @brief deletes a liste
 * @param cell_t is the head of the list to deletes
 * @return void
 */
void delete_list(cell_t *head);


/**
 * @brief creates a 256x256 histogram
 * @param none
 * @return pointer to the new histogram
 */
histo_t create_histo();

/**
 * @brief Initialisation of the histogram with image data
 * @param h is the histogram to initialize
 * @param img is the image to process
 * @return void
 */
void init_histo(histo_t h, Image *img);

/**
 * @brief Suppression of histo
 * @param h is the histogram to delete
 * @return void
 */
void delete_histo(histo_t h);

/**
 * @brief gives frequency of a color in histogram
 * @param h is the histogram
 * @param R is the red value
 * @param G is the green value
 * @param B is the blue value
 * @return frequency of the color
 */
int give_freq_histo(histo_t h,int R, int G, int B); 

/**
 * @brief creates an iterator for the histogram
 * @param h is the histogram to iterate
 * @return pointer to the new iterator
 */
histo_iter create_histo_iter(histo_t h);

/**
 * @brief initializes the iterator to start position
 * @param it is the iterator to initialize
 * @return void
 */
void start_histo_iter(histo_iter it);

/**
 * @brief moves to next element in histogram
 * @param it is the iterator
 * @param h is the histogram
 * @return true if next element exists, false otherwise
 */
boolean next_histo_iter(histo_iter it, histo_t h);

/**
 * @brief gets the color at current iterator position
 * @param it is the iterator
 * @param tab is an array of size 3 to store RGB values
 * @return void
 */
void give_color_histo_iter(histo_iter it, int *tab);

/**
 * @brief deletes the histogram iterator
 * @param it is the iterator to delete
 * @return void
 */
void delete_histo_iter(histo_iter it);


#endif
