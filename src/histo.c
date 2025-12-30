#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"
#include "../include/histo.h"


cell_t* create_cell(int B, cell_t *next) {
    cell_t *new_cell;
    new_cell = (cell_t*)malloc(sizeof(cell_t));
    
    new_cell->B = B;
    new_cell->freq = 1;
    new_cell->next = next;

    return new_cell;
}


/* Attention : bien passer l'adresse de la cellule 
    quand on appelle la fonction
    ex : insert_cell(&head, 7)
*/
void insert_cell(cell_t **head, int B) {
    cell_t *new_cell;
    cell_t *current;
    cell_t *prev;

    current = *head;
    prev = NULL;

    while (current != NULL && current->B < B) {
        prev = current;
        current = current->next;
    }

    if (current != NULL && current->B == B) {
        current->freq += 1;
        return;
    }

    new_cell = create_cell(B, current);

    if (prev == NULL) {
        *head = new_cell;
    } else {
        prev->next = new_cell;
    }
}

/* Ne pas oublier d'affecter la première
    cellule à NULL après avoir appelé
    la fonction delete
*/
void delete_list(cell_t *head) {
    cell_t *current;
    cell_t *next;
    current = head;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

/* Fonction temporaire pour pouvoir verif
et tester les modifs de liste
*/
void afficher(cell_t *head) {
    cell_t *current = head;

    if (head == NULL) {
        printf("Liste inexistante\n");
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

    insert_cell(&head, 4);
    insert_cell(&head, 1);
    insert_cell(&head, 1);
    printf("\n\n\n");

    afficher(head);

    delete_list(head);
    head = NULL;
    afficher(head);

    return 0;
}












// /* ============= Fonctions Histo (Yann) =============== */

histo_t create_histo() {
    histo_t h = malloc(256 * sizeof(cell_t*));

    for (int r = 0; r < 256; r++) {
        h[r] = malloc(256 * sizeof(cell_t*));
        for (int g = 0; g < 256; g++) {
            h[r][g] = NULL;
        }
    }

    return h;
}
void init_histo(histo_t h,Image* image) {
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {

            unsigned char R = image->pixels[i][j].R;
            unsigned char G = image->pixels[i][j].G;
            unsigned char B = image->pixels[i][j].B;

            insert_cell(&h[R][G], B);
        }
    }
}

void delete_histo(histo_t h) {
    for (int r=0;r<256;r++) {
        for (int g=0;g<256;g++) {
            delete_list(h[r][g]);
            h[r][g] = NULL;
        }
    }
    free(h);
}

// int give_freq_histo(histo_t h,int R,int G,int B) {
//     if (h[R][G] == NULL) {
//         return 0;
//     }

//     cell_t* current;
//     current = h[R][G];
//     while (current != NULL) {
//         if (current -> B == B) {
//             return current.freq;
//         }
//         if (current -> B > B) {
//             return 0;
//         }
//         current = current -> next;
        
//     }
//     return 0;
// }

// /* ======= Partie histo_iter ========= */

// histo_iter create_histo_iter(histo_t h) {
//     histo_iter it = malloc(sizeof(histo_iter_s));
//     if (it == NULL) {
//         perror("Malloc failure");
//         return NULL;
//     }

//     for (int R = 0; R < 256; R++) {
//         for (int G = 0; G < 256; G++) {
//             if (h[R][G] != NULL) {
//                 it->R = R;
//                 it->G = G;
//                 it->current = h[R][G];
//                 return it;
//             }
//         }
//     }
    
//     perror("Empty histo");
//     return NULL;
// }
   
// void start_histo_iter(histo_iter it) {
//     /* 
//      * @TODO Impossible à implémenter pour l'instant car on ne 
//      * sauvegarde nul part la postion initiale...
//      */
// }


// void give_color_histo_iter(histo_iter it,int* tab) {
//     tab[0] = it->R;
//     tab[1] = it->G;
//     tab[2] = it->current->B;
// }

// boolean next_histo_iter(histo_iter it, histo_t h) {

//     if (it->current->next != NULL) {
//         it->current = it->current->next;
//         return true;
//     }

//     for (int R = it->R; R < 256; R++) {

//         int startG;
//         if (R == it->R) {
//             startG = it->G + 1;   
//         } else {
//             startG = 0;      
//         }

//         for (int G = startG; G < 256; G++) {
//             if (h[R][G] != NULL) {
//                 it->R = R;
//                 it->G = G;
//                 it->current = h[R][G];
//                 return true;
//             }
//         }
//     }

//     return false;
// }

// void delete_histo_iter(histo_iter it) {
//     if (it != NULL) {
//         free(it);
//     }
// }
























