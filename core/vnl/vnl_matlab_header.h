#ifndef vnl_matlab_header_h_
#define vnl_matlab_header_h_
#ifdef __GNUC__
#pragma interface
#endif
/*
  fsm@robots.ox.ac.uk
*/

//#undef LITTLE_ENDIAN
//#undef BIG_ENDIAN

struct vnl_matlab_header/*MATFileHeader*/ {
  long type; // sum of one byte order, one storage specifier and one precision specifier
  long rows;
  long cols;
  long imag;
  long namlen;
  
  enum type_t {
    // precision specifier
    vnl_DOUBLE_PRECISION = 0,
    vnl_SINGLE_PRECISION = 10,
    // storage specifier
    vnl_COLUMN_WISE = 0,
    vnl_ROW_WISE    = 100,
    // byte order
    vnl_LITTLE_ENDIAN = 0,
    vnl_BIG_ENDIAN    = 1000,
    //
    vnl_none = 0
  };
};

#endif // vnl_matlab_header_h_
