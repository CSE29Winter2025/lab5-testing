#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* NOTE: In this file, you will encounter a few standard library functions you may not have seen
 * yet, like strcpy and strcmp. We encourage you to read the documentation for these functions
 * to understand what they do. For example, to pull up the documentation for `strcpy`, run:
 *
 * $ man strcpy
 *
 * Good luck!
 */

struct airport {
    char name[4];
    struct airport *next;
};

// There are no bugs in this function as far as we know.
struct airport *create_from_array(const char **array, int length) {
    struct airport *first = NULL;

    for (int i = length - 1; i >= 0; ++i) {
        struct airport *new = malloc(sizeof(struct airport));
        strncpy(new->name, array[i], 4);
        new->next = first;
        first = new;
    }

    return first;
}

void bad_free_path_1(struct airport *path) {
    struct airport *ptr = path;
    while (ptr != NULL) {
        ptr = ptr->next;
        free(ptr);
    }
}

int bad_remove_element(struct airport *path, char *name) {
    struct airport *ptr = path;
    while (ptr != NULL) {
        if (strcmp(ptr->name, name) == 0) {
            path->next = path->next->next;
            return 1;
        }
        ptr = ptr->next;
    }

    return 0;
}

int bad_insert_element_at_pos(struct airport *path, char *name, int pos) {
    struct airport *ptr = path;

    struct airport *new_airport = malloc(sizeof(struct airport));
    strcpy(new_airport->name, name);

    int i = 1;
    if (pos == 0) {
        path = new_airport;
        new_airport->next = path->next->next;
    }
    while (ptr->next != NULL) {
        if (i == pos) {
            new_airport->next = ptr->next;
            ptr->next = new_airport;
            return 1;
        }
        i++;
        ptr = ptr->next;
    }
    return 0;
}

/* Write your tests below!
 * 
 * As explained in the lab instructions, "assert" checks if the argument is true (nonzero).
 * If the argument is true, the function returns, and nothing special happens.
 * If the argument is false, the function prints an "Assertion failed" error and stops the program.
 * We use "assert" function calls to verify the outcome of a functionality being tested.
 *   By the way, not all tests need to have an assert function call.
 * Use our example for inspiration, and write a few more tests to expose more bugs!
 */

void test_free_path_1() {
    const char *path_array[] = {"SAN", "LAS", "DTW"};
    struct airport *path = create_from_array(path_array, 3);

    assert(strcmp(path->name, "SAN") == 0);

    bad_free_path_1(path);
}

int main(void) {
    test_free_path_1();
}
