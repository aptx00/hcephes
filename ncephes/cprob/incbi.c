#include "mconf.h"
#include "ncephes/cprob.h"
#include <math.h>

extern double MACHEP, NCEPHES_MAXNUM, MAXLOG, MINLOG;

double ncephes_incbi(double aa, double bb, double yy0) {
    double a, b, y0, d, y, x, x0, x1, lgm, yp, di, dithresh, yl, yh, xt;
    int i, rflg, dir, nflg;

    i = 0;
    if (yy0 <= 0)
        return (0.0);
    if (yy0 >= 1.0)
        return (1.0);
    x0 = 0.0;
    yl = 0.0;
    x1 = 1.0;
    yh = 1.0;
    nflg = 0;

    if (aa <= 1.0 || bb <= 1.0) {
        dithresh = 1.0e-6;
        rflg = 0;
        a = aa;
        b = bb;
        y0 = yy0;
        x = a / (a + b);
        y = ncephes_incbet(a, b, x);
        goto ihalve;
    } else {
        dithresh = 1.0e-4;
    }
    /* approximation to inverse function */

    yp = -ncephes_ndtri(yy0);

    if (yy0 > 0.5) {
        rflg = 1;
        a = bb;
        b = aa;
        y0 = 1.0 - yy0;
        yp = -yp;
    } else {
        rflg = 0;
        a = aa;
        b = bb;
        y0 = yy0;
    }

    lgm = (yp * yp - 3.0) / 6.0;
    x = 2.0 / (1.0 / (2.0 * a - 1.0) + 1.0 / (2.0 * b - 1.0));
    d = yp * sqrt(x + lgm) / x -
        (1.0 / (2.0 * b - 1.0) - 1.0 / (2.0 * a - 1.0)) *
            (lgm + 5.0 / 6.0 - 2.0 / (3.0 * x));
    d = 2.0 * d;
    if (d < MINLOG) {
        x = 1.0;
        goto under;
    }
    x = a / (a + b * exp(d));
    y = ncephes_incbet(a, b, x);
    yp = (y - y0) / y0;
    if (fabs(yp) < 0.2)
        goto newt;

/* Resort to interval halving if not close enough. */
ihalve:

    dir = 0;
    di = 0.5;
    for (i = 0; i < 100; i++) {
        if (i != 0) {
            x = x0 + di * (x1 - x0);
            if (x == 1.0)
                x = 1.0 - MACHEP;
            if (x == 0.0) {
                di = 0.5;
                x = x0 + di * (x1 - x0);
                if (x == 0.0)
                    goto under;
            }
            y = ncephes_incbet(a, b, x);
            yp = (x1 - x0) / (x1 + x0);
            if (fabs(yp) < dithresh)
                goto newt;
            yp = (y - y0) / y0;
            if (fabs(yp) < dithresh)
                goto newt;
        }
        if (y < y0) {
            x0 = x;
            yl = y;
            if (dir < 0) {
                dir = 0;
                di = 0.5;
            } else if (dir > 3)
                di = 1.0 - (1.0 - di) * (1.0 - di);
            else if (dir > 1)
                di = 0.5 * di + 0.5;
            else
                di = (y0 - y) / (yh - yl);
            dir += 1;
            if (x0 > 0.75) {
                if (rflg == 1) {
                    rflg = 0;
                    a = aa;
                    b = bb;
                    y0 = yy0;
                } else {
                    rflg = 1;
                    a = bb;
                    b = aa;
                    y0 = 1.0 - yy0;
                }
                x = 1.0 - x;
                y = ncephes_incbet(a, b, x);
                x0 = 0.0;
                yl = 0.0;
                x1 = 1.0;
                yh = 1.0;
                goto ihalve;
            }
        } else {
            x1 = x;
            if (rflg == 1 && x1 < MACHEP) {
                x = 0.0;
                goto done;
            }
            yh = y;
            if (dir > 0) {
                dir = 0;
                di = 0.5;
            } else if (dir < -3)
                di = di * di;
            else if (dir < -1)
                di = 0.5 * di;
            else
                di = (y - y0) / (yh - yl);
            dir -= 1;
        }
    }
    mtherr("incbi", PLOSS);
    if (x0 >= 1.0) {
        x = 1.0 - MACHEP;
        goto done;
    }
    if (x <= 0.0) {
    under:
        mtherr("incbi", UNDERFLOW);
        x = 0.0;
        goto done;
    }

newt:

    if (nflg)
        goto done;
    nflg = 1;
    lgm = ncephes_lgam(a + b) - ncephes_lgam(a) - ncephes_lgam(b);

    for (i = 0; i < 8; i++) {
        /* Compute the function at this point. */
        if (i != 0)
            y = ncephes_incbet(a, b, x);
        if (y < yl) {
            x = x0;
            y = yl;
        } else if (y > yh) {
            x = x1;
            y = yh;
        } else if (y < y0) {
            x0 = x;
            yl = y;
        } else {
            x1 = x;
            yh = y;
        }
        if (x == 1.0 || x == 0.0)
            break;
        /* Compute the derivative of the function at this point. */
        d = (a - 1.0) * log(x) + (b - 1.0) * log(1.0 - x) + lgm;
        if (d < MINLOG)
            goto done;
        if (d > MAXLOG)
            break;
        d = exp(d);
        /* Compute the step to the next approximation of x. */
        d = (y - y0) / d;
        xt = x - d;
        if (xt <= x0) {
            y = (x - x0) / (x1 - x0);
            xt = x0 + 0.5 * y * (x - x0);
            if (xt <= 0.0)
                break;
        }
        if (xt >= x1) {
            y = (x1 - x) / (x1 - x0);
            xt = x1 - 0.5 * y * (x1 - x);
            if (xt >= 1.0)
                break;
        }
        x = xt;
        if (fabs(d / x) < 128.0 * MACHEP)
            goto done;
    }
    /* Did not converge.  */
    dithresh = 256.0 * MACHEP;
    goto ihalve;

done:

    if (rflg) {
        if (x <= MACHEP)
            x = 1.0 - MACHEP;
        else
            x = 1.0 - x;
    }
    return (x);
}
