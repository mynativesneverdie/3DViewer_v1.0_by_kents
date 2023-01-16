#ifndef SRC_PARCER_OBJ_H
#define SRC_PARSER_OBJ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Matrix {
    double **matrix;
    int rows;
    int cols;
} matrix_t;

typedef struct facets {
    int *vertexes;
    int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
    int count_of_vertexes;
    int count_of_facets;
    matrix_t matrix_3d;
    polygon_t *polygons;
};

#endif SRC_PARSER_OBJ_H