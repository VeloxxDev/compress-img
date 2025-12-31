#include <stdio.h>
#include <stdlib.h>
#include "../include/minunit.h"
#include "../include/image.h"
#include "../include/histo.h"


MU_TEST(test_histo_pipeline_with_file) {
    const char *fname = "./test.ppm";

    FILE *f = fopen(fname, "r");
    mu_check(f != NULL);

    Image *img = load_pnm(f);
    fclose(f);
    mu_check(img != NULL);

    histo_t h = create_histo();
    mu_check(h != NULL);

    init_histo(h, img);

    mu_assert_int_eq(2, give_freq_histo(h, 255, 0, 0));   // rouge
    mu_assert_int_eq(1, give_freq_histo(h, 0, 255, 0));   // vert
    mu_assert_int_eq(1, give_freq_histo(h, 0, 0, 255));   // bleu


    histo_iter it = create_histo_iter(h);
    mu_check(it != NULL);

    int rgb[3];
    int seen_red = 0, seen_green = 0, seen_blue = 0;

    do {
        give_color_histo_iter(it, rgb);

        if (rgb[0] == 255 && rgb[1] == 0 && rgb[2] == 0)
            seen_red = 1;
        else if (rgb[0] == 0 && rgb[1] == 255 && rgb[2] == 0)
            seen_green = 1;
        else if (rgb[0] == 0 && rgb[1] == 0 && rgb[2] == 255)
            seen_blue = 1;
        else
            mu_check(0 && "Couleur inattendue dans l'itérateur");

    } while (next_histo_iter(it, h));

    mu_check(seen_red);
    mu_check(seen_green);
    mu_check(seen_blue);

    delete_histo_iter(it);
    delete_histo(h);
    free_image(img);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_histo_pipeline_with_file);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}