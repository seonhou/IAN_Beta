#ifndef __GPU_BLAS_INTERFACE_H__
#define __GPU_BLAS_INTERFACE_H__

#include "BLAS_Interface.h"

#ifdef _USE_GPU

class GPU_Control {
private:
  static bool _initialized;

public:
  template <typename data_type>
  static bool big_enough(blas_int m,blas_int n,blas_int k) { 
    blas_int bs=16*sizeof(data_type);
    if(_initialized && m>=bs && n>=bs && k>=bs && (m>=4*bs || n>=4*bs || k>=4*bs)) return true;
    return false; 
  }

  static bool initialized(void) { return _initialized; }

  static void init_device(void) { _initialized=true; }
};

struct GPU_BLAS_Interface : public BLAS_Interface {

// Interface for BLAS subroutines

  //template <typename data_type>
  //static data_type DOT(blas_int n,const data_type* x,blas_int incx,
  //                     const data_type* y,blas_int incy);

  //template <typename data_type>
  //static void SCAL(blas_int n,data_type alpha,data_type* x,blas_int incx);

  //template <typename data_type>
  //static void AXPY(blas_int n,data_type alpha,const data_type* x,
  //                 blas_int incx,data_type* y,blas_int incy);

  //template <typename data_type>
  //static void GEMV(blas_str trans,blas_int m,blas_int n,
  //                 data_type alpha,const data_type* A,blas_int ldA,
  //                 const data_type* x,blas_int incx,data_type beta,
  //                 data_type* y,blas_int incy);

  template <typename data_type>
  static void GEMM(blas_str transA,blas_str transB,
                   blas_int m,blas_int n,blas_int k,
                   data_type alpha,const data_type* A,blas_int ldA,
                   const data_type* B,blas_int ldB,
                   data_type beta,data_type* C,blas_int ldC);

  template <typename data_type>
  static void TRSM(blas_str lr,blas_str uplo,
                   blas_str trans,blas_str diag,
                   blas_int m,blas_int n,data_type alpha,
                   const data_type* A,blas_int ldA,
                   data_type* B,blas_int ldB);


// Interface for LAPACK subroutines

  template <typename data_type>
  static blas_int POTRF(blas_str uplo,blas_int n,data_type* A,blas_int ldA);

  template <typename data_type>
  static blas_int GETRF(blas_int m,blas_int n,data_type* A,blas_int ldA,blas_int* ipiv);

};

#include "magma.h"

// implementation to call double presicion BLAS

#define _GPU_BLAS_(SUB)   magmablas_s ## SUB
#define _GPU_LAPACK_(SUB) magma_s ## SUB
#define BLAS_data_type blas_real4
#include "GPU_BLAS_Impl.h"
#undef _GPU_BLAS_
#undef _GPU_LAPACK_
#undef BLAS_data_type

#define _GPU_BLAS_(SUB)   magmablas_d ## SUB
#define _GPU_LAPACK_(SUB) magma_d ## SUB
#define BLAS_data_type blas_real8
#include "GPU_BLAS_Impl.h"
#undef _GPU_BLAS_
#undef _GPU_LAPACK_
#undef BLAS_data_type


typedef BLAS_Tmpl<GPU_BLAS_Interface> GPU_BLAS;

#else

typedef BLAS_Tmpl<BLAS_Interface> GPU_BLAS;

#endif

#endif