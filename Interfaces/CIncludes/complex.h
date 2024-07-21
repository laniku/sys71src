/************************************************************

Created: Monday, June 27, 1988 12:42:53 PM
	Complex.h
	C Interface to the Macintosh Libraries


	Copyright Apple Computer, Inc. 1985-1991
	All rights reserved.
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <2>	  8/8/91	JL		Update copyright

	To Do:
************************************************************/

#ifndef __COMPLEX__
#define __COMPLEX__

#ifndef __SANE__
#include <SANE.h>
#endif

struct complex;

/*
	NOTE to users of the complex class stream i/o functionality:
	
	In order to use the complex stream functionality prototyped by the two following
	function declarations one must include either <IOStream.h> or <Stream.h> before
	including <Complex.h>.

*/
#ifdef __IOSTREAM__
ostream& operator<<(ostream&, complex);
	istream& operator>>(istream&, complex&);
#endif
	
struct complex {
	extended	re;
	extended	im;
	
#ifdef __cplusplus

		complex() { re =0.0; im =0.0; }
		complex(extended r, extended i =0.0) { re =r; im =i; }

	friend extended real(const complex);
	friend extended imag(const complex);
	friend extended abs(complex);
	friend extended norm(complex);
	friend extended arg(complex);

	friend complex	acos(complex);
	friend complex	acosh(complex);
	friend complex	asin(complex);
	friend complex	asinh(complex);
	friend complex	atan(complex);
	friend complex	atanh(complex);
	friend complex	conj(complex);
	friend complex	cos(complex);
	friend complex	cosh(complex);
	friend complex	exp(complex);
	friend complex	log(complex);
	friend complex	pow(complex, complex);
	friend complex	pow(complex, long);
	friend complex	pow(complex, extended);
	friend complex	pow(extended, complex);
	friend complex	polar(extended, extended);
	friend complex	sin(complex);
	friend complex	sinh(complex);
	friend complex	sqrt(complex);
	friend complex	sqr(complex);
	friend complex	tan(complex);
	friend complex	tanh(complex);
	friend complex	operator +(complex, complex);
	friend complex	operator -(complex, complex);
	friend complex	operator -(complex);
	friend complex	operator *(complex, complex);	
	friend complex	operator *(complex, extended);
	friend complex	operator *(extended, complex);
	friend complex	operator /(complex, complex);
	friend complex	operator /(complex, extended);
	friend complex	operator /(extended, complex);
	friend int		operator ==(complex, complex);
	friend int		operator !=(complex, complex);
	complex  operator +=(complex);
	complex  operator -=(complex);
	complex  operator *=(complex);
	complex  operator *=(extended);
	complex  operator /=(complex);
	complex  operator /=(extended);

#endif
};



#ifndef __cplusplus
typedef struct complex complex;
#else
extern "C" {
#endif
	
complex cadd( complex x, complex y );
complex csub( complex x, complex y );
complex cmul( complex x, complex y );
complex cdiv( complex x, complex y );
complex xdivc( extended x, complex y );
complex csqrt( complex z );
complex csin( complex z );
complex ccos( complex z );
complex csquare( complex z );
complex cexp( complex z );
complex clog( complex z );
complex cepwry( extended x, complex y );
complex cxpwri( complex x, long y );
complex cxpwre( complex x, extended y );
complex cxpwry( complex x, complex y );
complex csinh( complex z );
complex ccosh( complex z );
complex ctanh( complex z );
complex ctan( complex z );
complex casin( complex z );
complex casinh( complex z );
complex cacos( complex z );
complex cacosh( complex z );
complex catan( complex z );
complex catanh( complex z );
complex cconj( complex z );

extended cabs( complex z );
extended carg( complex z );

#ifdef __cplusplus
}	// close the extern "C" declaration

inline extended real(const complex a)	{ return a.re; }
inline extended imag(const complex a)	{ return a.im; }
inline extended abs(complex a)	{ return cabs(a); }
inline extended norm(complex a) { return a.re*a.re+a.im*a.im; }
inline extended arg(complex a)	{ return carg(a); }
inline complex	acos(complex a) { return cacos(a); }
inline complex	acosh(complex a)	{ return cacosh(a); }
inline complex	asin(complex a) { return casin(a); }
inline complex	asinh(complex a)	{ return casinh(a); }
inline complex	atan(complex a) { return catan(a); }
inline complex	atanh(complex a)	{ return catanh(a); }
inline complex	conj(complex a) { return complex(a.re, -a.im); }
inline complex	cos(complex a)	{ return ccos(a); }
inline complex	cosh(complex a) { return ccosh(a); }
inline complex	exp(complex a)	{ return cexp(a); }
inline complex	log(complex a)	{ return clog(a); }
inline complex	pow(complex a, complex b)	{ return cxpwry(a, b); }
inline complex	pow(complex a, long b)	{ return cxpwri(a, b); }
inline complex	pow(complex a, extended b)	{ return cxpwre(a, b); }
inline complex	pow(extended a, complex b) { return cepwry(a, b); }
inline complex	polar(extended r, extended theta)	{ return complex(r*cos(theta), r*sin(theta) ); }
inline complex	sin(complex a)	{ return csin(a); }
inline complex	sinh(complex a) { return csinh(a); }
inline complex	sqrt(complex a) { return csqrt(a); }
inline complex	sqr(complex a)	{ return csquare(a); }
inline complex	tan(complex a)	{ return ctan(a); }
inline complex	tanh(complex a) { return ctanh(a); }
inline complex	operator +(complex a, complex b)	{ return complex(a.re+b.re, a.im+b.im); }
inline complex	operator -(complex a,complex b) { return complex(a.re-b.re, a.im-b.im); }
inline complex	operator -(complex a)	{ return complex(-a.re, -a.im); }
inline complex	operator *(complex a, complex b)	{ return cmul(a, b); }	
inline complex	operator *(complex a, extended b)	{ return complex(a.re*b, a.im*b); }
inline complex	operator *(extended a, complex b)	{ return complex(a*b.re, a*b.im); }
inline complex	operator /(complex a, complex b)	{ return cdiv(a, b); }
inline complex	operator /(complex a, extended b) { return complex(a.re/b, a.im/b); }
inline complex	operator /(extended a, complex b)	{ return xdivc(a, b); }
inline int		operator ==(complex a, complex b)	{ return (a.re==b.re && a.im==b.im); }
inline int		operator !=(complex a, complex b)	{ return (a.re!=b.re || a.im!=b.im); }

inline complex complex::operator +=(complex a)
{
	re += a.re;
	im += a.im;
	return complex(re, im);
}

inline complex complex::operator -=(complex a)
{
	re -= a.re;
	im -= a.im;
	return complex(re, im);
}

inline complex complex::operator *=(complex a)
{
	return *this = cmul(*this, a);
}

inline complex complex::operator *=(extended a)
{
	re *= a;
	im *= a;
	return complex(re, im);
}

inline complex complex::operator /=(complex a)
{
	return *this = cdiv(*this, a);
}

inline complex complex::operator /=(extended a)
{
	re /= a;
	im /= a;
	return complex(re, im);
}

#endif

#endif
