#include "bmp.h"

#include "util.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define PRI_SPECIFIER(e) (_Generic((e), uint16_t          \
                                   : "%" PRIu16, uint32_t \
                                   : "%" PRIu32, default  \
                                   : "NOT IMPLEMENTED"))

#define PRINT_FIELD(t, name)                             \
  fprintf(f, "%-17s: ", #name);                          \
  fprintf(f, PRI_SPECIFIER(header->name), header->name); \
  fprintf(f, "\n");

void bmp_header_print(struct bmp_header const *header, FILE *f)
{
  FOR_BMP_HEADER(PRINT_FIELD)
}

static enum read_status read_header(FILE *f, struct bmp_header *header)
{
  return !fread(header, sizeof(struct bmp_header), 1, f);
}

static enum read_status read_image(FILE *in, struct image *img)
{
  const uint8_t mod_4    = img->width * 3 % 4;
  const uint64_t padding = mod_4 ? 4 - mod_4 : 0;

  img->data = (struct pixel *) malloc(sizeof(struct pixel) * img->width * img->height);
  for (size_t i = 0; i < img->height; i++) {
    fread(img->data, sizeof(struct pixel), img->width, in);
    fseek(in, padding, SEEK_CUR);
  }

  return READ_OK;
}

// static enum write_status write_image(FILE *out, struct image const *img)
// {
//   return WRITE_OK;
// }

enum read_status read_bmp_from_file(
    const char *filename,
    struct bmp_header *p_header,
    struct image *p_img)
{
  if (!filename)
  {
    err("Bad file path\n");
    return READ_INVALID_SIGNATURE;
  }
  FILE *f = fopen(filename, "rb");
  if (!f)
  {
    err("Can't open file\n");
    return READ_INVALID_SIGNATURE;
  }

  if (read_header(f, p_header))
  {
    err("Can't read header\n");
    fclose(f);
    return READ_INVALID_HEADER;
  }

  p_img->width  = p_header->biWidth;
  p_img->height = p_header->biHeight;
  if (read_image(f, p_img))
  {
    err("Can't read image\n");
    fclose(f);
    return READ_INVALID_BITS;
  }

  fclose(f);
  return READ_OK;
}
