#include <stdio.h>
#include <stdlib.h>
#include "../include/histo.h"
#include "../include/quantification.h"

/**
 * @brief Color cell for quantification list
 */
typedef struct cell_l {
    unsigned char R; /*!< Red component of the color */
    unsigned char G; /*!< Green component of the color */
    unsigned char B; /*!< Blue component of the color */
    int f; /*!< Frequency of this color */
    struct cell_l *next; /*!< Pointer to the next cell in the list */
} cell_l;

/**
 * @brief inserts a color cell in descending frequency order
 * @param head is the address of the list head
 * @param R is the red value
 * @param G is the green value
 * @param B is the blue value
 * @param f is the frequency
 * @return void
 */
void insert_by_ascending_sort(cell_l **head, int R, int G, int B, int f) {

    cell_l *new_cell;
    cell_l *current;
    cell_l *prev;

    new_cell = (cell_l*)malloc(sizeof(cell_l));
    current = *head;
    prev = NULL;

    new_cell->R = R;
    new_cell->G = G;
    new_cell->B = B;
    new_cell->f = f;

    while (current != NULL && current->f < f) {
        prev = current;
        current = current->next;
    }

    new_cell->next = current;
    if (prev == NULL) {
        *head = new_cell;
    } else {
        prev->next = new_cell;
    }
}

/**
 * @brief deletes the head element of the list
 * @param head is the address of the list head
 * @return void
 */
void delete_head(cell_l **head) {

    cell_l *del;

    if (*head == NULL)
        return;

    del = *head;
    *head = (*head)->next;
    free(del);
}

/**
 * @brief copies K colors from list to array
 * @param list is the color list
 * @param tab is the destination array of size K*3
 * @param K is the number of colors to copy
 * @return void
 */
void copy_to_tab(cell_l *list, int *tab, int K) {

    cell_l *current;
    int i;

    current = list;
    i = 0;

    while (current != NULL && i < K) {
        tab[i*3 + 0] = current->R;
        tab[i*3 + 1] = current->G;
        tab[i*3 + 2] = current->B;

        current = current->next;
        i++;
    }
}

/**
 * @brief deletes the entire color list
 * @param head is the list head
 * @return void
 */
void delete_list_l(cell_l *head) {

    cell_l *next;
    cell_l *current;
    current = head;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void quantification(histo_t h, int* tab, int K) {

    cell_l *list;
    histo_iter it;
    int count;
    int color[3];
    int freq;

    list = NULL;
    it = create_histo_iter(h);
    if (it == NULL) {
        perror("create_histo");
        return;
    }
    count = 0;
    
    /* Prise en compte du premier élément*/
    give_color_histo_iter(it, color);
    freq = give_freq_histo(h, color[0], color[1], color[2]);
    insert_by_ascending_sort(&list, color[0], color[1], color[2], freq);
    count++;


    while (next_histo_iter(it, h) && count < K) {
        give_color_histo_iter(it, color);
        freq = give_freq_histo(h,color[0],color[2],color[3]);

        insert_by_ascending_sort(&list, color[0], color[1], color[2], freq);
        count++;
    }

    while (next_histo_iter(it, h)) {
        give_color_histo_iter(it, color);
        freq = give_freq_histo(h,color[0],color[2],color[3]);

        if (list != NULL && freq > list->f) {
            delete_head(&list);
            insert_by_ascending_sort(&list, color[0], color[1], color[2], freq);
        }
    }
        
    copy_to_tab(list,  tab, K);

    delete_histo_iter(it);
    delete_list_l(list);
}

/**
 * @brief finds the nearest color in palette using Euclidean distance
 * @param R is the red value
 * @param G is the green value
 * @param B is the blue value
 * @param tab is the color palette array of K*3 colors
 * @param K is the number of colors in palette
 * @return index of the nearest color in the palette
 */
int nearest_color(int R, int G, int B, int *tab, int K) {
    int best = 0;
    int best_dist = 999999999;

    for (int i = 0; i < K; i++) {  // Distance Euclidienne 
        int dR = R - tab[i*3 + 0];
        int dG = G - tab[i*3 + 1];
        int dB = B - tab[i*3 + 2];

        int dist = dR*dR + dG*dG + dB*dB;

        if (dist < best_dist) {
            best_dist = dist;
            best = i;
        }
    }
    return best; 
}

/**
 * @brief maps input image colors to nearest palette colors
 * @param in is the input image
 * @param out is the output image
 * @param tab is the color palette array of K*3 colors
 * @param K is the number of colors in palette
 * @return void
 */
void mapping(Image *in, Image *out, int* tab, int K) {

    for (int y = 0; y < in->height; y++) {
        for (int x = 0; x < in->width; x++) {

            int R = in->pixels[(y*in->width + x)*3 + 0];
            int G = in->pixels[(y*in->width + x)*3 + 1];
            int B = in->pixels[(y*in->width + x)*3 + 2];

            int idx = nearest_color(R, G, B, tab, K);

            out->pixels[(y*out->width + x)*3 + 0] = tab[idx*3 + 0];
            out->pixels[(y*out->width + x)*3 + 1] = tab[idx*3 + 1];
            out->pixels[(y*out->width + x)*3 + 2] = tab[idx*3 + 2];
        }
    }
}