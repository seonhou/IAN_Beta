#ifndef __BLAS_INTERFACE_H__
#define __BLAS_INTERFACE_H__

typedef int    blas_int;
typedef float  blas_real4;
typedef double blas_real8;
typedef const char*  blas_str;

class BLAS_Interface {
private:
  static int_type _num_t;

public:
  static void     set_num_threads(int_type nt);
  static int_type get_num_threads(void);

// Interface for BLAS subroutines

  template <typename data_type>
  static data_type DOT(blas_int n,const data_type* x,blas_int incx,
                       const data_type* y,blas_int incy);

  template <typename data_type>
  static void SCAL(blas_int n,data_type alpha,data_type* x,blas_int incx);

  template <typename data_type>
  static void AXPY(blas_int n,data_type alpha,const data_type* x,
                   blas_int incx,data_type* y,blas_int incy);

  template <typename data_type>
  static void GEMV(blas_str trans,blas_int m,blas_int n,
                   data_type alpha,const data_type* A,blas_int ldA,
                   const data_type* x,blas_int incx,data_type beta,
                   data_type* y,blas_int incy);

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
  static blas_int POTRS(blas_str uplo,blas_int n,blas_int nrhs,data_type* A,
                        blas_int ldA,data_type* rhs,blas_int ldrhs);

  template <typename data_type>
  static blas_int SYTRF(blas_str uplo,blas_int n,data_type* A,blas_int ldA,blas_int* ipiv);

  template <typename data_type>
  static blas_int SYTRS(blas_str uplo,blas_int n,blas_int nrhs,data_type* A,blas_int ldA,
                        blas_int* ipiv, data_type* rhs,blas_int ldrhs);

  template <typename data_type>
  static blas_int GETRF(blas_int m,blas_int n,data_type* A,blas_int ldA,blas_int* ipiv);

  template <typename data_type>
  static blas_int GETRS(blas_str trans,blas_int n,blas_int nrhs,data_type* A,blas_int ldA,
                        blas_int* ipiv, data_type* rhs,blas_int ldrhs);

  template <typename data_type>
  static blas_int GETRI(blas_int n,data_type* A,blas_int ldA,blas_int* ipiv,data_type* work,blas_int lwork);

  template <typename data_type>
  static blas_int SYEV(blas_str jobs,blas_str uplo,blas_int n,data_type* A,blas_int ldA,
                       data_type* w,data_type* work,blas_int lwork);
};


////////////////////////////////////////////////////////////////////////////////////////////
// use MKL implementation of BLAS/LAPACK

#include "mkl.h"
#include <omp.h>

inline void     BLAS_Interface::set_num_threads(int_type nt) 
{ 
  _num_t=nt; 
  MKL_Set_Num_Threads(nt); 
  omp_set_num_threads(nt);
}

inline int_type BLAS_Interface::get_num_threads(void) 
{ 
  return _num_t;
}

// implementation to call single presicion BLAS
#define _BLAS_(SUB)   S ## SUB
#define BLAS_data_type blas_real4
#include "BLAS_Impl.h"
#undef _BLAS_
#undef BLAS_data_type

// implementation to call double presicion BLAS
#define _BLAS_(SUB) D ## SUB
//#define USER_LAPACK
#define BLAS_data_type blas_real8
#include "BLAS_Impl.h"
#undef _BLAS_
#undef BLAS_data_type
////////////////////////////////////////////////////////////////////////////////////////////


template <typename BLAS_Type>
struct BLAS_Tmpl {

//! BLAS_GEMV : y := alpha*A*x + beta*y
template <typename MatrixType,typename VectorType1,typename VectorType2>
inline static VectorType2& MxV(typename VectorType1::T_numtype alpha,const MatrixType& A,const VectorType1& x,
                        typename VectorType1::T_numtype beta,VectorType2& y)
{
  using namespace BLAS_ArrayInfo;
  BLAS_Type::GEMV("N",get_rows(A),get_columns(A),alpha,A.data(),get_ld(A),x.data(),get_stride(x),beta,y.data(),get_stride(y));
  return y;
}

//! BLAS_GEMV : y := A*x
template <typename MatrixType,typename VectorType1,typename VectorType2>
inline static VectorType2& MxV(const MatrixType& A,const VectorType1& x,VectorType2& y)
{
  typedef VectorType1::T_numtype data_type;
  data_type alpha=data_type(1.0);
  data_type beta=data_type(0.0);
  MxV(alpha,A,x,beta,y);
  return y;
}

//! BLAS_GEMV : y := alpha*A'*x + beta*y
template <typename MatrixType,typename VectorType1,typename VectorType2>
inline static VectorType2& MtxV(typename VectorType1::T_numtype alpha,const MatrixType& A,const VectorType1& x,
                         typename VectorType1::T_numtype beta,VectorType2& y)
{
  using namespace BLAS_ArrayInfo;
  BLAS_Type::GEMV("T",get_rows(A),get_columns(A),alpha,A.data(),get_ld(A),x.data(),get_stride(x),beta,y.data(),get_stride(y));
  return y;
}

//! BLAS_GEMV : y := A'*x
template <typename MatrixType,typename VectorType1,typename VectorType2>
inline static VectorType2& MtxV(const MatrixType& A,const VectorType1& x,VectorType2& y)
{
  typedef VectorType1::T_numtype data_type;
  data_type alpha=data_type(1.0);
  data_type beta=data_type(0.0);
  MtxV(alpha,A,x,beta,y);
  return y;
}

//! BLAS_GEMM : C := alpha*A*B + beta*C
template <typename MatrixType1,typename MatrixType2,typename MatrixType3>
inline static MatrixType3& MxM(typename MatrixType1::T_numtype alpha,const MatrixType1& A,const MatrixType2& B,
                        typename MatrixType1::T_numtype beta,MatrixType3& C)
{
  using namespace BLAS_ArrayInfo;
  BLAS_Type::GEMM("N","N",get_rows(C),get_columns(C),get_columns(A),alpha,A.data(),get_ld(A),
                        B.data(),get_ld(B),beta,C.data(),get_ld(C));
  return C;
}

//! BLAS_GEMM : C := A*B
template <typename MatrixType1,typename MatrixType2,typename MatrixType3>
inline static MatrixType3&  MxM(const MatrixType1& A,const MatrixType2& B,MatrixType3& C)
{
  typedef MatrixType1::T_numtype data_type;
  data_type alpha=data_type(1.0);
  data_type beta=data_type(0.0);
  MxM(alpha,A,B,beta,C);
  return C;
}

//! BLAS_GEMM : C := alpha*A'*B + beta*C
template <typename MatrixType1,typename MatrixType2,typename MatrixType3>
inline static MatrixType3&  MtxM(typename MatrixType1::T_numtype alpha,const MatrixType1& A,const MatrixType2& B,
                          typename MatrixType1::T_numtype beta,MatrixType3& C)
{
  using namespace BLAS_ArrayInfo;
  BLAS_Type::GEMM("T","N",get_rows(C),get_columns(C),get_rows(A),alpha,A.data(),get_ld(A),
                        B.data(),get_ld(B),beta,C.data(),get_ld(C));
  return C;
}

//! BLAS_GEMM : C := A'*B
template <typename MatrixType1,typename MatrixType2,typename MatrixType3>
inline static MatrixType3& MtxM(const MatrixType1& A,const MatrixType2& B,MatrixType3& C)
{
  typedef MatrixType1::T_numtype data_type;
  data_type alpha=data_type(1.0);
  data_type beta=data_type(0.0);
  MtxM(alpha,A,B,beta,C);
  return C;
}

//! BLAS_GEMM : C := alpha*A*B' + beta*C
template <typename MatrixType1,typename MatrixType2,typename MatrixType3>
inline static MatrixType3& MxMt(typename MatrixType1::T_numtype alpha,const MatrixType1& A,const MatrixType2& B,
                         typename MatrixType1::T_numtype beta,MatrixType3& C)
{
  using namespace BLAS_ArrayInfo;
  BLAS_Type::GEMM("N","T",get_rows(C),get_columns(C),get_columns(A),alpha,A.data(),get_ld(A),
                        B.data(),get_ld(B),beta,C.data(),get_ld(C));
  return C;
}

//! BLAS_GEMM : C := A*B'
template <typename MatrixType1,typename MatrixType2,typename MatrixType3>
inline static MatrixType3& MxMt(const MatrixType1& A,const MatrixType2& B,MatrixType3& C)
{
  typedef MatrixType1::T_numtype data_type;
  data_type alpha=data_type(1.0);
  data_type beta=data_type(0.0);
  MxMt(alpha,A,B,beta,C);
  return C;
}

//! BLAS_GEMM : C := alpha*A'*B' + beta*C
template <typename MatrixType1,typename MatrixType2,typename MatrixType3>
inline static MatrixType3& MtxMt(typename MatrixType1::T_numtype alpha,const MatrixType1& A,const MatrixType2& B,
                          typename MatrixType1::T_numtype beta,MatrixType3& C)
{
  using namespace BLAS_ArrayInfo;
  BLAS_Type::GEMM("T","T",get_rows(C),get_columns(C),get_rows(A),alpha,A.data(),get_ld(A),
                        B.data(),get_ld(B),beta,C.data(),get_ld(C));
  return C;
}

//! BLAS_GEMM : C := A'*B'
template <typename MatrixType1,typename MatrixType2,typename MatrixType3>
inline static MatrixType3& MtxMt(const MatrixType1& A,const MatrixType2& B,MatrixType3& C)
{
  typedef MatrixType1::T_numtype data_type;
  data_type alpha=data_type(1.0);
  data_type beta=data_type(0.0);
  MtxMt(alpha,A,B,beta,C);
  return C;
}

//! LAPACK_POTRF : A = L * L^T
template <typename MatrixType>
inline static void LLT_factorize(MatrixType& A) 
{
  using namespace BLAS_ArrayInfo;
  blas_int info;
  if( (info=BLAS_Type::POTRF("L",get_rows(A),A.data(),get_ld(A))) ) throw info;
}

//! LAPACK_POTRS : solve ( L * L^T ) * x = b
template <typename MatrixType1,typename MatrixType2>
inline static void LLT_substitute(MatrixType1& A,MatrixType2& rhs) 
{
  using namespace BLAS_ArrayInfo;
  blas_int info;
  if( (info=BLAS_Type::POTRS("L",get_rows(A),get_columns(rhs),A.data(),get_ld(A),rhs.data(),get_ld(rhs))) ) throw info;
}

//! solve A * x = b with A = L * L^T
template <typename MatrixType1,typename MatrixType2>
inline static void LLT_solve(MatrixType1& A,MatrixType2& rhs) 
{
  LLT_factorize(A);
  LLT_substitute(A,rhs);
}

//! LAPACK_SYTRF : A = L * D * L^T (P is a permutation matrix stored in ipiv)
template <typename MatrixType,typename VectorType>
inline static void LDLT_factorize(MatrixType& A,VectorType& ipiv) 
{
  using namespace BLAS_ArrayInfo;
  blas_int info;
  blas_int nn=get_rows(A);
  if( (info=BLAS_Type::SYTRF("L",nn,A.data(),get_ld(A),ipiv.data())) ) throw info;
}

//! LAPACK_SYTRS : solve ( L * D * L^T ) * x = P * b (P is a permutation matrix stored in ipiv)
template <typename MatrixType1,typename MatrixType2,typename VectorType>
inline static void LDLT_substitute(MatrixType1& A,MatrixType2& rhs,VectorType& ipiv) 
{
  using namespace BLAS_ArrayInfo;
  blas_int info;
  if( (info=BLAS_Type::SYTRS("L",get_rows(A),get_columns(rhs),A.data(),get_ld(A),
                                  ipiv.data(),rhs.data(),get_ld(rhs))) ) throw info;
}

//! solve A * x = b with A = L * D * L^T (P is a permutation matrix stored in ipiv)
template <typename MatrixType1,typename MatrixType2>
inline static void LDLT_solve(MatrixType1& A,MatrixType2& rhs) 
{
  IntVector ipiv(rhs.rows());
  LDLT_factorize(A,ipiv);
  LDLT_substitute(A,rhs,ipiv);
}

//! LAPACK_GETRF : P * A = L * U (P is a permutation matrix stored in ipiv)
template <typename MatrixType,typename VectorType>
inline static void LU_factorize(MatrixType& A,VectorType& ipiv) 
{
  using namespace BLAS_ArrayInfo;
  blas_int info;
  blas_int nn=get_rows(A);
  if( (info=BLAS_Type::GETRF(nn,nn,A.data(),get_ld(A),ipiv.data())) ) throw info;
}

//! LAPACK_GETRS : solve ( L * U ) * x = P * b (P is a permutation matrix stored in ipiv)
template <typename MatrixType1,typename MatrixType2,typename VectorType>
inline static void LU_substitute(MatrixType1& A,MatrixType2& rhs,VectorType& ipiv) 
{
  using namespace BLAS_ArrayInfo;
  blas_int info;
  if( (info=BLAS_Type::GETRS("N",get_rows(A),get_columns(rhs),A.data(),get_ld(A),
                                  ipiv.data(),rhs.data(),get_ld(rhs))) ) throw info;
}

//! solve A * x = b with P * A = L * U (P is a permutation matrix stored in ipiv)
template <typename MatrixType1,typename MatrixType2>
inline static void LU_solve(MatrixType1& A,MatrixType2& rhs) 
{
  IntVector ipiv(rhs.rows());
  LU_factorize(A,ipiv);
  LU_substitute(A,rhs,ipiv);
}

template <typename MatrixType>
inline static void LU_inverse(MatrixType& A) 
{
  typedef MatrixType::T_numtype data_type;
  const blas_int lwork=64*1024;
  data_type work[lwork];
  if( (info=BLAS_Type::GETRI(nc,A.data(),get_ld(A),ipiv.data(),work,lwork)) ) throw info;
}

template <typename MatrixType>
inline static typename MatrixType::T_numtype inverse2x2(MatrixType& A) 
{
  typedef MatrixType::T_numtype data_type;
  data_type a11,a12,a21,a22,det,idet;
  a11=A(0,0);
  a21=A(1,0);
  a12=A(0,1);
  a22=A(1,1);
  det = a11*a22-a12*a21;
  if(is_zero(det)) throw 1;
  idet = 1./det;
  A(0,0) = a22*idet;
  A(0,1) =-a12*idet;
  A(1,0) =-a21*idet;
  A(1,1) = a11*idet;
  return det;
}

template <typename MatrixType>
inline static typename MatrixType::T_numtype determinant2x2(MatrixType& A) 
{
  typedef MatrixType::T_numtype data_type;
  data_type a11,a12,a21,a22;
  a11=A(0,0);
  a21=A(1,0);
  a12=A(0,1);
  a22=A(1,1);
  return a11*a22-a12*a21;
}

template <typename MatrixType>
inline static typename MatrixType::T_numtype inverse3x3(MatrixType& A) 
{
  typedef MatrixType::T_numtype data_type;
  data_type a11,a12,a13,a21,a22,a23,a31,a32,a33,det,idet;
  a11=A(0,0);
  a21=A(1,0);
  a31=A(2,0);
  a12=A(0,1);
  a22=A(1,1);
  a32=A(2,1);
  a13=A(0,2);
  a23=A(1,2);
  a33=A(2,2);
  det = a11*a22*a33+a21*a32*a13+a31*a12*a23-a11*a32*a23-a31*a22*a13-a21*a12*a33;
  if(is_zero(det)) throw 1;
  idet = 1./det;
  A(0,0) = (a22*a33-a23*a32)*idet;
  A(0,1) = (a13*a32-a12*a33)*idet;
  A(0,2) = (a12*a23-a13*a22)*idet;
  A(1,0) = (a23*a31-a21*a33)*idet;
  A(1,1) = (a11*a33-a13*a31)*idet;
  A(1,2) = (a13*a21-a11*a23)*idet;
  A(2,0) = (a21*a32-a22*a31)*idet;
  A(2,1) = (a12*a31-a11*a32)*idet;
  A(2,2) = (a11*a22-a12*a21)*idet;
  return det;
}

template <typename MatrixType>
inline static typename MatrixType::T_numtype determinant3x3(MatrixType& A) 
{
  typedef MatrixType::T_numtype data_type;
  data_type a11,a12,a13,a21,a22,a23,a31,a32,a33,det;
  a11=A(0,0);
  a21=A(1,0);
  a31=A(2,0);
  a12=A(0,1);
  a22=A(1,1);
  a32=A(2,1);
  a13=A(0,2);
  a23=A(1,2);
  a33=A(2,2);
  det = a11*a22*a33+a21*a32*a13+a31*a12*a23-a11*a32*a23-a31*a22*a13-a21*a12*a33;
  return det;
}

//! solve X * A = B with P * A = L * U (P is a permutation matrix stored in ipiv)
//!  X = B * U^(-1) * L^(-1) * P
template <typename MatrixType1,typename MatrixType2>
inline static void LU_solve_post(MatrixType1& A,MatrixType2& rhs) 
{
  using namespace BLAS_ArrayInfo;
  blas_int nr=rhs.rows(),nc=rhs.columns();
  assert(get_rows(A)==nc);
  IntVector ipiv(nc);

  //blas_int info;
  //if( (info=BLAS_Type::GETRF(nc,nc,A.data(),get_ld(A),ipiv.data())) ) throw info;

  //const blas_int NB=64;
  //blas_int lwork=nr*nc;
  //MatrixType2 work(nr,nc);
  //if( (info=BLAS_Type::GETRI(nc,A.data(),get_ld(A),ipiv.data(),work.data(),lwork)) ) throw info;

  //MxM(rhs,A,work);
  //rhs = work;

  LU_factorize(A,ipiv);

  BLAS_Type::TRSM("R","U","N","N",nr,nc,1.,A.data(),get_ld(A),rhs.data(),get_ld(rhs));
  BLAS_Type::TRSM("R","L","N","U",nr,nc,1.,A.data(),get_ld(A),rhs.data(),get_ld(rhs));

  // column exchange by ipiv
  blas_int i,ii,j;
  for(i=0;i<nc;i++) {
    ii=ipiv[i]-1;
    if(ii!=i)
      for(j=0;j<nr;j++) swap(rhs(j,i),rhs(j,ii));
  }
}

template <typename MatrixType,typename VectorType>
inline static void sym_eigen_solve(MatrixType& A,VectorType& w) 
{
  using namespace BLAS_ArrayInfo;
  typedef MatrixType::T_numtype data_type;
  blas_int info;
  const blas_int lwork=64*1024;
  data_type work[lwork];
  if( (info=BLAS_Type::SYEV("V","L",get_rows(A),A.data(),get_ld(A),w.data(),work,lwork)) ) throw info;
}

template <typename VectorType1,typename VectorType2,typename MatrixType>
inline static MatrixType& VtxV(const VectorType1& A,const VectorType2& B,MatrixType& C)
{
  typedef MatrixType::T_numtype data_type;
  data_type val;
  data_type* pri;
  int_type i,j,nr=A.size();
  int_type nc=B.size();
  for(i=0;i<nc;i++) {
    val=B[i];
    pri=&C(0,i);
    for(j=0;j<nr;j++) pri[j] += A[j]*val;
  }
  return C;
}

};

typedef BLAS_Tmpl<BLAS_Interface> BLAS;

#endif