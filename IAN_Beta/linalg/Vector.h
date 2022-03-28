#ifndef __VECTOR_H
#define __VECTOR_H

#include <iostream>
#include <assert.h>
#include <math.h>
#include "ArrayAllocator.h"
#include "VectorCommaAssignment.h"
#include "VectorEvaluation.h"
#include "Range.h"

using namespace std;

#ifdef _CHECK_RANGE
#define vec_assert(cond) assert(cond)
#else
#define vec_assert(cond)
#endif

template < typename AllocatorType=DynamicAllocator<real_type> >
class Vector : public AllocatorType {
private: 
  int_type   _size;

  template <typename AllocatorType1>
  void copy_vec_(const Vector<AllocatorType1>& vec);

public:
  typedef typename AllocatorType::member_type data_type;
  typedef typename AllocatorType::member_type T_numtype;

  typedef data_type*       iterator;
  typedef const data_type* const_iterator ;

  iterator begin(void) { return data(); }
  iterator end(void) { return data()+size(); }
  const_iterator begin(void) const { return data(); }
  const_iterator end(void) const { return data()+size(); }

  // constructors
  Vector(void):_size(AllocatorType::DEFAULT_SIZE),AllocatorType() {}
  Vector(int_type size):_size(size),AllocatorType(size) {}
  Vector(const data_type* ptr,int_type size):_size(size),AllocatorType(const_cast<data_type*>(ptr)) {}
  Vector(const Vector<AllocatorType>& vec):_size(vec._size),AllocatorType(vec._size) { copy_vec_(vec); }
  //template <int_type N>
  //Vector(const data_type vec[N]):_size(N),AllocatorType(N) { for(int_type i=0;i<_size;i++) data()[i]=vec[i]; }
  //template <typename VectorType1,typename VectorType2,typename OprType>
  //Vector(const Vec2Expr<VectorType1,VectorType2,OprType>& vov):_size(vov._v1.size()),AllocatorType(vov._v1.size()) { allocate_(_size);  *this=vov; }
  ~Vector(void) {  deallocate_(); }

  void resize(int_type sz);
  void clear(void) { resize(0); }
  int_type size(void) const { return _size; }
  int_type stride(void) const { return 1; }

  void swap(Vector& vec) { std::swap(_size,vec._size); AllocatorType::swap(vec); }

  void reserve(int_type sz) { if(size()<sz) resize(sz); }

  const data_type&  operator[](int_type i) const { vec_assert(_size>i); return *data(i); }
  data_type& operator[](int_type i) { vec_assert(_size>i); return *data(i); }
  const data_type&  operator()(int_type i) const { vec_assert(_size>i); return *data(i); }
  data_type& operator()(int_type i) { vec_assert(_size>i); return *data(i); }

  Vector< SharedAllocator<data_type> >  operator()(const Range& r) const 
  { return Vector< SharedAllocator<data_type> >(const_cast<data_type*>(data(r.first())),r.count(size()-1));  }
  Vector< SharedAllocator<data_type> >  operator()(const Range& r)  
  { return Vector< SharedAllocator<data_type> >(data(r.first()),r.count(size()-1));  }

  //Vector& operator=(data_type d);
  VectorCommaAssignment<AllocatorType> operator=(const data_type& val) {
    if(size()>0) *data()=val;
    return VectorCommaAssignment<AllocatorType>(this,1,val);
  }

  Vector& operator=(const Vector& vec);
  template <typename AllocatorType1>
  Vector& operator=(const Vector<AllocatorType1>& vec);
  template <typename VectorType1,typename VectorType2,typename OprType>
  Vector& operator=(const Vec2Expr<VectorType1,VectorType2,OprType>& vov);

  DEF_VEC_UPDATE(+=)
  DEF_VEC_UPDATE(-=)
  DEF_VEC_UPDATE(*=)
  DEF_VEC_UPDATE(/=)

  template <typename AllocatorType1,typename AllocatorType2>
  Vector& operator=(const MatMulVec<AllocatorType1,AllocatorType2 >& mmv);  // y=A*x  using BLAS
  template <typename AllocatorType1,typename AllocatorType2>
  Vector& operator+=(const MatMulVec<AllocatorType1,AllocatorType2 >& mmv); // y+=A*x using BLAS
  template <typename AllocatorType1,typename AllocatorType2>
  Vector& operator-=(const MatMulVec<AllocatorType1,AllocatorType2 >& mmv); // y-=A*x using BLAS

  template <typename AllocatorType1,typename AllocatorType2>
  Vector& operator=(const CMatMulVec<AllocatorType1,AllocatorType2 >& mmv);  // y=A`*x  using BLAS
  template <typename AllocatorType1,typename AllocatorType2>
  Vector& operator+=(const CMatMulVec<AllocatorType1,AllocatorType2 >& mmv); // y+=A`*x using BLAS
  template <typename AllocatorType1,typename AllocatorType2>
  Vector& operator-=(const CMatMulVec<AllocatorType1,AllocatorType2 >& mmv); // y-=A`*x using BLAS
};

template <typename AllocatorType>
ostream& operator<<(ostream&,const Vector<AllocatorType>&);


//template <typename AllocatorType>
//inline ScalMulVecAddVec<AllocatorType> operator+(const ScalMulVec<AllocatorType>& sv,const Vector<AllocatorType>& v2)
//{ return ScalMulVecAddVec<AllocatorType>(sv,v2); }

typedef Vector< DynamicAllocator<real_type> >  RealVector;
typedef Vector< StaticAllocator<real_type,3> > RealVector2;
typedef Vector< StaticAllocator<real_type,3> > RealVector3;
typedef Vector< StaticAllocator<real_type,6> > RealVector6;
typedef Vector< SharedAllocator<real_type> >   RealVectorRef;

typedef Vector< DynamicAllocator<int_type> >  IntVector;
typedef Vector< StaticAllocator<int_type,3> > IntVector2;
typedef Vector< StaticAllocator<int_type,3> > IntVector3;
typedef Vector< StaticAllocator<int_type,6> > IntVector6;
typedef Vector< SharedAllocator<int_type> >   IntVectorRef;

#define RealFixedVector(N) Vector< StaticAllocator<real_type,N> >
#define IntFixedVector(N)  Vector< StaticAllocator<int_type,N> >

template <typename AllocatorType1,typename AllocatorType2>
typename AllocatorType1::member_type vec_dot(const Vector<AllocatorType1>& vec1,const Vector<AllocatorType2>& vec2);

inline real_type norm(const RealVector3& vec) { const real_type* ptr=vec.data(); return sqrt(ptr[0]*ptr[0]+ptr[1]*ptr[1]+ptr[2]*ptr[2]); }

inline RealVector3 cross(const RealVector3& v1,const RealVector3& v2) 
{ 
  RealVector3 v3;
  v3(0)=v1(1)*v2(2)-v1(2)*v2(1);
  v3(1)=v1(2)*v2(0)-v1(0)*v2(2);
  v3(2)=v1(0)*v2(1)-v1(1)*v2(0);
  return v3; 
}

template <typename VectorType>
typename VectorType::data_type max_abs(const VectorType& vec)
{
  typename VectorType::data_type maxval=0;
  for(int_type i=0;i<vec.size();i++) maxval=std::max(maxval,fabs(vec[i]));
  return maxval;
}

template <typename VectorType>
typename VectorType::data_type max_val(const VectorType& vec)
{
  typename VectorType::data_type maxval=vec[0];
  for(int_type i=1;i<vec.size();i++) maxval=std::max(maxval,vec[i]);
  return maxval;
}

namespace BLAS_ArrayInfo {

template <typename AllocatorType>
inline int_type get_ld(const Vector<AllocatorType>& vec) { return vec.size(); }

template <typename AllocatorType>
inline int_type get_stride(const Vector<AllocatorType>& vec) { return vec.stride(); }

template <typename AllocatorType>
inline int_type get_rows(const Vector<AllocatorType>& vec) { return vec.size(); }

template <typename AllocatorType>
inline int_type get_columns(const Vector<AllocatorType>& vec) { return 1; }

}

#endif