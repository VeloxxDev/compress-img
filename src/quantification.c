#include <stdio.h>
#include <stdlib.h>
#include "../include/histo.h"
#include "../include/quantification.h"

typedef struct cell_l {
    unsigned char R;
    unsigned char G;
    unsigned char B;
    int f;
    struct cell_l *next;
} cell_l;

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

void delete_head(cell_l **head) {

    cell_l *del;

    if (*head == NULL)
        return;

    del = *head;
    *head = (*head)->next;
    free(del);
}

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
    count = 0;

    while (next_histo_iter(it, h) && count < K) {
        give_color_histo_iter(it, color);
        freq = it->current->freq;

        insert_by_ascending_sort(&list, color[0], color[1], color[2], freq);
        count++;
    }

    while (next_histo_iter(it, h)) {
        give_color_histo_iter(it, color);
        freq = it->current->freq;

        if (list != NULL && freq > list->f) {
            delete_head(&list);
            insert_by_ascending_sort(&list, color[0], color[1], color[2], freq);
        }
    }
        
    copy_to_tab(list,  tab, K);

    delete_histo_iter(it);
    delete_list_l(list);
}
