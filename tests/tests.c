#include <stdio.h>
#include "histo.h"
#include "minunit.h"

int tests_run = 0;

static char * test_add() {
    mu_assert("Erreur: add(1,2) != 3", add(1, 2) == 3);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_add);
    return 0;
}

int main() {
    char *result = all_tests();
    if (result != 0) {
        printf("❌ %s\n", result);
    } else {
        printf("✅ Tous les tests sont passés\n");
    }
    printf("Tests exécutés: %d\n", tests_run);

    return result != 0;
}
