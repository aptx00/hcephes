#include "ncephes/ncephes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef WIN32
# ifndef NAN
   static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
#  define NAN (*(const float *) __nan)
# endif
#endif

#ifdef _MSC_VER
# if (_MSC_VER <= 1500)
#  define isnan(x) _isnan(x)
# endif
#endif

#define SUCCESS EXIT_SUCCESS
#define FAIL EXIT_FAILURE


// int test_filepath(const byte *filepath, VariantIndexing **index)
// {
//     BGenFile *bgen;
//     Variant *variants;
//     string *samples;
//     inti e;
//
//     bgen = bgen_open(filepath);
//
//     if (bgen == NULL) return FAIL;
//
//     if (bgen_nsamples(bgen) != 500) return FAIL;
//
//     if (bgen_nvariants(bgen) != 199) return FAIL;
//
//     samples = bgen_read_samples(bgen);
//
//     if (samples != NULL)
//     {
//         e = strncmp("sample_001", (char *)samples[0].str, samples[0].len);
//
//         if (e != 0) return FAIL;
//
//         e = strncmp("sample_500", (char *)samples[499].str, samples[0].len);
//
//         if (e != 0) return FAIL;
//     }
//
//     variants = bgen_read_variants(bgen, index);
//
//     e = strncmp("SNPID_2", (char *)variants[0].id.str, variants[0].id.len);
//
//     if (e != 0) return FAIL;
//
//     e = strncmp("SNPID_200", (char *)variants[198].id.str, variants[198].id.len);
//
//     if (e != 0) return FAIL;
//
//     bgen_free_samples(bgen, samples);
//     bgen_free_variants(bgen, variants);
//
//     bgen_close(bgen);
//
//     return EXIT_SUCCESS;
// }
//
// int test_probabilities(VariantIndexing *index, inti nsamples)
// {
//     VariantGenotype *vg;
//     FILE *f;
//     char   line[65536];
//     double prob[3];
//     double eps = 1e-4;
//     int    tmp;
//     inti   ncombs;
//     inti i, j;
//     real  *probabilities;
//
//     f = fopen("test/data/example.matrix", "r");
//
//     if (f == NULL) return FAIL;
//
//     for (i = 0; i < 199; ++i)
//     {
//         vg = bgen_open_variant_genotype(index, i);
//
//         if (bgen_ploidy(vg) != 2)
//         {
//             fprintf(stderr, "Wrong ploidy.\n");
//             return FAIL;
//         }
//
//         ncombs = bgen_ncombs(vg);
//
//         probabilities = calloc(nsamples * ncombs, sizeof(real));
//
//         bgen_read_variant_genotype(index, vg, probabilities);
//
//         for (j = 0; j < 500; ++j)
//         {
//             tmp = fscanf(f, "%lf", prob + 0);
//             tmp = fscanf(f, "%lf", prob + 1);
//             tmp = fscanf(f, "%lf", prob + 2);
//
//             if ((prob[0] == 0) && (prob[1] == 0) && (prob[2] == 0))
//             {
//                 prob[0] = NAN;
//                 prob[1] = NAN;
//                 prob[2] = NAN;
//
//                 if (!isnan(probabilities[j * 3 + 0])) return FAIL;
//
//                 if (!isnan(probabilities[j * 3 + 1])) return FAIL;
//
//                 if (!isnan(probabilities[j * 3 + 2])) return FAIL;
//             } else {
//                 if (fabs(prob[0] - probabilities[j * 3 + 0]) > eps) return FAIL;
//
//
//                 if (fabs(prob[1] - probabilities[j * 3 + 1]) > eps) return
//                         FAIL;
//
//                 if (fabs(prob[2] - probabilities[j * 3 + 2]) > eps) return
//                         FAIL;
//             }
//         }
//         bgen_close_variant_genotype(index, vg);
//         free(probabilities);
//     }
//
//     fclose(f);
//
//     return SUCCESS;
// }

int main()
{
    return SUCCESS;
}
