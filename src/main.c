#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"
#include "../include/histo.h"
#include "../include/quantification.h"

int main(int argc, char **argv) {

    /* --- Vérification des arguments --- */
    if (argc != 3) {
        printf("Nombre d'arguments incorect");
        return 1;
    }

    int K = atoi(argv[1]);
    if (K <= 0) {
        fprintf(stderr, "K doit être strictement positif.\n");
        return 1;
    }

    /* --- Ouverture du fichier d'entrée --- */
    FILE *f = fopen(argv[2], "r");
    if (!f) {
        perror("Erreur fopen input");
        return 1;
    }

    /* --- Chargement de l'image --- */
    Image *input = load_pnm(f);
    fclose(f);

    if (!input) {
        fprintf(stderr, "Erreur load_pnm\n");
        return 1;
    }

    /* --- Création et initialisation de l'histogramme --- */
    histo_t h = create_histo();
    if (!h) {
        fprintf(stderr, "Erreur create_histo\n");
        free_image(input);
        return 1;
    }

    init_histo(h, input);

    /* --- Allocation de la table des K couleurs --- */
    int *tab = malloc(K * 3 * sizeof(int));
    if (!tab) {
        fprintf(stderr, "Erreur malloc tab\n");
        delete_histo(h);
        free_image(input);
        return 1;
    }

    /* --- Quantification : trouver les K couleurs les plus fréquentes --- */
    quantification(h, tab, K);

    /* --- Création de l'image de sortie --- */
    Image *output = create_image(input->width, input->height);
    if (!output) {
        fprintf(stderr, "Erreur create_image\n");
        free(tab);
        delete_histo(h);
        free_image(input);
        return 1;
    }

    /* --- Mapping : remplacer chaque pixel par la couleur la plus proche --- */
    mapping(input, output, tab, K);

    /* --- Sauvegarde de l'image de sortie --- */
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

    /* --- Nettoyage mémoire --- */
    free(tab);
    delete_histo(h);
    free_image(input);
    free_image(output);

    printf("Image quantifiée sauvegardée dans output.ppm\n");
    return 0;
}