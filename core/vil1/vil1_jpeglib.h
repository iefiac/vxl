#ifndef vil_jpeglib_h_
#define vil_jpeglib_h_
#ifdef __GNUC__
#pragma interface
#endif
/*
  fsm@robots.ox.ac.uk
*/

#include <vcl/vcl_cstdio.h>
#include <vcl/vcl_cstdlib.h>

// ?
extern "C" {
#define boolean jpeg_boolean
#include <jpeglib.h>
#include <jerror.h>
#undef boolean
}

#endif // vil_jpeglib_h_
