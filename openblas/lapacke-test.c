/*******************************************************************************
*  Copyright (C) 2009-2015 Intel Corporation. All Rights Reserved.
*  The information and material ("Material") provided below is owned by Intel
*  Corporation or its suppliers or licensors, and title to such Material remains
*  with Intel Corporation or its suppliers or licensors. The Material contains
*  proprietary information of Intel or its suppliers and licensors. The Material
*  is protected by worldwide copyright laws and treaty provisions. No part of
*  the Material may be copied, reproduced, published, uploaded, posted,
*  transmitted, or distributed in any way without Intel's prior express written
*  permission. No license under any patent, copyright or other intellectual
*  property rights in the Material is granted to or conferred upon you, either
*  expressly, by implication, inducement, estoppel or otherwise. Any license
*  under such intellectual property rights must be express and approved by Intel
*  in writing.
*
********************************************************************************
*/
/*
   LAPACKE_dgeev Example.
   ======================

   Program computes the eigenvalues and left and right eigenvectors of a general
   rectangular matrix A:

    -1.01   0.86  -4.60   3.31  -4.81
     3.98   0.53  -7.04   5.29   3.55
     3.30   8.26  -3.89   8.20  -1.51
     4.43   4.96  -7.66  -7.33   6.18
     7.31  -6.43  -6.16   2.47   5.58

   Description.
   ============

   The routine computes for an n-by-n real nonsymmetric matrix A, the
   eigenvalues and, optionally, the left and/or right eigenvectors. The right
   eigenvector v(j) of A satisfies

   A*v(j)= lambda(j)*v(j)

   where lambda(j) is its eigenvalue. The left eigenvector u(j) of A satisfies

   u(j)H*A = lambda(j)*u(j)H

   where u(j)H denotes the conjugate transpose of u(j). The computed
   eigenvectors are normalized to have Euclidean norm equal to 1 and
   largest component real.

   Example Program Results.
   ========================

 LAPACKE_dgeev (row-major, high-level) Example Program Results

 Eigenvalues
 (  2.86, 10.76) (  2.86,-10.76) ( -0.69,  4.70) ( -0.69, -4.70) -10.46

 Left eigenvectors
 (  0.04,  0.29) (  0.04, -0.29) ( -0.13, -0.33) ( -0.13,  0.33)   0.04
 (  0.62,  0.00) (  0.62,  0.00) (  0.69,  0.00) (  0.69,  0.00)   0.56
 ( -0.04, -0.58) ( -0.04,  0.58) ( -0.39, -0.07) ( -0.39,  0.07)  -0.13
 (  0.28,  0.01) (  0.28, -0.01) ( -0.02, -0.19) ( -0.02,  0.19)  -0.80
 ( -0.04,  0.34) ( -0.04, -0.34) ( -0.40,  0.22) ( -0.40, -0.22)   0.18

 Right eigenvectors
 (  0.11,  0.17) (  0.11, -0.17) (  0.73,  0.00) (  0.73,  0.00)   0.46
 (  0.41, -0.26) (  0.41,  0.26) ( -0.03, -0.02) ( -0.03,  0.02)   0.34
 (  0.10, -0.51) (  0.10,  0.51) (  0.19, -0.29) (  0.19,  0.29)   0.31
 (  0.40, -0.09) (  0.40,  0.09) ( -0.08, -0.08) ( -0.08,  0.08)  -0.74
 (  0.54,  0.00) (  0.54,  0.00) ( -0.29, -0.49) ( -0.29,  0.49)   0.16
*/
#include <stdlib.h>
#include <stdio.h>
#include "lapacke.h"

/* Auxiliary routines prototypes */
extern void print_eigenvalues( char* desc, int n, double* wr, double* wi );
extern void print_eigenvectors( char* desc, int n, double* wi, double* v,
      int ldv );

/* Parameters */
#define N 5
#define LDA N
#define LDVL N
#define LDVR N

/* Main program */
int main() {
        /* Locals */
        int n = N, lda = LDA, ldvl = LDVL, ldvr = LDVR, info;
        /* Local arrays */
        double wr[N], wi[N], vl[LDVL*N], vr[LDVR*N];
        double a[LDA*N] = {
           -1.01,  0.86, -4.60,  3.31, -4.81,
            3.98,  0.53, -7.04,  5.29,  3.55,
            3.30,  8.26, -3.89,  8.20, -1.51,
            4.43,  4.96, -7.66, -7.33,  6.18,
            7.31, -6.43, -6.16,  2.47,  5.58
        };
        /* Executable statements */
        printf( "LAPACKE_dgeev (row-major, high-level) Example Program Results\n" );
        /* Solve eigenproblem */
        info = LAPACKE_dgeev( LAPACK_ROW_MAJOR, 'V', 'V', n, a, lda, wr, wi,
                        vl, ldvl, vr, ldvr );
        /* Check for convergence */
        if( info > 0 ) {
                printf( "The algorithm failed to compute eigenvalues.\n" );
                exit( 1 );
        }
        /* Print eigenvalues */
        print_eigenvalues( "Eigenvalues", n, wr, wi );
        /* Print left eigenvectors */
        print_eigenvectors( "Left eigenvectors", n, wi, vl, ldvl );
        /* Print right eigenvectors */
        print_eigenvectors( "Right eigenvectors", n, wi, vr, ldvr );
        exit( 0 );
} /* End of LAPACKE_dgeev Example */

/* Auxiliary routine: printing eigenvalues */
void print_eigenvalues( char* desc, int n, double* wr, double* wi ) {
        int j;
        printf( "\n %s\n", desc );
   for( j = 0; j < n; j++ ) {
      if( wi[j] == (double)0.0 ) {
         printf( " %6.2f", wr[j] );
      } else {
         printf( " (%6.2f,%6.2f)", wr[j], wi[j] );
      }
   }
   printf( "\n" );
}

/* Auxiliary routine: printing eigenvectors */
void print_eigenvectors( char* desc, int n, double* wi, double* v, int ldv ) {
        int i, j;
        printf( "\n %s\n", desc );
   for( i = 0; i < n; i++ ) {
      j = 0;
      while( j < n ) {
         if( wi[j] == (double)0.0 ) {
            printf( " %6.2f", v[i*ldv+j] );
            j++;
         } else {
            printf( " (%6.2f,%6.2f)", v[i*ldv+j], v[i*ldv+(j+1)] );
            printf( " (%6.2f,%6.2f)", v[i*ldv+j], -v[i*ldv+(j+1)] );
            j += 2;
         }
      }
      printf( "\n" );
   }
}
