#include "s21_parser.h"
#include <locale.h>

static void parse_f(FILE *file, struct info *src);
static void parse_v(FILE *file, struct info *src);

void parse_file(char *file_name, struct info *src) {
  setlocale(LC_ALL, "POSIX");

  FILE *file = fopen(file_name, "r");
  src->index_f = 0;
  src->index_v = 0;
  src->index_p = 0;
  src->max_v = 0;

  char ch = '\0', buff = '\0';

  while (ch != EOF) {
    ch = fgetc(file);
    if (buff == 'v' && ch == ' ') {
      parse_v(file, src);
    } else if (buff == 'f' && ch == ' ') {
      parse_f(file, src);
    }
    buff = ch;
  }

  fclose(file);
}

static void parse_v(FILE *file, struct info *src) {
  src->arr_v = realloc(src->arr_v, (src->index_v + 3) * sizeof(float));

  if (src->arr_v != NULL) {
    int ch_num =
        fscanf(file, "%f %f %f", &src->arr_v[src->index_v + 0],
               &src->arr_v[src->index_v + 1], &src->arr_v[src->index_v + 2]);

    for (int k = 0; k < 3; k++) {
      if (fabs(src->arr_v[src->index_v + k]) > src->max_v) {
        src->max_v = fabs(src->arr_v[src->index_v + k]);
      }
    }

    src->index_v += 3;
  } else {
    printf("Allocation memory error in parse v 2\n");
    exit(1);
  }
}

void free_dataset(struct info *src) {
  free(src->arr_f);
  free(src->arr_v);
}


static void parse_f(FILE *file, struct info *src) {
  int vertice = 0;
  int init = 0;

  src->index_p++;  // count polygons
  int first_index = src->index_f;

  while (fscanf(file, "%d/%*d/%*d", &vertice) == 1) {
    if (init < 2) {
      src->arr_f = realloc(src->arr_f, (src->index_f + 1) * sizeof(unsigned int));

      src->arr_f[src->index_f] = vertice - 1;
      src->index_f += 1;
    } else {
      src->arr_f = realloc(src->arr_f, (src->index_f + 2) * sizeof(unsigned int));

      src->arr_f[src->index_f] = src->arr_f[src->index_f - 1];
      src->arr_f[src->index_f + 1] = vertice - 1;
      src->index_f += 2;
    }

    init++;
  }

  src->arr_f = realloc(src->arr_f, (src->index_f + 2) * sizeof(unsigned int));
  src->arr_f[src->index_f] = src->arr_f[first_index];
  src->arr_f[src->index_f + 1] = src->arr_f[src->index_f - 1];
  src->index_f += 2;
}

