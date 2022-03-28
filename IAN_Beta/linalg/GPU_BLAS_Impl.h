// this file can be included only from GPU_BLAS_interface.
// Never include this file from other files

template <>
inline void GPU_BLAS_Interface::GEMM(blas_str transA,blas_str transB,
                                 blas_int m,blas_int n,blas_int k,
                                 BLAS_data_type alpha,const BLAS_data_type* A,blas_int ldA,
                                 const BLAS_data_type* B,blas_int ldB,
                                 BLAS_data_type beta,BLAS_data_type* C,blas_int ldC)
{
  if(GPU_Control::big_enough<BLAS_data_type>(m,n,k)) _GPU_BLAS_(gemm)(transA,transB,&m,&n,&k,&alpha,A,&ldA,B,&ldB,&beta,C,&ldC);
  else BLAS_Interface::GEMM(transA,transB,m,n,k,alpha,A,ldA,B,ldB,beta,C,ldC);
}

template <>
inline void GPU_BLAS_Interface::TRSM(blas_str lr,blas_str uplo,
                                 blas_str trans,blas_str diag,
                                 blas_int m,blas_int n,BLAS_data_type alpha,
                                 const BLAS_data_type* A,blas_int ldA,
                                       BLAS_data_type* B,blas_int ldB)
{  
  if(GPU_Control::big_enough<BLAS_data_type>(m,m,n)) _GPU_BLAS_(trsm)(lr,uplo,trans,diag,&m,&n,&alpha,A,&ldA,B,&ldB);
  else BLAS_Interface::TRSM(lr,uplo,trans,diag,m,n,alpha,A,ldA,B,ldB);
}

template <>
inline blas_int GPU_BLAS_Interface::POTRF(blas_str uplo,blas_int n,BLAS_data_type* A,blas_int ldA)
{
  blas_int info;
  if(GPU_Control::big_enough<BLAS_data_type>(n,n,n)) _GPU_LAPACK_(potrf)(const_cast<char*>(uplo),&n,A,&ldA,&info);
  else info=BLAS_Interface::POTRF(uplo,n,A,ldA);
  return info;
}

template <>
inline blas_int GPU_BLAS_Interface::GETRF(blas_int m,blas_int n,BLAS_data_type* A,blas_int ldA,blas_int* ipiv)
{
  blas_int info;
  if(GPU_Control::big_enough<BLAS_data_type>(m,n,n)) _GPU_LAPACK_(getrf)(&m,&n,A,&ldA,ipiv,&info);
  else BLAS_Interface::GETRF(m,n,A,ldA,ipiv,info);
  return info;
}

