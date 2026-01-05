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
  * @file test_histo.c
  */

#include "minunit.h"
#include <stdlib.h>   
#include <string.h>
#include "../include/histo.h"
#include "../include/image.h"

/* Setup / Teardown */
void test_setup(void) { }
void test_teardown(void) { }

/*
   TESTS LISTES CHAÎNÉES
 */

MU_TEST(test_create_cell) {
    cell_t *c = create_cell(42, NULL);
    mu_check(c != NULL);
    mu_check(c->B == 42);
    mu_check(c->freq == 1);
    mu_check(c->next == NULL);
    free(c);
}

MU_TEST(test_insert_cell) {
    cell_t *head = NULL;

    insert_cell(&head, 10);
    mu_check(head->B == 10);
    mu_check(head->freq == 1);

    insert_cell(&head, 5);
    mu_check(head->B == 5);
    mu_check(head->next->B == 10);

    insert_cell(&head, 10);
    mu_check(head->next->freq == 2);

    delete_list(head);
}

/*
   TESTS HISTOGRAMME
 */

static Image *fake_image() {
    Image *img = malloc(sizeof(Image));
    img->width = 2;
    img->height = 2;
    img->pixels = malloc(12);

    unsigned char data[] = {
        10,20,30,  10,20,30,
        50,60,70,  10,20,30
    };
    memcpy(img->pixels, data, 12);
    return img;
}

MU_TEST(test_create_histo) {
    histo_t h = create_histo();
    mu_check(h != NULL);
    mu_check(h[0][0] == NULL);
    delete_histo(h);
}

MU_TEST(test_init_histo) {
    Image *img = fake_image();
    histo_t h = create_histo();

    init_histo(h, img);

    mu_check(give_freq_histo(h,10,20,30) == 3);
    mu_check(give_freq_histo(h,50,60,70) == 1);
    mu_check(give_freq_histo(h,1,2,3) == 0);

    delete_histo(h);
    free(img->pixels);
    free(img);
}

/*
   TESTS ITÉRATEUR
*/

MU_TEST(test_histo_iter) {
    Image *img = malloc(sizeof(Image));
    img->width = 1;
    img->height = 2;
    img->pixels = malloc(6);

    unsigned char data[] = { 1,2,3, 4,5,6 };
    memcpy(img->pixels, data, 6);

    histo_t h = create_histo();
    init_histo(h, img);

    histo_iter it = create_histo_iter(h);
    mu_check(it != NULL);

    int tab[3];
    give_color_histo_iter(it, tab);
    mu_check(tab[0] == 1);
    mu_check(tab[1] == 2);
    mu_check(tab[2] == 3);

    mu_check(next_histo_iter(it, h) == true);
    give_color_histo_iter(it, tab);
    mu_check(tab[2] == 6);

    mu_check(next_histo_iter(it, h) == false);

    delete_histo_iter(it);
    delete_histo(h);
    free(img->pixels);
    free(img);
}

/*
   SUITE DE TESTS
*/

MU_TEST_SUITE(histo_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_create_cell);
    MU_RUN_TEST(test_insert_cell);

    MU_RUN_TEST(test_create_histo);
    MU_RUN_TEST(test_init_histo);

    MU_RUN_TEST(test_histo_iter);
}

/*
   MAIN
*/

int main() {
    MU_RUN_SUITE(histo_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
