#ifndef HISTO
#define HISTO

#include <stdio.h>
#include "image.h"

/*
 *  Cells structure for the histogram
 */
typedef struct cell_s cell_t;
struct cell_s {
    unsigned char B;
    int freq;
    struct cell_s *next;
};


/*
 *  Histo structure.
 */
typedef cell_t*** histo_t;


/*
 * Structure of histo_iter_s and his pointeur histo_iter bellow.
 */
typedef struct histo_iter_s {
    int R;
    int G;
    cell_t *current;
} histo_iter_s;

typedef histo_iter_s* histo_iter;

typedef enum {false,true} boolean;


/*
 *  @func This function creates a new cell
 *  @param B is a int wich represents the value for blue in 
 *   the cell
 *  @ret a pointer to the new cell
 */
cell_t* create_cell(int B, cell_t *next);

/*
 * @func inserts a cell in sorted order, or increments frequency if exists
 * @param head is the address of the head of the list
 * @param B is the blue value to insert
 * @ret void
 */
void insert_cell(cell_t **head, int B);


/*
 * @func deletes a liste
 * @param cell_t is the head of the list to deletes
 * @ret void
 */
void delete_list(cell_t *head);


/*
 * @func creates a 256x256 histogram
 * @param none
 * @ret pointer to the new histogram
 */
histo_t create_histo();

/*
 * @func Initialisation of the histogram with image data
 * @param h is the histogram to initialize
 * @param img is the image to process
 * @ret void
 */
void init_histo(histo_t h, Image *img);

/*
 * @func Suppression of histo
 * @param h is the histogram to delete
 * @ret void
 */
void delete_histo(histo_t h);

/*
 * @func gives frequency of a color in histogram
 * @param h is the histogram
 * @param R is the red value
 * @param G is the green value
 * @param B is the blue value
 * @ret frequency of the color
 */
int give_freq_histo(histo_t h,int R, int G, int B); 

/*
 * @func creates an iterator for the histogram
 * @param h is the histogram to iterate
 * @ret pointer to the new iterator
 */
histo_iter create_histo_iter(histo_t h);

/*
 * @func initializes the iterator to start position
 * @param it is the iterator to initialize
 * @ret void
 */
void start_histo_iter(histo_iter it);

/*
 * @func moves to next element in histogram
 * @param it is the iterator
 * @param h is the histogram
 * @ret true if next element exists, false otherwise
 */
boolean next_histo_iter(histo_iter it, histo_t h);

/*
 * @func gets the color at current iterator position
 * @param it is the iterator
 * @param tab is an array of size 3 to store RGB values
 * @ret void
 */
void give_color_histo_iter(histo_iter it, int *tab);

/*
 * @func deletes the histogram iterator
 * @param it is the iterator to delete
 * @ret void
 */
void delete_histo_iter(histo_iter it);


#endif
