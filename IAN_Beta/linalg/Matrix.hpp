#include "Matrix.h"

//template <typename data_type>
//void C_MatrixStorage<data_type>::allocate_(void)
//{
//  _data = new data_type*[rows()];
//  _data[0] = new data_type[size()];
//  for(int_type i=0; i<rows(); i++)
//     _data[i] = _data[0] + columns()*i;
//}
//
//template <typename data_type>
//void C_MatrixStorage<data_type>::deallocate_(void)
//{
//  if(_data!=NULL) {
//    delete[] _data[0];
//    delete[] _data;
//    _data=NULL;
//  }
//}

template <typename StorageType>
template <typename StorageType1>
void Matrix<StorageType>::copy_mat_(const Matrix<StorageType1>& mat)
{
  // valid for FORT_MatrixStorage only
  if(mat.get_ld()==get_ld() && get_ld()==rows()) {
    int_type sz=rows()*columns();
    data_type* pdest=data();
    const data_type* psrc=mat.data();
    for(int_type i=0;i<sz;++i) pdest[i]=psrc[i];
  }
  else {
    data_type* pdest=data();
    const data_type* psrc=mat.data();
    int_type i,j,nc=columns(),nr=rows();
    for(i=0;i<nc;++i) { 
      for(j=0;j<nr;++j) pdest[j]=psrc[j];
      pdest += get_ld();
      psrc += mat.get_ld();
    }
  }

  //for(int_type j=0;j<columns();j++) 
  //  for(int_type i=0;i<rows();i++) get_(i,j)=mat(i,j);
}

template <typename StorageType>
inline void Matrix<StorageType>::resize(int_type nRow, int_type nCol)
{
  if(resize_(nRow,nCol)) {
    deallocate_();
    allocate_(size());
  }
}

//template <typename StorageType>
//Matrix<StorageType>& Matrix<StorageType>::operator=(const typename StorageType::data_type& d)
//{
//  for(int_type i=0;i<rows();i++) for(int_type j=0;j<columns();j++) get_(i,j)=d;
//  return *this;
//}

template <typename StorageType>
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Matrix<StorageType>& mat) 
{ 
  resize(mat.rows(),mat.columns());
  copy_mat_(mat);
  return *this; 
}

template <typename StorageType>
template <typename StorageType1>
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Matrix<StorageType1>& mat) 
{ 
  resize(mat.rows(),mat.columns());
  copy_mat_(mat);
  return *this; 
}

template <typename StorageType>
template <typename MatrixType1,typename MatrixType2,typename OprType>
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Mat2Expr<MatrixType1,MatrixType2,OprType>& mom)
{ 
  for(int_type i=0;i<rows();i++) for(int_type j=0;j<columns();j++) get_(i,j) = mom(i,j);
  return *this;
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // C Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Mat2ExprMxM< C_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm)
{
  return BLAS::MxM(mmm._m2,mmm._m1,*this); // C Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // Fortran Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Mat2ExprMxM< FORT_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm)
{
  return BLAS::MxM(mmm._m1,mmm._m2,*this); // Fortran Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // C / Fortran Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Mat2ExprMxM< C_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm)
{
  return BLAS::MtxM(mmm._m1,mmm._m2,*this); // C / Fortran Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // Fortran / C Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Mat2ExprMxM< FORT_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm)
{
  return BLAS::MxMt(mmm._m1,mmm._m2,*this); // Fortran / C Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // C Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator+=(const Mat2ExprMxM< C_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm)
{
  return BLAS::MxM(1.,mmm._m2,mmm._m1,1.,*this); // C Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // Fortran Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator+=(const Mat2ExprMxM< FORT_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm)
{
  return BLAS::MxM(1.,mmm._m1,mmm._m2,1.,*this); // Fortran Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // C / Fortran Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator+=(const Mat2ExprMxM< C_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm)
{
  return BLAS::MtxM(1.,mmm._m1,mmm._m2,1.,*this); // C / Fortran Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // Fortran / C Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator+=(const Mat2ExprMxM< FORT_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm)
{
  return BLAS::MxMt(1.,mmm._m1,mmm._m2,1.,*this); // Fortran / C Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // C Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Mat2ExprSxMxM< C_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm)
{
  data_type alpha=mmm._m1._m1._s;
  return BLAS::MxM(alpha,mmm._m2,mmm._m1._m2,0.,*this); // C Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // Fortran Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Mat2ExprSxMxM< FORT_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm)
{
  data_type alpha=mmm._m1._m1._s;
  return BLAS::MxM(alpha,mmm._m1._m2,mmm._m2,0.,*this); // Fortran Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // C / Fortran Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Mat2ExprSxMxM< C_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm)
{
  data_type alpha=mmm._m1._m1._s;
  return BLAS::MtxM(alpha,mmm._m1._m2,mmm._m2,0.,*this); // C / Fortran Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // Fortran / C Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator=(const Mat2ExprSxMxM< FORT_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm)
{
  data_type alpha=mmm._m1._m1._s;
  return BLAS::MxMt(alpha,mmm._m1._m2,mmm._m2,0.,*this); // Fortran / C Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // C Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator+=(const Mat2ExprSxMxM< C_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm)
{
  data_type alpha=mmm._m1._m1._s;
  return BLAS::MxM(alpha,mmm._m2,mmm._m1._m2,1.,*this); // C Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // Fortran Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator+=(const Mat2ExprSxMxM< FORT_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm)
{
  data_type alpha=mmm._m1._m1._s;
  return BLAS::MxM(alpha,mmm._m1._m2,mmm._m2,1.,*this); // Fortran Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // C / Fortran Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator+=(const Mat2ExprSxMxM< C_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm)
{
  data_type alpha=mmm._m1._m1._s;
  return BLAS::MtxM(alpha,mmm._m1._m2,mmm._m2,1.,*this); // C / Fortran Matrix multiplication using BLAS
}

template <typename StorageType>
template <typename AllocatorType1,typename AllocatorType2> // Fortran / C Matrix multiplication using BLAS
inline Matrix<StorageType>& Matrix<StorageType>::operator+=(const Mat2ExprSxMxM< FORT_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm)
{
  data_type alpha=mmm._m1._m1._s;
  return BLAS::MxMt(alpha,mmm._m1._m2,mmm._m2,1.,*this); // Fortran / C Matrix multiplication using BLAS
}

template <typename StorageType>
bool Matrix<StorageType>::is_identity(void) const
{
  int_type n=rows();
  if(n!=columns()) return false;
  for(int_type i=0,j;i<n;i++) {
    for(j=0;j<i;j++) if(!is_zero(get_(i,j))) return false;
    if(!is_equal(get_(i,i),1.)) return false;
    for(j=i+1;j<n;j++) if(!is_zero(get_(i,j))) return false;
  }
  return true;
}

template <typename StorageType>
bool Matrix<StorageType>::operator==(const typename StorageType::data_type& val) const
{
  int_type i,j,nr=rows(),nc=columns();
  for(i=0;i<nc;i++) {
    for(j=0;j<nr;j++) if(!is_zero(get_(j,i)-val)) return false;
  }
  return true;
}

template <typename StorageType>
istream& operator>>(istream& is,Matrix<StorageType>& mat)
{
  for(int i=0;i<mat.rows();i++)
    for(int j=0;j<mat.columns();j++) is>>mat(i,j);
  return is;
}

template <typename StorageType>
ostream& operator<<(ostream& os,const Matrix<StorageType>& mat)
{
  for(int_type i=0;i<mat.rows();i++) {
    for(int_type j=0;j<mat.columns();j++) os<<mat(i,j)<<"  ";
  }
  return os;
}