/* This file is an image processing operation for GEGL
 */


#ifdef GEGL_PROPERTIES
   /* no properties */
#else

#define GEGL_OP_POINT_FILTER

#ifndef IMGFLO_OP_NAME
#define IMGFLO_OP_NAME(orig) orig
#endif

#include "gegl-op.h"

static void prepare (GeglOperation *operation)
{
  const Babl *format = babl_format ("YA float");
  gegl_operation_set_format (operation, "input", format);
  gegl_operation_set_format (operation, "output", format);
}

gboolean
process(GeglOperation *op,
        void *in_buf, void *out_buf, glong samples,
        const GeglRectangle *roi, gint level)
{
  float *in = in_buf;
  float *out = out_buf;
  while (samples--)
    {
      *out++ = *in++;
      *out++ = *in++;
    }

  return TRUE;
}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class = GEGL_OPERATION_CLASS (klass);
  GeglOperationPointFilterClass *point_filter_class = GEGL_OPERATION_POINT_FILTER_CLASS (klass);

  point_filter_class->process = process;
  operation_class->prepare = prepare;

  gegl_operation_class_set_keys (operation_class,
      "name",        IMGFLO_OP_NAME("imgflo:example"),
      "title",       "imgflo: Make Grey",
      "categories" , "grayscale:color",
      "description", "Turns the image grayscale",
      NULL);
}

#endif
