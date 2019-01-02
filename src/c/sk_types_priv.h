/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef sk_types_priv_DEFINED
#define sk_types_priv_DEFINED

#include "sk_types.h"

class SkMaskFilter;
class SkPaint;
class SkShader;
class SkTypeface;
class SkFontMetrics;
class SkRect;
enum class SkTextEncoding;

static inline const SkPaint& AsPaint(const sk_paint_t& cpaint) {
    return reinterpret_cast<const SkPaint&>(cpaint);
}

static inline const SkPaint* AsPaint(const sk_paint_t* cpaint) {
    return reinterpret_cast<const SkPaint*>(cpaint);
}

static inline SkPaint* AsPaint(sk_paint_t* cpaint) {
    return reinterpret_cast<SkPaint*>(cpaint);
}

static inline SkMaskFilter* AsMaskFilter(sk_maskfilter_t* cfilter) {
    return reinterpret_cast<SkMaskFilter*>(cfilter);
}

static inline sk_maskfilter_t* ToMaskFilter(SkMaskFilter* filter) {
    return reinterpret_cast<sk_maskfilter_t*>(filter);
}

static inline SkShader* AsShader(sk_shader_t* cshader) {
    return reinterpret_cast<SkShader*>(cshader);
}

static sk_typeface_t* ToTypeface(SkTypeface* typeface) {
  return reinterpret_cast<sk_typeface_t*>(typeface);
}

static SkTypeface* AsTypeface(sk_typeface_t* ctypeface) {
  return reinterpret_cast<SkTypeface*>(ctypeface);
}

static sk_font_metrics_t* ToFontMetrics(SkFontMetrics* rect) {
  return reinterpret_cast<sk_font_metrics_t*>(rect);
}

static SkFontMetrics* AsFontMetrics(sk_font_metrics_t* cmetrics) {
  return reinterpret_cast<SkFontMetrics*>(cmetrics);
}

static sk_rect_t* ToRect(SkRect* rect) {
  return reinterpret_cast<sk_rect_t*>(rect);
}

static SkRect* AsRect(sk_rect_t* crect) {
  return reinterpret_cast<SkRect*>(crect);
}

static sk_text_encoding_t ToTextEncoding(SkTextEncoding encoding) {
  return (sk_text_encoding_t)(encoding);
}

static SkTextEncoding AsTextEncoding(sk_text_encoding_t cencoding) {
  return (SkTextEncoding)(cencoding);
}

#endif
