#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info {
  unsigned int index_v;
  unsigned int index_f;
  unsigned int index_p;
  unsigned int *arr_f;
  float *arr_v;
  float max_v;
};

void parse_file(char *fileName, struct info *src);
void free_dataset(struct info *src);

#endif // SRC_PARSER_PARSER_H_
