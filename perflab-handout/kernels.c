#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/*
 * Please fill in the following team struct
 */
team_t team = {
    "KEK",                      /* Team name */

    "Kıvanç Tezören",            /* First member full name */
    "e2380939",                  /* First member id */

    "Ece Satılmış",              /* Third member full name (leave blank if none) */
    "e2375681",                          /* Third member id (leave blank if none) */

    "Kutay Özman",               /* Second member full name (leave blank if none) */
    "e2380798",                         /* Second member id (leave blank if none) */
};

/****************
 * EXPOSURE FUSION KERNEL *
 ****************/

/*******************************************************
 * Your different versions of the exposure fusion kernel go here
 *******************************************************/

char kek_fusion_descr[] = "kek_fusion: Code motion + Strength reduction"
    " + Common expr. sharing + Switch";
void kek_fusion(int dim, int *img, int *w, int *dst) {
    // TODO: is this ANSI compliant?
    // TODO: is dim always a multiple of 8 (or another number)?
    int i, j, k;
    int limit10 = dim - 9;  // TODO: use in loop check directly?
    // TODO: multi-layered unrolling?

    long dimdim = dim * dim;
    long dimdim_acc = 0, inter2, idim_acc;
    
    for (k = 0; k < 4; k++){
        // TODO: islem sirasi? bi ihtimal
        // TODO: int olarak de denenir
        idim_acc = 0;
        
        for (i = 0; i < dim; i++) {
            // 10-unroll
            for (j = 0; j < limit10; j += 10) {
                // TODO: Move k loop here & accumulate
                inter2 = dimdim_acc + j;

                dst[idim_acc] += w[inter2] * img[inter2];

                inter2++;
                dst[idim_acc + 1] += w[inter2] * img[inter2];

                inter2++;
                dst[idim_acc + 2] += w[inter2] * img[inter2];

                inter2++;
                dst[idim_acc + 3] += w[inter2] * img[inter2];

                inter2++;
                dst[idim_acc + 4] += w[inter2] * img[inter2];

                inter2++;
                dst[idim_acc + 5] += w[inter2] * img[inter2];

                inter2++;
                dst[idim_acc + 6] += w[inter2] * img[inter2];

                inter2++;
                dst[idim_acc + 7] += w[inter2] * img[inter2];

                inter2++;
                dst[idim_acc + 8] += w[inter2] * img[inter2];

                inter2++;
                dst[idim_acc + 9] += w[inter2] * img[inter2];

                idim_acc += 10;
                inter2 += 10;
            }

            // Finish off the remaining with switch table
            // dim - j (remaining elements) is either 0, 1, 2, ..., 8, or 9 here
            // Note the intentional fall through

            switch (dim - j) {
            case 9:
                inter2 = dimdim_acc + j;
                dst[idim_acc] += w[inter2] * img[inter2];

                j++;
                idim_acc++;
            case 8:
                inter2 = dimdim_acc + j;
                dst[idim_acc] += w[inter2] * img[inter2];

                j++;
                idim_acc++;
            case 7:
                inter2 = dimdim_acc + j;
                dst[idim_acc] += w[inter2] * img[inter2];

                j++;
                idim_acc++;
            case 6:
                inter2 = dimdim_acc + j;
                dst[idim_acc] += w[inter2] * img[inter2];

                j++;
                idim_acc++;
            case 5:
                inter2 = dimdim_acc + j;
                dst[idim_acc] += w[inter2] * img[inter2];

                j++;
                idim_acc++;
            case 4:
                inter2 = dimdim_acc + j;
                dst[idim_acc] += w[inter2] * img[inter2];

                j++;
                idim_acc++;
            case 3:
                inter2 = dimdim_acc + j;
                dst[idim_acc] += w[inter2] * img[inter2];

                j++;
                idim_acc++;
            case 2:
                inter2 = dimdim_acc + j;
                dst[idim_acc] += w[inter2] * img[inter2];

                j++;
                idim_acc++;
            case 1:
                inter2 = dimdim_acc + j;
                dst[idim_acc] += w[inter2] * img[inter2];

                idim_acc++;
            case 0:
                break;
            }

            /*
            // Non-switch:
            for (; j < dim; j++) {
                long inter2 = dimdim_acc + j;
                
                dst[idim_acc] += w[inter2] * img[inter2];
                idim_acc++;
            }
            */
            
            dimdim_acc += dim;
            //idim_acc is already incremented by dim
        }
        
        dimdim_acc += dimdim - idim_acc;
    }
}


char kek_fusion_double_unroll_descr[] = "kek_fusion_double_unroll:"
    " Common subexpr. + i unroll by 2 + j unroll by 4";
void kek_fusion_double_unroll(int dim, int *img, int *w, int *dst)
{
    // TODO: Check instruction order in objdump for parallel optimization
    // TODO: Does long -> int create a significant difference?
    // TODO: Is dim always a multiple of 8 (or another number)?
    register int i, j, k;
    
    long kdimdim, idimj, idim, kdimj, kdimjsec, idimjsec;
    
    for (k = 0; k < 4; k++) {
        kdimdim = k * dim * dim;
        
        for (i = 0; i < dim; i+=2) {
            idim = i*dim;
            
            for (j = 0; j < dim - 3; j += 4) {
                // TODO: May move k loop here
                idimj = idim + j;
                kdimj = kdimdim +idimj;
                idimjsec = idim + dim + j;
                kdimjsec = kdimdim + idimjsec;
                
                dst[idimj] += w[kdimj] * img[kdimj];
                dst[idimj + 1] += w[kdimj + 1] * img[kdimj + 1];
                dst[idimj + 2] += w[kdimj + 2] * img[kdimj + 2];
                dst[idimj + 3] += w[kdimj + 3] * img[kdimj + 3];
                
                dst[idimjsec] += w[kdimjsec] * img[kdimjsec];
                dst[idimjsec + 1] += w[kdimjsec + 1] * img[kdimjsec + 1];
                dst[idimjsec + 2] += w[kdimjsec + 2] * img[kdimjsec + 2];
                dst[idimjsec + 3] += w[kdimjsec + 3] * img[kdimjsec + 3];
            }
        }
        
        // dim is guaranteed to be a multiple of 32 - no need for cleanup loops
    }
}

char kek_fusion_nonaliasing_descr[] = "kek_fusion_nonaliasing:"
    " Same + k loop relocation w/ aliasing removed";
void kek_fusion_nonaliasing(int dim, int *img, int *w, int *dst)
{
    // TODO: Check instruction order in objdump for parallel optimization
    // TODO: Does long -> int create a significant difference?
    // TODO: Is this ANSI compliant?
    // TODO: Is dim always a multiple of 8 (or another number)?
    register int i, j;
    
    // TODO: idim_acc may be unnecessary
    register long idim_acc = 0;  // Accumulates i*dim + j
    register long dimdim = dim * dim;
    
    // Accumulators for unaliasing the k loop
    long k_nonalias_acc1,
        k_nonalias_acc2,
        k_nonalias_acc3,
        k_nonalias_acc4;
        
    // TODO: Multi-layered unrolling? (unrolling i by 2 preferred)
    for (i = 0; i < dim; i++) {
        // 4-unroll
        for (j = 0; j < dim - 3; j += 4) {
            // k from 0 to 3 (inclusive), loop eliminated by completely
            //  unrolling
            // TODO: Can the additions be optimized further?
            
            k_nonalias_acc1 = w[idim_acc] * img[idim_acc]
                + w[dimdim + idim_acc] * img[dimdim + idim_acc]
                + w[(dimdim << 1) + idim_acc] * img[(dimdim << 1) + idim_acc]
                + w[3 * dimdim + idim_acc] * img[3 * dimdim + idim_acc];
            
            k_nonalias_acc2 = w[idim_acc + 1] * img[idim_acc + 1]
                + w[dimdim + idim_acc + 1] * img[dimdim + idim_acc + 1]
                + w[(dimdim << 1) + idim_acc + 1] * img[(dimdim << 1) + idim_acc + 1]
                + w[3 * dimdim + idim_acc + 1] * img[3 * dimdim + idim_acc + 1];
            
            k_nonalias_acc3 = w[idim_acc + 2] * img[idim_acc + 2]
                + w[dimdim + idim_acc + 2] * img[dimdim + idim_acc + 2]
                + w[(dimdim << 1) + idim_acc + 2] * img[(dimdim << 1) + idim_acc + 2]
                + w[3 * dimdim + idim_acc + 2] * img[3 * dimdim + idim_acc + 2];
            
            k_nonalias_acc4 = w[idim_acc + 3] * img[idim_acc + 3]
                + w[dimdim + idim_acc + 3] * img[dimdim + idim_acc + 3]
                + w[(dimdim << 1) + idim_acc + 3] * img[(dimdim << 1) + idim_acc + 3]
                + w[3 * dimdim + idim_acc + 3] * img[3 * dimdim + idim_acc + 3];
            
            dst[idim_acc] += k_nonalias_acc1;
            dst[idim_acc + 1] += k_nonalias_acc2;
            dst[idim_acc + 2] += k_nonalias_acc3;
            dst[idim_acc + 3] += k_nonalias_acc4;
            
            idim_acc += 4;  // Prepare for next dst batch
        }

        // Finish off the remaining with switch table
        // dim - j (remaining elements) is either 0, 1, 2, or 3 here
        // Note the intentional fall through
        // TODO: Can the additions be optimized further?

        switch (dim - j) {
        case 3:
            dst[idim_acc] += w[idim_acc] * img[idim_acc]
                + w[dimdim + idim_acc] * img[dimdim + idim_acc]
                + w[(dimdim << 1) + idim_acc] * img[(dimdim << 1) + idim_acc]
                + w[3 * dimdim + idim_acc] * img[3 * dimdim + idim_acc];

            idim_acc++;
        case 2:
            dst[idim_acc] += w[idim_acc] * img[idim_acc]
                + w[dimdim + idim_acc] * img[dimdim + idim_acc]
                + w[(dimdim << 1) + idim_acc] * img[(dimdim << 1) + idim_acc]
                + w[3 * dimdim + idim_acc] * img[3 * dimdim + idim_acc];

            idim_acc++;
        case 1:
            dst[idim_acc] += w[idim_acc] * img[idim_acc]
                + w[dimdim + idim_acc] * img[dimdim + idim_acc]
                + w[(dimdim << 1) + idim_acc] * img[(dimdim << 1) + idim_acc]
                + w[3 * dimdim + idim_acc] * img[3 * dimdim + idim_acc];

            idim_acc++;
        case 0:
            break;
        }
        
        // idim_acc is already incremented by dim - no need for action
    }
}

/*
 * naive_fusion - The naive baseline version of exposure fusion
 */
char naive_fusion_descr[] = "naive_fusion: Naive baseline exposure fusion";
void naive_fusion(int dim, int *img, int *w, int *dst) {
    int i, j, k;
    for(k = 0; k < 4; k++){
        for(i = 0; i < dim; i++) {
            for(j = 0; j < dim; j++) {
                    dst[i*dim+j] += w[k*dim*dim+i*dim+j] * img[k*dim*dim+i*dim+j];
            }
        }
    }
}

/*
 * fusion - Your current working version of fusion
 * IMPORTANT: This is the version you will be graded on
 */
// TODO: inline'a çevir
char fusion_descr[] = "fusion: Current working version";
void fusion(int dim, int *img, int *w, int *dst)
{
    kek_fusion_double_unroll(dim, img, w, dst);
}

/*********************************************************************
 * register_fusion_functions - Register all of your different versions
 *     of the fusion kernel with the driver by calling the
 *     add_fusion_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_fusion_functions()
{
    add_fusion_function(&naive_fusion, naive_fusion_descr);
    add_fusion_function(&fusion, fusion_descr);
    /* ... Register additional test functions here */
    
    add_fusion_function(&kek_fusion, kek_fusion_descr);
    add_fusion_function(&kek_fusion_nonaliasing, kek_fusion_nonaliasing_descr);
    add_fusion_function(&kek_fusion_double_unroll, kek_fusion_double_unroll_descr);
}

/***************************
 * GAUSSIAN BLUR KERNEL *
 ***************************/

/******************************************************
 * Your different versions of the Gaussian blur functions go here
 ******************************************************/


char kek_blur_kl_elim_descr[] = "kek_blur_kl_elim: k & l loops are eliminated +"
    " unalias in k loop";
void kek_blur_kl_elim(int dim, float *img, float *flt, float *dst)
{
    int i, j;
    long idim, kdim, kdimj, idimj;
    // Separate unaliasing accumulators for SIMD
    float temp_unalias1 = 0.f,
        temp_unalias2 = 0.f,
        temp_unalias3 = 0.f,
        temp_unalias4 = 0.f,
        temp_unalias5 = 0.f;
    
    for(i = 0; i < dim - 4; i++){
        idim = i*dim;
        
        for(j = 0; j < dim - 4; j++) {
            idimj = idim + j;
            
            // k = 0
            kdim = 0;
            kdimj = j;
                
            temp_unalias1 += img[idim + kdimj] * flt[kdim];
            temp_unalias2 += img[idim + kdimj + 1] * flt[kdim + 1];
            temp_unalias3 += img[idim + kdimj + 2] * flt[kdim + 2];
            temp_unalias4 += img[idim + kdimj + 3] * flt[kdim + 3];
            temp_unalias5 += img[idim + kdimj + 4] * flt[kdim + 4];

            // k = 1
            kdim += dim;
            kdimj = kdim + j;
            
            temp_unalias1 += img[idim + kdimj] * flt[kdim];
            temp_unalias2 += img[idim + kdimj + 1] * flt[kdim + 1];
            temp_unalias3 += img[idim + kdimj + 2] * flt[kdim + 2];
            temp_unalias4 += img[idim + kdimj + 3] * flt[kdim + 3];
            temp_unalias5 += img[idim + kdimj + 4] * flt[kdim + 4];
            
            // k = 2
            kdim += dim;
            kdimj = kdim + j;
            
            temp_unalias1 += img[idim + kdimj] * flt[kdim];
            temp_unalias2 += img[idim + kdimj + 1] * flt[kdim + 1];
            temp_unalias3 += img[idim + kdimj + 2] * flt[kdim + 2];
            temp_unalias4 += img[idim + kdimj + 3] * flt[kdim + 3];
            temp_unalias5 += img[idim + kdimj + 4] * flt[kdim + 4];
            
            // k = 3
            kdim += dim;
            kdimj = kdim + j;
            
            temp_unalias1 += img[idim + kdimj] * flt[kdim];
            temp_unalias2 += img[idim + kdimj + 1] * flt[kdim + 1];
            temp_unalias3 += img[idim + kdimj + 2] * flt[kdim + 2];
            temp_unalias4 += img[idim + kdimj + 3] * flt[kdim + 3];
            temp_unalias5 += img[idim + kdimj + 4] * flt[kdim + 4];
            
            // k = 4
            kdim += dim;
            kdimj = kdim + j;
            
            temp_unalias1 += img[idim + kdimj] * flt[kdim];
            temp_unalias2 += img[idim + kdimj + 1] * flt[kdim + 1];
            temp_unalias3 += img[idim + kdimj + 2] * flt[kdim + 2];
            temp_unalias4 += img[idim + kdimj + 3] * flt[kdim + 3];
            temp_unalias5 += img[idim + kdimj + 4] * flt[kdim + 4];
            
            dst[idimj] += temp_unalias1 + temp_unalias2 + temp_unalias3
                + temp_unalias4 + temp_unalias5;
                
            temp_unalias1 = temp_unalias2 = temp_unalias3 = temp_unalias4
                = temp_unalias5 = 0;
        }
    }
}


char kek_blur_ju4_descr[] = "kek_blur: only l loop is eliminated + unalias in k"
    " loop + unroll j by 4";
void kek_blur_ju4(int dim, float *img, float *flt, float *dst) {
    int i, j, k;
    long idim, kdim, kdimj, idimj;
    // Separate unaliasing accumulators for parallel execution
    float temp_unalias1 = 0.f,
        temp_unalias2 = 0.f,
        temp_unalias3 = 0.f,
        temp_unalias4 = 0.f,
        temp_unalias5 = 0.f;
    
    for (i = 0; i < dim - 4; i++) {
        idim = i*dim;
        
        // 4-unroll
        for(j = 0; j < dim - 7; j += 4) {  // Limit is: (dim - 4) - 3
            idimj = idim + j;
            
            // j <- j + 0
            for(k = 0; k < 5; k++){
                kdim = k*dim;
                kdimj = kdim + j;
                
                temp_unalias1 += img[idim + kdimj] * flt[kdim];
                temp_unalias2 += img[idim + kdimj + 1] * flt[kdim + 1];
                temp_unalias3 += img[idim + kdimj + 2] * flt[kdim + 2];
                temp_unalias4 += img[idim + kdimj + 3] * flt[kdim + 3];
                temp_unalias5 += img[idim + kdimj + 4] * flt[kdim + 4];
            }
            
            dst[idimj] += temp_unalias1 + temp_unalias2 + temp_unalias3
                + temp_unalias4 + temp_unalias5;
            
            temp_unalias1 = temp_unalias2 = temp_unalias3 = temp_unalias4
                = temp_unalias5 = 0;
            
            // j <- j + 1
            for(k = 0; k < 5; k++){
                kdim = k*dim;
                kdimj = kdim + j + 1;
                
                temp_unalias1 += img[idim + kdimj] * flt[kdim];
                temp_unalias2 += img[idim + kdimj + 1] * flt[kdim + 1];
                temp_unalias3 += img[idim + kdimj + 2] * flt[kdim + 2];
                temp_unalias4 += img[idim + kdimj + 3] * flt[kdim + 3];
                temp_unalias5 += img[idim + kdimj + 4] * flt[kdim + 4];
            }
            
            dst[idimj + 1] += temp_unalias1 + temp_unalias2 + temp_unalias3
                + temp_unalias4 + temp_unalias5;
            
            temp_unalias1 = temp_unalias2 = temp_unalias3 = temp_unalias4
                = temp_unalias5 = 0;
            
            // j <- j + 2
            for(k = 0; k < 5; k++){
                kdim = k*dim;
                kdimj = kdim + j + 2;
                
                temp_unalias1 += img[idim + kdimj] * flt[kdim];
                temp_unalias2 += img[idim + kdimj + 1] * flt[kdim + 1];
                temp_unalias3 += img[idim + kdimj + 2] * flt[kdim + 2];
                temp_unalias4 += img[idim + kdimj + 3] * flt[kdim + 3];
                temp_unalias5 += img[idim + kdimj + 4] * flt[kdim + 4];
            }
            
            dst[idimj + 2] += temp_unalias1 + temp_unalias2 + temp_unalias3
                + temp_unalias4 + temp_unalias5;
            
            temp_unalias1 = temp_unalias2 = temp_unalias3 = temp_unalias4
                = temp_unalias5 = 0;
            
            // j <- j + 3
            for(k = 0; k < 5; k++){
                kdim = k*dim;
                kdimj = kdim + j + 3;
                
                temp_unalias1 += img[idim + kdimj] * flt[kdim];
                temp_unalias2 += img[idim + kdimj + 1] * flt[kdim + 1];
                temp_unalias3 += img[idim + kdimj + 2] * flt[kdim + 2];
                temp_unalias4 += img[idim + kdimj + 3] * flt[kdim + 3];
                temp_unalias5 += img[idim + kdimj + 4] * flt[kdim + 4];
            }
            
            dst[idimj + 3] += temp_unalias1 + temp_unalias2 + temp_unalias3
                + temp_unalias4 + temp_unalias5;
            
            temp_unalias1 = temp_unalias2 = temp_unalias3 = temp_unalias4
                = temp_unalias5 = 0;
        }
        
        // dim is guaranteed to be a multiple of 32 - no need for a cleanup loop
    }
}


char kek_blur_descr[] = "kek_blur: eliminated k, l loops + unalias in k loop"
    " + localized flt";
void kek_blur(int dim, float *img, float *flt, float *dst) {
    int i, j;
    long idim, idimj;
    // Separate unaliasing accumulators for parallel execution
    float temp_unalias1 = 0.f,
        temp_unalias2 = 0.f,
        temp_unalias3 = 0.f,
        temp_unalias4 = 0.f,
        temp_unalias5 = 0.f;
    
    // Contiguous version of flt to use cache and spatial locality
    float flt_spatloc[25];
    
    // Initialize flt_spatloc
    // TODO: can the assignments be done more efficiently?
    // TODO: increment dim in a variable instead of multiplication?
    flt_spatloc[0] = flt[0];
    flt_spatloc[1] = flt[1];
    flt_spatloc[2] = flt[2];
    flt_spatloc[3] = flt[3];
    flt_spatloc[4] = flt[4];
    
    flt_spatloc[5] = flt[dim];
    flt_spatloc[6] = flt[dim + 1];
    flt_spatloc[7] = flt[dim + 2];
    flt_spatloc[8] = flt[dim + 3];
    flt_spatloc[9] = flt[dim + 4];
    
    flt_spatloc[10] = flt[2*dim];
    flt_spatloc[11] = flt[2*dim + 1];
    flt_spatloc[12] = flt[2*dim + 2];
    flt_spatloc[13] = flt[2*dim + 3];
    flt_spatloc[14] = flt[2*dim + 4];
    
    flt_spatloc[15] = flt[3*dim];
    flt_spatloc[16] = flt[3*dim + 1];
    flt_spatloc[17] = flt[3*dim + 2];
    flt_spatloc[18] = flt[3*dim + 3];
    flt_spatloc[19] = flt[3*dim + 4];
    
    flt_spatloc[20] = flt[4*dim];
    flt_spatloc[21] = flt[4*dim + 1];
    flt_spatloc[22] = flt[4*dim + 2];
    flt_spatloc[23] = flt[4*dim + 3];
    flt_spatloc[24] = flt[4*dim + 4];
    
    for (i = 0; i < dim - 4; i++) {
        idim = i*dim;
        
        for (j = 0; j < dim - 4; j++) {
            idimj = idim + j;
            
            // Eliminated k loop
            // TODO: increment dim in a variable instead of multiplication?
            
            // k = 0
            temp_unalias1 += img[idim + j] * flt_spatloc[0];
            temp_unalias2 += img[idim + j + 1] * flt_spatloc[1];
            temp_unalias3 += img[idim + j + 2] * flt_spatloc[2];
            temp_unalias4 += img[idim + j + 3] * flt_spatloc[3];
            temp_unalias5 += img[idim + j + 4] * flt_spatloc[4];
            
            // k = 1
            temp_unalias1 += img[idim + dim + j] * flt_spatloc[5];
            temp_unalias2 += img[idim + dim + j + 1] * flt_spatloc[6];
            temp_unalias3 += img[idim + dim + j + 2] * flt_spatloc[7];
            temp_unalias4 += img[idim + dim + j + 3] * flt_spatloc[8];
            temp_unalias5 += img[idim + dim + j + 4] * flt_spatloc[9];
            
            // k = 2
            temp_unalias1 += img[idim + 2 * dim + j] * flt_spatloc[10];
            temp_unalias2 += img[idim + 2 * dim + j + 1] * flt_spatloc[11];
            temp_unalias3 += img[idim + 2 * dim + j + 2] * flt_spatloc[12];
            temp_unalias4 += img[idim + 2 * dim + j + 3] * flt_spatloc[13];
            temp_unalias5 += img[idim + 2 * dim + j + 4] * flt_spatloc[14];
            
            // k = 3
            temp_unalias1 += img[idim + 3 * dim + j] * flt_spatloc[15];
            temp_unalias2 += img[idim + 3 * dim + j + 1] * flt_spatloc[16];
            temp_unalias3 += img[idim + 3 * dim + j + 2] * flt_spatloc[17];
            temp_unalias4 += img[idim + 3 * dim + j + 3] * flt_spatloc[18];
            temp_unalias5 += img[idim + 3 * dim + j + 4] * flt_spatloc[19];
            
            // k = 4
            temp_unalias1 += img[idim + 4 * dim + j] * flt_spatloc[20];
            temp_unalias2 += img[idim + 4 * dim + j + 1] * flt_spatloc[21];
            temp_unalias3 += img[idim + 4 * dim + j + 2] * flt_spatloc[22];
            temp_unalias4 += img[idim + 4 * dim + j + 3] * flt_spatloc[23];
            temp_unalias5 += img[idim + 4 * dim + j + 4] * flt_spatloc[24];
            
            /*
            for (k = 0; k < 5; k++) {
                kdim = k*dim;
                kdimj = kdim + j;
                
                temp_unalias1 += img[idim + kdimj] * flt[kdim];
                temp_unalias2 += img[idim + kdimj + 1] * flt[kdim + 1];
                temp_unalias3 += img[idim + kdimj + 2] * flt[kdim + 2];
                temp_unalias4 += img[idim + kdimj + 3] * flt[kdim + 3];
                temp_unalias5 += img[idim + kdimj + 4] * flt[kdim + 4];
            }
            */
            
            dst[idimj] += temp_unalias1 + temp_unalias2 + temp_unalias3
                + temp_unalias4 + temp_unalias5;
                
            temp_unalias1 = temp_unalias2 = temp_unalias3 = temp_unalias4
                = temp_unalias5 = 0;
        }
    }
}


/*
 * naive_blur - The naive baseline version of Gaussian blur
 */
char naive_blur_descr[] = "naive_blur The naive baseline version of Gaussian blur";
void naive_blur(int dim, float *img, float *flt, float *dst) {

    int i, j, k, l;

    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
            for(k = 0; k < 5; k++){
                for(l = 0; l < 5; l++) {
                    dst[i*dim+j] = dst[i*dim+j] + img[(i+k)*dim+j+l] * flt[k*dim+l];
                }
            }
        }
    }
}

/*
 * blur - Your current working version of Gaussian blur
 * IMPORTANT: This is the version you will be graded on
 */
char blur_descr[] = "blur: Current working version";
void blur(int dim, float *img, float *flt, float *dst)
{
    kek_blur(dim, img, flt, dst);
}

/*********************************************************************
 * register_blur_functions - Register all of your different versions
 *     of the gaussian blur kernel with the driver by calling the
 *     add_blur_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_blur_functions()
{
    add_blur_function(&naive_blur, naive_blur_descr);
    add_blur_function(&blur, blur_descr);
    /* ... Register additional test functions here */
    
    add_blur_function(&kek_blur_kl_elim, kek_blur_kl_elim_descr);
    add_blur_function(&kek_blur_ju4, kek_blur_ju4_descr);
    add_blur_function(&kek_blur, kek_blur_descr);
}
