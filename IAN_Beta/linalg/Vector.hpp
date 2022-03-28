#ifndef __VECTOR_HPP_
#define __VECTOR_HPP_

#include "Vector.h"
#include "Matrix.h"
#include "BLAS_Interface.h"

template <typename StorageType>
template <typename AllocatorType>
inline Matrix<StorageType>::Matrix(Vector<AllocatorType>& vec)
:StorageType(vec.data(),vec.size(),1,vec.size()) {}

template <typename AllocatorType>
template <typename AllocatorType1>
void Vector<AllocatorType>::copy_vec_(const Vector<AllocatorType1>& vec)
{
  const data_type *v1=vec.data();
  data_type *v0=data();
  for(int_type i=0;i<_size;i++) v0[i]=v1[i];
}

template <typename AllocatorType>
void Vector<AllocatorType>::resize(int_type sz)
{
  if(sz==_size) return;
  deallocate_();
  _size = sz;
  allocate_(_size);
}

//template <typename AllocatorType>
//Vector<AllocatorType>& Vector<AllocatorType>::operator=(data_type d)
//{
//  data_type *v0=data();
//  for(int_type i=0;i<_size;i++) v0[i]=d;
//  return *this;
//}

template <typename AllocatorType>
Vector<AllocatorType>& Vector<AllocatorType>::operator=(const Vector<AllocatorType>& vec) 
{ 
  resize(vec.size());
  copy_vec_(vec);
  return *this; 
}

template <typename AllocatorType>
template <typename AllocatorType1>
Vector<AllocatorType>& Vector<AllocatorType>::operator=(const Vector<AllocatorType1>& vec) 
{ 
  resize(vec.size());
  copy_vec_(vec);
  return *this; 
}

template <typename AllocatorType>
template <typename AllocatorType1,typename AllocatorType2>
Vector<AllocatorType>& Vector<AllocatorType>::operator=(const MatMulVec<AllocatorType1,AllocatorType2>& mmv)
{
  resize(mmv._m.rows());
  return BLAS::MxV(mmv._m,mmv._v,*this);
  //return BLAS::MxV(1.,mmv._m,mmv._v,0.,*this);
}

template <typename AllocatorType>
template <typename AllocatorType1,typename AllocatorType2>
Vector<AllocatorType>& Vector<AllocatorType>::operator+=(const MatMulVec<AllocatorType1,AllocatorType2>& mmv)
{
  resize(mmv._m.rows());
  return BLAS::MxV(1.,mmv._m,mmv._v,1.,*this);
}

template <typename AllocatorType>
template <typename AllocatorType1,typename AllocatorType2>
Vector<AllocatorType>& Vector<AllocatorType>::operator-=(const MatMulVec<AllocatorType1,AllocatorType2>& mmv)
{
  resize(mmv._m.rows());
  return BLAS::MxV(-1.,mmv._m,mmv._v,1.,*this);
}

template <typename AllocatorType>
template <typename AllocatorType1,typename AllocatorType2>
Vector<AllocatorType>& Vector<AllocatorType>::operator=(const CMatMulVec<AllocatorType1,AllocatorType2>& mmv)
{
  resize(mmv._m.rows());
  return BLAS::MtxV(mmv._m,mmv._v,*this);
  //return BLAS::MxV(1.,mmv._m,mmv._v,0.,*this);
}

template <typename AllocatorType>
template <typename AllocatorType1,typename AllocatorType2>
Vector<AllocatorType>& Vector<AllocatorType>::operator+=(const CMatMulVec<AllocatorType1,AllocatorType2>& mmv)
{
  resize(mmv._m.rows());
  return BLAS::MtxV(1.,mmv._m,mmv._v,1.,*this);
}

template <typename AllocatorType>
template <typename AllocatorType1,typename AllocatorType2>
Vector<AllocatorType>& Vector<AllocatorType>::operator-=(const CMatMulVec<AllocatorType1,AllocatorType2>& mmv)
{
  resize(mmv._m.rows());
  return BLAS::MtxV(-1.,mmv._m,mmv._v,1.,*this);
}

//template <typename AllocatorType>
//Vector<AllocatorType>& Vector<AllocatorType>::operator=(const ScalMulVecAddVec<AllocatorType>& daxpy)
//{
//  assert(daxpy._v2.size()==daxpy._sv._v.size());
//  resize(daxpy._v2.size());
//  data_type s=daxpy._sv._s;
//  const data_type* v1=daxpy._sv._v.data();
//  const data_type* v2=daxpy._v2.data();
//  data_type* v0=data();
//  for(int_type i=0;i<_size;i++) v0[i]=s*v1[i]+v2[i];
//  return *this;
//}

template <typename AllocatorType>
template <typename VectorType1,typename VectorType2,typename OprType>
Vector<AllocatorType>& Vector<AllocatorType>::operator=(const Vec2Expr<VectorType1,VectorType2,OprType>& vov)
{
  //const data_type* v1=vov._v1.data();
  //const data_type* v2=vov._v2.data();
  data_type* v3=data();
  for(int_type i=0;i<_size;i++) v3[i]=vov[i];
  return *this;
} 


template <>
template <typename AllocatorType1,typename AllocatorType2> // Vector x Vector^T
Matrix< C_MatrixStorage< DynamicAllocator<real_type> > >& 
Matrix< C_MatrixStorage< DynamicAllocator<real_type> > >::operator=(const Vec2ExprVxV<AllocatorType1,AllocatorType2>& vv)
{
  const typename AllocatorType1::member_type* v1=vv._v1.data();
  typename AllocatorType1::member_type vi;
  const typename AllocatorType2::member_type* v2=vv._v2.data();
  int_type n1=vv._v1.size();
  int_type n2=vv._v2.size();
  data_type* rp;
  resize(n1,n2);
  for(int_type i=0;i<n1;i++) {
    rp = get_p(i,0);
    vi = v1[i];
    for(int_type j=0;j<n2;j++)
      *(rp+j)=vi*v2[j];
  }
  return *this;
}

template <>
template <typename AllocatorType1,typename AllocatorType2> // Vector x Vector^T
Matrix< FORT_MatrixStorage< DynamicAllocator<real_type> > >& 
Matrix< FORT_MatrixStorage< DynamicAllocator<real_type> > >::operator=(const Vec2ExprVxV<AllocatorType1,AllocatorType2>& vv)
{
  const typename AllocatorType1::member_type* v1=vv._v1.data();
  typename AllocatorType2::member_type vi;
  const typename AllocatorType2::member_type* v2=vv._v2.data();
  int_type n1=vv._v1.size();
  int_type n2=vv._v2.size();
  data_type* rp;
  resize(n1,n2);
  for(int_type i=0;i<n2;i++) {
    rp = get_p(0,i);
    vi = v2[i];
    for(int_type j=0;j<n1;j++)
      *(rp+j)=v1[j]*vi;
  }
  return *this;
}


template <typename AllocatorType1,typename AllocatorType2>
typename AllocatorType1::member_type vec_dot(const Vector<AllocatorType1>& vec1,const Vector<AllocatorType2>& vec2)
{
  assert(vec1.size()==vec2.size());
  typename AllocatorType1::member_type sum=0;
  const typename AllocatorType1::member_type* v1=vec1.data();
  const typename AllocatorType1::member_type* v2=vec2.data();  
  for(int_type i=0;i<vec1.size();i++) 
    sum+=v1[i]*v2[i];
  return sum;
}

template <typename AllocatorType>
ostream& operator<<(ostream& os,const Vector<AllocatorType>& vec)
{
  for(int_type i=0;i<vec.size();i++) os<<vec[i]<<"  ";
  return os;
}

#endif