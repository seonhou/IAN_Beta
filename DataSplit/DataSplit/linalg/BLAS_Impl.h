// this file can be included only from BLAS_interface.
// Never include this file from other files

template <>
inline BLAS_data_type BLAS_Interface::DOT(blas_int n,const BLAS_data_type* x,blas_int incx,
                                                     const BLAS_data_type* y,blas_int incy)
{
  BLAS_data_type res=_BLAS_(DOT)(&n,x,&incx,y,&incy);
  return res;
}

template <>
inline void BLAS_Interface::SCAL(blas_int n,BLAS_data_type alpha,
                                 BLAS_data_type* x,blas_int incx) 
{
  _BLAS_(SCAL)(&n,&alpha,x,&incx);
}

template <>
inline void BLAS_Interface::AXPY(blas_int n,BLAS_data_type alpha,const BLAS_data_type* x,
                                 blas_int incx,BLAS_data_type* y,blas_int incy)
{
  _BLAS_(AXPY)(&n,&alpha,x,&incx,y,&incy);
}

template <>
inline void BLAS_Interface::GEMV(blas_str trans,blas_int m,blas_int n,
                                 BLAS_data_type alpha,const BLAS_data_type* A,blas_int ldA,
                                 const BLAS_data_type* x,blas_int incx,BLAS_data_type beta,
                                       BLAS_data_type* y,blas_int incy)
{
  _BLAS_(GEMV)(trans,&m,&n,&alpha,A,&ldA,x,&incx,&beta,y,&incy);
}

template <>
inline void BLAS_Interface::GEMM(blas_str transA,blas_str transB,
                                 blas_int m,blas_int n,blas_int k,
                                 BLAS_data_type alpha,const BLAS_data_type* A,blas_int ldA,
                                 const BLAS_data_type* B,blas_int ldB,
                                 BLAS_data_type beta,BLAS_data_type* C,blas_int ldC)
{
  _BLAS_(GEMM)(transA,transB,&m,&n,&k,&alpha,A,&ldA,B,&ldB,&beta,C,&ldC);
}

template <>
inline void BLAS_Interface::TRSM(blas_str lr,blas_str uplo,
                                 blas_str trans,blas_str diag,
                                 blas_int m,blas_int n,BLAS_data_type alpha,
                                 const BLAS_data_type* A,blas_int ldA,
                                       BLAS_data_type* B,blas_int ldB)
{  
  _BLAS_(TRSM)(lr,uplo,trans,diag,&m,&n,&alpha,A,&ldA,B,&ldB);
}

template <>
inline blas_int BLAS_Interface::POTRF(blas_str uplo,blas_int n,BLAS_data_type* A,blas_int ldA)
{
  blas_int info;
  _BLAS_(POTRF)(const_cast<char*>(uplo),&n,A,&ldA,&info);
  return info;
}

template <>
inline blas_int BLAS_Interface::POTRS(blas_str uplo,blas_int n,blas_int nrhs,BLAS_data_type* A,
                                  blas_int ldA,BLAS_data_type* rhs,blas_int ldrhs)
{
  blas_int info;
  _BLAS_(POTRS)(const_cast<char*>(uplo),&n,&nrhs,A,&ldA,rhs,&ldrhs,&info);
  return info;
}

template <>
inline blas_int BLAS_Interface::SYTRF(blas_str uplo,blas_int n,BLAS_data_type* A,blas_int ldA,blas_int* ipiv)
{
  const blas_int LWORK=8*1024*1024;
  BLAS_data_type work[LWORK];
  blas_int info,lw=LWORK;
  _BLAS_(SYTRF)(const_cast<char*>(uplo),&n,A,&ldA,ipiv,work,&lw,&info);
  return info;
}

template <>
inline blas_int BLAS_Interface::SYTRS(blas_str uplo,blas_int n,blas_int nrhs,BLAS_data_type* A,blas_int ldA,
                        blas_int* ipiv, BLAS_data_type* rhs,blas_int ldrhs)
{
  blas_int info;
  _BLAS_(SYTRS)(const_cast<char*>(uplo),&n,&nrhs,A,&ldA,ipiv,rhs,&ldrhs,&info);
  return info;
}

#ifdef USER_LAPACK
template <>
inline blas_int BLAS_Interface::GETRF(blas_int m,blas_int n,BLAS_data_type* A,blas_int ldA,blas_int* ipiv)
{
  //int dgeptrf_mt(int,int,double*,int,int*,int,int);
  //return dgeptrf_mt(m,m,A,ldA,ipiv,_num_t,0);
  int dgeptrf_st(int,int,double*,int,int*);
  return dgeptrf_st(m,m,A,ldA,ipiv);
}
#else
template <>
inline blas_int BLAS_Interface::GETRF(blas_int m,blas_int n,BLAS_data_type* A,blas_int ldA,blas_int* ipiv)
{
  blas_int info;
  _BLAS_(GETRF)(&m,&n,A,&ldA,ipiv,&info);
  return info;
}
#endif

template <>
inline blas_int BLAS_Interface::GETRI(blas_int n,BLAS_data_type* A,blas_int ldA,
                                      blas_int* ipiv,BLAS_data_type* work,blas_int lwork)
{
  blas_int info;
  _BLAS_(GETRI)(&n,A,&ldA,ipiv,work,&lwork,&info);
  return info;
}

template <>
inline blas_int BLAS_Interface::GETRS(blas_str trans,blas_int n,blas_int nrhs,BLAS_data_type* A,blas_int ldA,
                        blas_int* ipiv, BLAS_data_type* rhs,blas_int ldrhs)
{
  blas_int info;
  _BLAS_(GETRS)(const_cast<char*>(trans),&n,&nrhs,A,&ldA,ipiv,rhs,&ldrhs,&info);
  return info;
}

template <>
inline blas_int BLAS_Interface::SYEV(blas_str jobs,blas_str uplo,blas_int n,BLAS_data_type* A,blas_int ldA,
                                     BLAS_data_type* w,BLAS_data_type* work,blas_int lwork)
{
  blas_int info;
  _BLAS_(SYEV)(const_cast<char*>(jobs),const_cast<char*>(uplo),
               &n,A,&ldA,w,work,&lwork,&info);
  return info;
}