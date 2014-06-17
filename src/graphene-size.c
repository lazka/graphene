/* graphene-size.c: Size
 *
 * Copyright © 2014  Emmanuele Bassi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * SECTION:graphene-size
 * @Title: Size
 * @short_description: Size representation
 *
 * #graphene_size_t represents a size composed of a @graphene_size_t.width
 * by a @graphene_size_t.height.
 */

#include "config.h"

#include <math.h>

#include "graphene-point.h"

/**
 * graphene_size_alloc: (constructor)
 *
 * Allocates a new #graphene_size_t.
 *
 * The contents of the returned value are undefined.
 *
 * Returns: (transfer full): the newly allocated #graphene_size_t
 *
 * Since: 1.0
 */
graphene_size_t *
graphene_size_alloc (void)
{
  return calloc (1, sizeof (graphene_size_t));
}

/**
 * graphene_size_free:
 * @s: a #graphene_size_t
 *
 * Frees the resources allocated by graphene_size_alloc().
 *
 * Since: 1.0
 */
void
graphene_size_free (graphene_size_t *s)
{
  free (s);
}

/**
 * graphene_size_init:
 * @s: a #graphene_size_t
 * @width: the width
 * @height: the height
 *
 * Initializes a #graphene_size_t using the given @width and @height.
 
 * Returns: (transfer none): the initialized #graphene_size_t
 *
 * Since: 1.0
 */
graphene_size_t *
graphene_size_init (graphene_size_t *s,
                    float            width,
                    float            height)
{
  g_return_val_if_fail (s != NULL, NULL);

  s->width = width;
  s->height = height;

  return s;
}

/**
 * graphene_size_init_from_size:
 * @s: a #graphene_size_t
 * @src: a #graphene_size_t
 *
 * Initializes a #graphene_size_t using the width and height of
 * the given @src.
 
 * Returns: (transfer none): the initialized #graphene_size_t
 *
 * Since: 1.0
 */
graphene_size_t *
graphene_size_init_from_size (graphene_size_t       *s,
                              const graphene_size_t *src)
{
  g_return_val_if_fail (s != NULL, NULL);
  g_return_val_if_fail (src != NULL, s);

  *s = *src;

  return s;
}

/**
 * graphene_size_equal:
 * @a: a #graphene_size_t
 * @b: a #graphene_size_t
 *
 * Checks whether the two give #graphene_size_t are equal.
 *
 * Returns: %TRUE if the sizes are equal
 *
 * Since: 1.0
 */
gboolean
graphene_size_equal (const graphene_size_t *a,
                     const graphene_size_t *b)
{
  if (a == b)
    return TRUE;

  if (a == NULL || b == NULL)
    return FALSE;

  return fabsf (a->width - b->width) < GRAPHENE_FLOAT_EPSILON &&
         fabsf (a->height - b->height) < GRAPHENE_FLOAT_EPSILON;
}

/**
 * graphene_size_scale:
 * @s: a #graphene_size_t
 * @factor: the scaling factor
 * @res: (out caller-allocates): return location for the scaled size
 *
 * Scales the components of a #graphene_size_t using the given @factor.
 *
 * Since: 1.0
 */
void
graphene_size_scale (const graphene_size_t *s,
                     float                  factor,
                     graphene_size_t       *res)
{
  g_return_if_fail (s != NULL);
  g_return_if_fail (res != NULL);

  *res = *s;

  res->width *= factor;
  res->height *= factor;
}

/**
 * graphene_size_interpolate:
 * @a: a #graphene_size_t
 * @b: a #graphene_size_t
 * @factor: the linear interpolation factor
 * @res: (out caller-allocates): return location for the interpolated size
 *
 * Linearly interpolates the two given #graphene_size_t using the given
 * interpolation @factor.
 *
 * Since: 1.0
 */
void
graphene_size_interpolate (const graphene_size_t *a,
                           const graphene_size_t *b,
                           double                 factor,
                           graphene_size_t       *res)
{
  g_return_if_fail (a != NULL && b != NULL);
  g_return_if_fail (res != NULL);

  res->width = a->width + (b->width - a->width) * factor;
  res->height = a->height + (b->height - a->height) * factor;
}

static const graphene_size_t _graphene_size_zero = GRAPHENE_SIZE_INIT_ZERO;

/**
 * graphene_size_zero:
 *
 * A constant pointer to a zero #graphene_size_t, useful for
 * equality checks and interpolations.
 *
 * Returns: (transfer none): a constant size
 *
 * Since: 1.0
 */
const graphene_size_t *
graphene_size_zero (void)
{
#ifdef GRAPHENE_ENABLE_DEBUG
  g_assert (_graphene_size_zero.width == 0.f);
  g_assert (_graphene_size_zero.height == 0.f);
#endif

  return &_graphene_size_zero;
}
