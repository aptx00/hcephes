#include "mconf.h"
#include "ncephes/ncephes.h"

/* Factorials of integers from 0 through 33 */
static double factbl[] = {
    1.00000000000000000000E0,          1.00000000000000000000E0,
    2.00000000000000000000E0,          6.00000000000000000000E0,
    2.40000000000000000000E1,          1.20000000000000000000E2,
    7.20000000000000000000E2,          5.04000000000000000000E3,
    4.03200000000000000000E4,          3.62880000000000000000E5,
    3.62880000000000000000E6,          3.99168000000000000000E7,
    4.79001600000000000000E8,          6.22702080000000000000E9,
    8.71782912000000000000E10,         1.30767436800000000000E12,
    2.09227898880000000000E13,         3.55687428096000000000E14,
    6.40237370572800000000E15,         1.21645100408832000000E17,
    2.43290200817664000000E18,         5.10909421717094400000E19,
    1.12400072777760768000E21,         2.58520167388849766400E22,
    6.20448401733239439360E23,         1.55112100433309859840E25,
    4.03291461126605635584E26,         1.0888869450418352160768E28,
    3.04888344611713860501504E29,      8.841761993739701954543616E30,
    2.6525285981219105863630848E32,    8.22283865417792281772556288E33,
    2.6313083693369353016721801216E35, 8.68331761881188649551819440128E36};
#define MAXFAC 33

double ncephes_fac(int i) {
    double x, f, n;
    int j;

    if (i < 0) {
        ncephes_mtherr("fac", NCEPHES_SING);
        return (HUGE_VAL);
    }

    if (i > MAXFAC) {
        ncephes_mtherr("fac", NCEPHES_OVERFLOW);
        return (HUGE_VAL);
    }

    /* Get answer from table for small i. */
    if (i < 34) {
#ifdef NCEPHES_UNK
        return (factbl[i]);
#else
        return (*(double *)(&factbl[4 * i]));
#endif
    }
    /* Use ncephes_gamma function for large i. */
    if (i > 55) {
        x = i + 1;
        return (ncephes_gamma(x));
    }
    /* Compute directly for intermediate i. */
    n = 34.0;
    f = 34.0;
    for (j = 35; j <= i; j++) {
        n += 1.0;
        f *= n;
    }
#ifdef NCEPHES_UNK
    f *= factbl[33];
#else
    f *= *(double *)(&factbl[4 * 33]);
#endif
    return (f);
}
