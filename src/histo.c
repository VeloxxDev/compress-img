#include <stdio.h>
#include <stdlib.h>
#include "image.h"

typedef struct cell_s cell_t;
struct cell_s {
    unsigned char B;
    int freq;
    struct cell_s *next;
};

typedef struct liste_s {
    cell_t *tete;
    cell_t *queue;
} liste_t;


cell_t* create_cell(int B, cell_t *next) {
    cell_t *new_cell;
    new_cell = (cell_t*)malloc(sizeof(cell_t));
    
    new_cell->B = B;
    new_cell->freq = 1;
    new_cell->next = next;

    return new_cell;
}


/* @todo problème quand il faut placer au début
        la cellule avant le head n'est pas celle pointée
*/
void insert_cell(cell_t *head, int B) {
    cell_t *new_cell;
    cell_t *current;
    cell_t *temp = create_cell(-1, head);
    current = temp;

    while (current->next != NULL && current->next->B < B) {
        current = current->next;
    }
    if (current->next != NULL && current->next->B == B) {
        current->next->freq += 1;
    } else {
        new_cell = create_cell(B, current->next);
        current->next = new_cell;
    }
    free(temp);
    temp = NULL;
}

/* petit problèmes la dedans, surement des 
    fuites memoires
*/
void delete_list(cell_t *head) {
    cell_t *current;
    cell_t *del;
    current = head;

    while (current->next != NULL) {
        del = current;
        current = current->next;
        free(del);
    }
    // free(current);
}

/* Fonction temporaire pour pouvoir verif
et tester les modifs de liste
a modif pour les listes vides
*/
void afficher(cell_t *head) {
    cell_t *current = head;

    if (head == NULL) {
        printf("Liste inexistante");
        return;
    }

    while (current != NULL) {
        printf("B: %d, freq: %d\n", current->B, current->freq);
        current = current->next;
    }
}

int main() {

    cell_t *head = create_cell(2, NULL);

    cell_t *suiv = create_cell(7, NULL);
    suiv->freq = 3;

    head->next = suiv;
    
    afficher(head);

    insert_cell(head, 4);
    insert_cell(head, 2);
    printf("\n\n\n");

    afficher(head);

    delete_list(head);
    afficher(head);

    return 0;
}












/* ============= Fonctions Histo (Yann) =============== */

histo create_histo() {
    histo new_histo = malloc(256*256*sizeof(cell_t*));
    for (int r=0;r<256;r++) {
        for (int g=0;g<256;g++) {
            histo[r][g] = NULL;
        }
    }
}

void init_histo(histo h,Image* image) {
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {

            unsigned char R = image->pixels[i][j].R;
            unsigned char G = image->pixels[i][j].G;
            unsigned char B = image->pixels[i][j].B;

            insert_cell(&histo[R][G], B);
        }
    }
}

void delete_histo(histo h) {
    for (int r=0;r<256;r++) {
        for (int g=0;g<256;g++) {
            delete_list(histo[r][g]);
        }
    }
}

int give_freq_histo(histo h,int R,int G,int B) {
    if (h[R][G] == NULL) {
        return 0;
    }

    cell_t* current;
    current = h[R][G];
    while (current != NULL) {
        if (current -> B == B) {
            return current.freq;
        }
        if (current -> B > B) {
            return 0;
        }
        current = current -> next;
        
    }
    return 0;
}

/* ======= Partie histo_iter ========= */

histo_iter create_histo_iter(cell_t *histo[256][256]) {
    histo_iter it = malloc(sizeof(histo_iter_s));
    if (it == NULL) {
        perror("Malloc failure");
        return NULL;
    }

    for (int R = 0; R < 256; R++) {
        for (int G = 0; G < 256; G++) {
            if (histo[R][G] != NULL) {
                it->R = R;
                it->G = G;
                it->current = histo[R][G];
                return it;
            }
        }
    }
    
    perror("Empty histo");
    return NULL;
}
    

