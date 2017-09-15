#include "mconf.h"

extern double ncephes_incbet(double, double, double);
extern double ncephes_incbi(double, double, double);
extern double pow(double, double);
extern double ncephes_log1p(double);
extern double ncephes_expm1(double);

double ncephes_bdtrc(int k, int n, double p) {
  double dk, dn;

  if ((p < 0.0) || (p > 1.0))
    goto domerr;
  if (k < 0)
    return (1.0);

  if (n < k) {
  domerr:
    mtherr("bdtrc", DOMAIN);
    return (0.0);
  }

  if (k == n)
    return (0.0);
  dn = n - k;
  if (k == 0) {
    if (p < .01)
      dk = -ncephes_expm1(dn * ncephes_log1p(-p));
    else
      dk = 1.0 - pow(1.0 - p, dn);
  } else {
    dk = k + 1;
    dk = ncephes_incbet(dk, dn, p);
  }
  return (dk);
}

double ncephes_bdtr(int k, int n, double p) {
  double dk, dn;

  if ((p < 0.0) || (p > 1.0))
    goto domerr;
  if ((k < 0) || (n < k)) {
  domerr:
    mtherr("bdtr", DOMAIN);
    return (0.0);
  }

  if (k == n)
    return (1.0);

  dn = n - k;
  if (k == 0) {
    dk = pow(1.0 - p, dn);
  } else {
    dk = k + 1;
    dk = ncephes_incbet(dn, dk, 1.0 - p);
  }
  return (dk);
}

double ncephes_bdtri(int k, int n, double y) {
  double dk, dn, p;

  if ((y < 0.0) || (y > 1.0))
    goto domerr;
  if ((k < 0) || (n <= k)) {
  domerr:
    mtherr("bdtri", DOMAIN);
    return (0.0);
  }

  dn = n - k;
  if (k == 0) {
    if (y > 0.8)
      p = -ncephes_expm1(ncephes_log1p(y - 1.0) / dn);
    else
      p = 1.0 - pow(y, 1.0 / dn);
  } else {
    dk = k + 1;
    p = ncephes_incbet(dn, dk, 0.5);
    if (p > 0.5)
      p = ncephes_incbi(dk, dn, 1.0 - y);
    else
      p = 1.0 - ncephes_incbi(dn, dk, y);
  }
  return (p);
}
