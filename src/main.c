#include <stdio.h>

#include "bmp.h"
#include "util.h"
#include "image.h"

void usage()
{
  fprintf(stderr, "Usage: make run ARGS=\"BMP_FILE_NAME\"\n");
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    usage();
  }
  if (argc < 2)
  {
    err("Not enough arguments \n");
  }
  else if (argc > 2)
  {
    err("Too many arguments \n");
  }

  struct bmp_header h = {0};
  struct image img = {0};

  if (!read_bmp_from_file(argv[1], &h, &img))
  {
    bmp_header_print(&h, stdout);
  }
  else
  {
    err("Failed to open BMP file or reading header or picture.\n");
  }

  return 0;
}
