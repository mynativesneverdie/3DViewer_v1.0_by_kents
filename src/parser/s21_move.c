
#include "s21_parser.h"

void move_axis(struct info *src, float x_offset, float y_offset, float z_offset) {
    for (unsigned int k = 0; k < src->index_v; k += 3) {
        src->arr_v[k + 0] += x_offset;
        src->arr_v[k + 1] += y_offset;
        src->arr_v[k + 2] += z_offset;
    }
}