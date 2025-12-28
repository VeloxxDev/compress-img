#include <stdio.h>
#include <stdlib.h>


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

void init_histo(histo h,FILE* image) {
    /* TODO Jsp comment traiter les images */
    
}

void delete_histo(histo h) {
    for (int r=0;r<256;r++) {
        for (int g=0;g<256;g++) {
            delete_list(histo[r][g]);
        }
    }
}

