#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "histo.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("Il manque un argument");
        return 1;
    }

    image_t img = load_pnm(argv[1]);
    histo h = create_histo(img);

    histo_iter it = create_histo_iter(h);

    int rgb[3];

    while (next_histo_iter(it)) {
        give_color_histo_iter(it, rgb);

        int R = rgb[0];
        int G = rgb[1];
        int B = rgb[2];

        int lum = (R + G + B) / 3;
        int freq = give_freq_histo(h, R, G, B);

        printf("%d %d %d %d %d\n", R, G, B, lum, freq);

        next_histo_iter(it);
    }

    delete_histo_iter(it);
    delete_histo(h);
    delete_image(img);

    return 0;
}
