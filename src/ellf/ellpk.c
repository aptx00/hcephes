#include "hcephes.h"

static double P[] = {1.37982864606273237150E-4, 2.28025724005875567385E-3,
                     7.97404013220415179367E-3, 9.85821379021226008714E-3,
                     6.87489687449949877925E-3, 6.18901033637687613229E-3,
                     8.79078273952743772254E-3, 1.49380448916805252718E-2,
                     3.08851465246711995998E-2, 9.65735902811690126535E-2,
                     1.38629436111989062502E0};

static double Q[] = {2.94078955048598507511E-5, 9.14184723865917226571E-4,
                     5.94058303753167793257E-3, 1.54850516649762399335E-2,
                     2.39089602715924892727E-2, 3.01204715227604046988E-2,
                     3.73774314173823228969E-2, 4.88280347570998239232E-2,
                     7.03124996963957469739E-2, 1.24999999999870820058E-1,
                     4.99999999999999999821E-1};
static double C1 = 1.3862943611198906188E0; /* log(4) */

double hcephes_ellpk(double x) {
    // line added by danilo
    x = 1 - x;
    if ((x < 0.0) || (x > 1.0)) {
        hcephes_mtherr("ellpk", HCEPHES_DOMAIN);
        return (0.0);
    }

    if (x > HCEPHES_MACHEP) {
        return (hcephes_polevl(x, P, 10) - log(x) * hcephes_polevl(x, Q, 10));
    } else {
        if (x == 0.0) {
            hcephes_mtherr("ellpk", HCEPHES_SING);
            return (HUGE_VAL);
        } else {
            return (C1 - 0.5 * log(x));
        }
    }
}
