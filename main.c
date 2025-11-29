#include <stdio.h>
#include <stdlib.h>

typedef struct coordinates {
    int* x;
    int* y;
    int* z;
} coordinates_t;

typedef enum Errors {
    ERROR_NONE = 0,
    ERROR_MEMORY = 1,
    ERROR_INVALID = 2,
    ERROR_OVERFLOW = 3,
    ERROR_UNKNOWN = 99
} Errors_t;

int main(void) {
    coordinates_t coor1 = {
        .x = malloc(sizeof(int)),
        .y = malloc(sizeof(int)),
        .z = malloc(sizeof(int))
    };
    if (!coor1.x || !coor1.y || !coor1.z) {
        free(coor1.x);
        free(coor1.y);
        free(coor1.z);
        return ERROR_MEMORY;
    }
    int* coords[] = {coor1.x, coor1.y, coor1.z};
    const char* names[] = {"x", "y", "z"};

    for (int i = 0; i < 3; i++) {
        printf("%s: ", names[i]);
        if (scanf("%d", coords[i]) != 1) {
            printf("Invalid input!\n");
            free(coor1.x);
            free(coor1.y);
            free(coor1.z);
            return ERROR_INVALID;
        }
        printf("%s = %d\n", names[i], *coords[i]);
    }
    free(coor1.x);
    free(coor1.y);
    free(coor1.z);
    return ERROR_NONE;
}
