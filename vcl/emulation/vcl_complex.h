#ifndef vcl_emulation_complex_h
#define vcl_emulation_complex_h
#define VCL_COMPLEX_AVAILABLE

#include <vcl/vcl_compiler.h>
#include <vcl/vcl_cmath.h>
#include <vcl/vcl_iostream.h>

// The Sunpro 4.2 compiler has a bug that it will not instantiate
// inline friend functions with global linkage, so we remove
// all the inline's while instantiation is taking place.

#if defined(__SUNPRO_CC) && defined(INSTANTIATE_TEMPLATES)
# define inline
#endif

#include <vcl/emulation/vcl_functional.h> // for op!=

// implementation of class vcl_complex<FLOAT>, copied from g++ 2.7.2 - PVR

#if defined (VCL_VC50)
template <class FLOAT> class vcl_complex;
typedef vcl_complex<double> vcl_double_complex;
typedef vcl_complex<float> vcl_float_complex;
#endif

template <class FLOAT>
class vcl_complex
{
public:
  vcl_complex (FLOAT r = 0, FLOAT i = 0): re (r), im (i) { }
#if VCL_HAS_MEMBER_TEMPLATES
  template <class T>  
  vcl_complex (vcl_complex<T> const& that): re(that.real()), im(that.imag()) {}
#else
#if defined (VCL_VC50)
  vcl_complex (vcl_float_complex const& that): re(that.real()), im(that.imag()) {}
  vcl_complex (vcl_double_complex const& that): re(that.real()), im(that.imag()) {}
#else
  vcl_complex (vcl_complex<float> const& that): re(that.real()), im(that.imag()) {}
  vcl_complex (vcl_complex<double> const& that): re(that.real()), im(that.imag()) {}
#endif
#endif

  vcl_complex& operator += (const vcl_complex&);
  vcl_complex& operator -= (const vcl_complex&);
  vcl_complex& operator *= (const vcl_complex&);
  vcl_complex& operator /= (const vcl_complex&);
  FLOAT real () const { return re; }
  FLOAT imag () const { return im; }
private:
  FLOAT re, im;
};


template <class FLOAT>
inline vcl_complex<FLOAT>&
vcl_complex<FLOAT>::operator += (const vcl_complex<FLOAT>& r)
{
  re += r.real();
  im += r.imag();
  return *this;
}

template <class FLOAT>
inline vcl_complex<FLOAT>&
vcl_complex<FLOAT>::operator -= (const vcl_complex<FLOAT>& r)
{
  re -= r.real();
  im -= r.imag();
  return *this;
}

template <class FLOAT>
inline vcl_complex<FLOAT>&
vcl_complex<FLOAT>::operator *= (const vcl_complex<FLOAT>& r)
{
  FLOAT f = re * r.real() - im * r.imag();
  im = re * r.imag() + im * r.real();
  re = f;
  return *this;
}

template <class FLOAT>
inline vcl_complex<FLOAT>&
vcl_complex<FLOAT>::operator /= (const vcl_complex<FLOAT>& y)
{
  FLOAT ar = (FLOAT) fabs (y.real());
  FLOAT ai = (FLOAT) fabs (y.imag());
  FLOAT nr, ni;
  FLOAT t, d;
  if (ar <= ai)
    {
      t = y.real() / y.imag();
      d = y.imag() * (1 + t*t);
      nr = (re * t + im) / d;
      ni = (im * t - re) / d;
    }
  else
    {
      t = y.imag() / y.real();
      d = y.real() * (1 + t*t);
      nr = (re + im * t) / d;
      ni = (im - re * t) / d;
    }
  re = nr;
  im = ni;
  return *this;
}

template <class FLOAT> inline FLOAT
real (vcl_complex<FLOAT> const& x) { return x.real(); }

template <class FLOAT> inline FLOAT
imag (vcl_complex<FLOAT> const& x) { return x.imag(); }


template <class FLOAT> inline vcl_complex<FLOAT>
operator + (const vcl_complex<FLOAT>& x, const vcl_complex<FLOAT>& y)
{
  return vcl_complex<FLOAT> (x.real() + y.real(), x.imag() + y.imag());
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator + (const vcl_complex<FLOAT>& x, FLOAT y)
{
  return vcl_complex<FLOAT> (x.real() + y, x.imag());
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator + (FLOAT x, const vcl_complex<FLOAT>& y)
{
  return vcl_complex<FLOAT> (x + y.real(), y.imag());
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator - (const vcl_complex<FLOAT>& x, const vcl_complex<FLOAT>& y)
{
  return vcl_complex<FLOAT> (x.real() - y.real(), x.imag() - y.imag());
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator - (const vcl_complex<FLOAT>& x, FLOAT y)
{
  return vcl_complex<FLOAT> (x.real() - y, x.imag());
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator - (FLOAT x, const vcl_complex<FLOAT>& y)
{
  return vcl_complex<FLOAT> (x - y.real(), - y.imag());
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator * (const vcl_complex<FLOAT>& x, const vcl_complex<FLOAT>& y)
{
  return vcl_complex<FLOAT> (x.real() * y.real() - x.imag() * y.imag(),
			   x.real() * y.imag() + x.imag() * y.real());
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator * (const vcl_complex<FLOAT>& x, FLOAT y)
{
  return vcl_complex<FLOAT> (x.real() * y, x.imag() * y);
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator * (FLOAT x, const vcl_complex<FLOAT>& y)
{
  return vcl_complex<FLOAT> (x * y.real(), x * y.imag());
}

template <class FLOAT> vcl_complex<FLOAT>
operator / (const vcl_complex<FLOAT>& x, FLOAT y)
{
  return vcl_complex<FLOAT> (x.real() / y, x.imag() / y);
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator + (const vcl_complex<FLOAT>& x)
{
  return x;
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator - (const vcl_complex<FLOAT>& x)
{
  return vcl_complex<FLOAT> (-x.real(), -x.imag());
}

template <class FLOAT> inline bool
operator == (const vcl_complex<FLOAT>& x, const vcl_complex<FLOAT>& y)
{
  return x.real() == y.real() && x.imag() == y.imag();
}

template <class FLOAT> inline bool
operator == (const vcl_complex<FLOAT>& x, FLOAT y)
{
  return x.real() == y && x.imag() == 0;
}

template <class FLOAT> inline bool
operator == (FLOAT x, const vcl_complex<FLOAT>& y)
{
  return x == y.real() && y.imag() == 0;
}

// template <class FLOAT> inline bool
// operator != (const vcl_complex<FLOAT>& x, const vcl_complex<FLOAT>& y)
// {
//   return x.real() != y.real() || x.imag() != y.imag();
// }

template <class FLOAT> inline bool
operator != (const vcl_complex<FLOAT>& x, FLOAT y)
{
  return x.real() != y || x.imag() != 0;
}

template <class FLOAT> inline bool
operator != (FLOAT x, const vcl_complex<FLOAT>& y)
{
  return x != y.real() || y.imag() != 0;
}

template <class FLOAT> inline FLOAT
abs (const vcl_complex<FLOAT>& x)
{
  return (FLOAT) hypot (x.real(), x.imag());
}

template <class FLOAT> inline FLOAT
arg (const vcl_complex<FLOAT>& x)
{
  return (FLOAT) atan2 (x.imag(), x.real());
}

template <class FLOAT> inline vcl_complex<FLOAT>
polar (FLOAT r, FLOAT t)
{
  return vcl_complex<FLOAT> (r * cos (t), r * sin (t));
}

template <class FLOAT> inline vcl_complex<FLOAT>
conj (const vcl_complex<FLOAT>& x)
{
  return vcl_complex<FLOAT> (x.real(), -x.imag());
}

template <class FLOAT> inline FLOAT
norm (const vcl_complex<FLOAT>& x)
{
  return x.real() * x.real() + x.imag() * x.imag();
}

template <class FLOAT> vcl_complex<FLOAT>
cos (const vcl_complex<FLOAT>& x)
{
  return vcl_complex<FLOAT> (cos (x.real()) * cosh (x.imag()),
			   - sin (x.real()) * sinh (x.imag()));
}

template <class FLOAT> inline vcl_complex<FLOAT>
cosh (const vcl_complex<FLOAT>& x)
{
  return vcl_complex<FLOAT> (cosh (x.real()) * cos (x.imag()),
			   sinh (x.real()) * sin (x.imag()));
}

template <class FLOAT> inline vcl_complex<FLOAT>
exp (const vcl_complex<FLOAT>& x)
{
  return polar (FLOAT (exp (x.real())), x.imag());
}


template <class FLOAT> inline vcl_complex<FLOAT>
log (const vcl_complex<FLOAT>& x)
{
  return vcl_complex<FLOAT> (log (abs (x)), (FLOAT) atan2 (x.imag(), x.real()));
}

template <class FLOAT> inline vcl_complex<FLOAT>
pow (const vcl_complex<FLOAT>& x, const vcl_complex<FLOAT>& y)
{
  FLOAT logr = log (abs (x));
  FLOAT t = (FLOAT) atan2 (x.imag(), x.real()); // was arg, but sunCC messed up WAH

  return polar (FLOAT (exp (logr * y.real() - y.imag() * t)),
		FLOAT (y.imag() * logr + y.real() * t));
}

template <class FLOAT> inline vcl_complex<FLOAT>
pow (const vcl_complex<FLOAT>& x, FLOAT y)
{
  return exp (FLOAT (y) * log (x));
}

template <class FLOAT> inline vcl_complex<FLOAT>
pow (FLOAT x, const vcl_complex<FLOAT>& y)
{
  return exp (y * FLOAT (log (x)));
}

template <class FLOAT> inline vcl_complex<FLOAT>
sin (const vcl_complex<FLOAT>& x)
{
  return vcl_complex<FLOAT> (sin (x.real()) * cosh (x.imag()),
			   cos (x.real()) * sinh (x.imag()));
}

template <class FLOAT> inline vcl_complex<FLOAT>
sinh (const vcl_complex<FLOAT>& x)
{
  return vcl_complex<FLOAT> (sinh (x.real()) * cos (x.imag()),
			   cosh (x.real()) * sin (x.imag()));
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator / (const vcl_complex<FLOAT>& x, const vcl_complex<FLOAT>& y)
{
  FLOAT ar = fabs (y.real());
  FLOAT ai = fabs (y.imag());
  FLOAT nr, ni;
  FLOAT t, d;
  if (ar <= ai)
    {
      t = y.real() / y.imag();
      d = y.imag() * (1 + t*t);
      nr = (x.real() * t + x.imag()) / d;
      ni = (x.imag() * t - x.real()) / d;
    }
  else
    {
      t = y.imag() / y.real();
      d = y.real() * (1 + t*t);
      nr = (x.real() + x.imag() * t) / d;
      ni = (x.imag() - x.real() * t) / d;
    }
  return vcl_complex<FLOAT> (nr, ni);
}

template <class FLOAT> inline vcl_complex<FLOAT>
operator / (FLOAT x, const vcl_complex<FLOAT>& y)
{
  FLOAT ar = fabs (y.real());
  FLOAT ai = fabs (y.imag());
  FLOAT nr, ni;
  FLOAT t, d;
  if (ar <= ai)
    {
      t = y.real() / y.imag();
      d = y.imag() * (1 + t*t);
      nr = x * t / d;
      ni = -x / d;
    }
  else
    {
      t = y.imag() / y.real();
      d = y.real() * (1 + t*t);
      nr = x / d;
      ni = -x * t / d;
    }
  return vcl_complex<FLOAT> (nr, ni);
}

template <class FLOAT> inline vcl_complex<FLOAT>
pow (const vcl_complex<FLOAT>& xin, int y)
{
  if (y == 0)
    return vcl_complex<FLOAT> (1.0);
  vcl_complex<FLOAT> r (1.0);
  vcl_complex<FLOAT> x (xin);
  if (y < 0)
    {
      y = -y;
      x = ((FLOAT)1.0)/x;
    }
  for (;;)
    {
      if (y & 1)
	r *= x;
      if (y >>= 1)
	x *= x;
      else
	return r;
    }
}

template <class FLOAT> inline vcl_complex<FLOAT>
sqrt (const vcl_complex<FLOAT>& x)
{
  FLOAT r = abs (x);
  FLOAT nr, ni;
  if (r == 0.0)
    nr = ni = r;
  else if (x.real() > 0)
    {
      nr = sqrt (0.5 * (r + x.real()));
      ni = x.imag() / nr / 2;
    }
  else
    {
      ni = sqrt (0.5 * (r - x.real()));
      if (x.imag() < 0)
	ni = - ni;
      nr = x.imag() / ni / 2;
    }
  return vcl_complex<FLOAT> (nr, ni); 
}

template <class FLOAT>
inline
ostream& operator << (ostream& o, vcl_complex<FLOAT> const& x)
{
  o << x.real(); 
  if (x.imag()) {
    if (x.imag() > 0) 
      o << '+'; 
    o << x.imag() << 'i';
  }
  return o;

}

template <class FLOAT>
inline
istream& operator >> (istream& o, vcl_complex<FLOAT>& x)
{
  FLOAT r, i;
  o >> r >> i;
  x = vcl_complex<FLOAT>(r,i);
  return o;
}

#ifdef __SUNPRO_CC
#ifdef INSTANTIATE_TEMPLATES
#undef inline 
#endif
#endif
// ANSI complex types
#define __STD_COMPLEX
typedef vcl_complex<float> vcl_float_complex;
typedef vcl_complex<double> vcl_double_complex;
typedef vcl_complex<long double> vcl_long_double_complex;

inline vcl_complex<float> operator*(const vcl_complex<float>& c, double d)
{
  float f = (float)d;
  return vcl_complex<float>(c.real() * f, c.imag() * f);
}

#define VCL_COMPLEX_INSTANTIATE \
extern "please include vcl/emulation/vcl_complex.txx instead"

#endif // vcl_emulation_complex_h
