#ifndef __MATRIX_H
#define __MATRIX_H

#include <iostream>
#include <assert.h>
#include "ArrayAllocator.h"
#include "MatrixCommaAssignment.h"
#include "MatrixEvaluation.h"

using namespace std;


class MatrixDimension {
private:
  int_type _nrow,_ncol;
  
protected:  
  MatrixDimension(void):_nrow(0),_ncol(0) {}
  MatrixDimension(int_type nRow,int_type nCol):_nrow(nRow),_ncol(nCol) {}
  
  void swap(MatrixDimension& md) { std::swap(_nrow,md._nrow); std::swap(_ncol,md._ncol); }

  bool resize_(int_type nRow,int_type nCol) 
  { 
    bool flag=false;
    if(nRow!=_nrow) { _nrow=nRow; flag=true; }
    if(nCol!=_ncol) { _ncol=nCol; flag=true; }
    return flag;
  }
  void check_range_(int_type ir,int_type ic) const { 
#ifdef _CHECK_RANGE
    assert(_nrow>ir); assert(_ncol>ic);
#endif
  }
  
public: 
  int_type rows(void) const { return _nrow; }
  int_type columns(void) const { return _ncol; }
  int_type size(void) const { return _nrow*_ncol; }
};


template <typename data_type>
class Shared2D_Allocator : public SharedAllocator<data_type> {
private:
  int_type   _ld;
  
protected:
  Shared2D_Allocator(void):SharedAllocator() {}
  Shared2D_Allocator(int_type size):SharedAllocator(size) {}
  Shared2D_Allocator(data_type* data,int_type ld):SharedAllocator(data),_ld(ld) {}

  void swap(Shared2D_Allocator& alc) { 
    std::swap(_ld,alc._ld); 
    SharedAllocator<data_type>::swap(alc); 
  }

  int_type get_ld_(int_type ld) const { return _ld; }

  enum { DEFAULT_ROWS=0, DEFAULT_COLUMNS=0 };
};

template <typename data_type,int_type NR=3,int_type NC=3>
class Static2D_Allocator : public StaticAllocator<data_type,NR*NC> {
protected:
  Static2D_Allocator(void):StaticAllocator() {}
  Static2D_Allocator(int_type size):StaticAllocator(size) {}
  Static2D_Allocator(data_type* data,int_type ld):StaticAllocator(data) {}

  void swap(Static2D_Allocator& alc) { assert(false); }

  enum { DEFAULT_ROWS=NR, DEFAULT_COLUMNS=NC };
};


template <typename AllocatorType>
class C_MatrixStorage : public MatrixDimension, public AllocatorType {
public:
  typedef typename AllocatorType::member_type data_type;
  typedef AllocatorType Allocator2DType;
  int_type get_ld(void) const { return AllocatorType::get_ld_(columns()); }  
  
protected:  
  C_MatrixStorage(void):MatrixDimension(AllocatorType::DEFAULT_ROWS,AllocatorType::DEFAULT_COLUMNS),AllocatorType() {}
  C_MatrixStorage(int_type nRow,int_type nCol):MatrixDimension(nRow,nCol),AllocatorType(size()) {}
  C_MatrixStorage(data_type* data,int_type nRow,int_type nCol,int_type ld):MatrixDimension(nRow,nCol),AllocatorType(data,ld) {}

  void swap(C_MatrixStorage& mstrg) { MatrixDimension::swap(mstrg); AllocatorType::swap(mstrg); }

  const data_type& get_(int_type ir,int_type ic) const { check_range_(ir,ic); return *data(ir*get_ld()+ic); }
  data_type& get_(int_type ir,int_type ic) { check_range_(ir,ic); return *data(ir*get_ld()+ic); }

  const data_type* get_p(int_type ir,int_type ic) const { check_range_(ir,ic); return data(ir*get_ld()+ic); }
  data_type* get_p(int_type ir,int_type ic) { check_range_(ir,ic); return data(ir*get_ld()+ic); }

  typedef Matrix< C_MatrixStorage< Shared2D_Allocator<data_type> > > SharedMatrixType;

  Vector< SharedAllocator<data_type> > get_column(const Range& ir,int_type ic) { assert(false); return get_row(ic,ir); }
  Vector< SharedAllocator<data_type> > get_row(int_type ir,const Range& ic); 

public:
  const data_type* operator[](int_type ir) const { return get_p(ir,0); } 
  data_type* operator[](int_type ir) { return get_p(ir,0); } 
};


template <typename AllocatorType>
class FORT_MatrixStorage : public MatrixDimension, public AllocatorType {  
public:
  typedef typename AllocatorType::member_type data_type;
  typedef AllocatorType Allocator2DType;
  int_type get_ld(void) const { return AllocatorType::get_ld_(rows()); }  
  
protected:  

  FORT_MatrixStorage(void):MatrixDimension(AllocatorType::DEFAULT_ROWS,AllocatorType::DEFAULT_COLUMNS),AllocatorType() {}
  FORT_MatrixStorage(int_type nRow,int_type nCol):MatrixDimension(nRow,nCol),AllocatorType(size()) {}
  FORT_MatrixStorage(data_type* data,int_type nRow,int_type nCol,int_type ld):MatrixDimension(nRow,nCol),AllocatorType(data,ld) {}

  void swap(FORT_MatrixStorage& mstrg) { MatrixDimension::swap(mstrg); AllocatorType::swap(mstrg); }

  const data_type& get_(int_type ir,int_type ic) const { check_range_(ir,ic); return *data(ir+get_ld()*ic); }
  data_type& get_(int_type ir,int_type ic) { check_range_(ir,ic); return *data(ir+get_ld()*ic); }

  const data_type* get_p(int_type ir,int_type ic) const { check_range_(ir,ic); return data(ir+get_ld()*ic); }
  data_type* get_p(int_type ir,int_type ic) { check_range_(ir,ic); return data(ir+get_ld()*ic); }

  typedef Matrix< FORT_MatrixStorage< Shared2D_Allocator<data_type> > > SharedMatrixType;

  Vector< SharedAllocator<data_type> > get_column(const Range& ir,int_type ic);
  Vector< SharedAllocator<data_type> > get_row(int_type ir,const Range& ic) { assert(false); return get_column(ic,ir); }
};


template <typename data_type>
class DiagonalMatrix {
private:
  data_type _val;

public:
  DiagonalMatrix(data_type val=1.):_val(val) {}
  data_type value(void) const { return _val; }
  DiagonalMatrix& operator=(data_type val) { _val=val; return *this; }
};

template <typename data_type>
DiagonalMatrix<data_type> operator*(data_type val,const DiagonalMatrix<data_type>& diag)
{
  return DiagonalMatrix<data_type>(val*diag.value());
}

typedef DiagonalMatrix<real_type> RealDiagonalMatrix;


template < typename StorageType=C_MatrixStorage< DynamicAllocator<real_type> > >
class Matrix : public StorageType {
private:
  template <typename StorageType1>
  void copy_mat_(const Matrix<StorageType1>& mat);

public:
  typedef typename StorageType::data_type data_type;
  typedef typename StorageType::data_type T_numtype;

  Matrix(void):StorageType() {}
  // constructor for Dynamic (or Static) Allocator
  Matrix(int_type nRow,int_type nCol):StorageType(nRow,nCol) {}
  // constructor for Shared2D_Allocator only
  Matrix(const data_type* data,int_type nRow,int_type nCol,int_type ld):StorageType(const_cast<data_type*>(data),nRow,nCol,ld) {}
  // copy constructor
  Matrix(const Matrix& mat);
  template <typename AllocatorType>
  Matrix(Vector<AllocatorType>& vec);

  ~Matrix(void) { deallocate_(); }
  
  void resize(int_type nRow,int_type nCol);

  // reserve nRow x nCol if current size is smaller than  nRow x nCol
  void reserve(int_type nRow,int_type nCol) {
    if(rows()<nRow || nCol<nCol) resize(nRow,nCol);
  }

  void swap(Matrix<StorageType>& mat) { StorageType::swap(mat); }

  const data_type& operator()(int_type ir,int_type ic) const { return get_(ir,ic); }
  data_type& operator()(int_type ir,int_type ic) { return get_(ir,ic); }
  typename StorageType::SharedMatrixType operator()(const Range& ir,const Range& ic);
  Vector< SharedAllocator<data_type> > operator()(const Range& ir,int_type ic) { return get_column(ir,ic); }
  Vector< SharedAllocator<data_type> > operator()(int_type ir,const Range& ic) { return get_row(ir,ic); }

  bool is_identity(void) const;
  bool operator==(const data_type& val) const;

  //Matrix& operator=(const data_type& d);
  MatrixCommaAssignment<StorageType> operator=(const data_type& val) { 
    if(size()>0) *data()=val;    
    return MatrixCommaAssignment<StorageType>(this,1,val);
  }

  Matrix& operator=(const Matrix& mat);

  template <typename StorageType1>
  Matrix& operator=(const Matrix<StorageType1>& mat);

  template <typename MatrixType1,typename MatrixType2,typename OprType>
  Matrix& operator=(const Mat2Expr<MatrixType1,MatrixType2,OprType>& mom);

  DEF_MAT_UPDATE(+=)
  DEF_MAT_UPDATE(-=)
  DEF_MAT_UPDATE(*=)
  DEF_MAT_UPDATE(/=)

  // special classes for BLAS matrix multiplication call
  template <typename AllocatorType1,typename AllocatorType2> // C Matrix multiplication using BLAS
  Matrix& operator=(const Mat2ExprMxM< C_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // Fortran Matrix multiplication using BLAS
  Matrix& operator=(const Mat2ExprMxM< FORT_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // C / Fortran Matrix multiplication using BLAS
  Matrix& operator=(const Mat2ExprMxM< C_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // Fortran / CMatrix multiplication using BLAS
  Matrix& operator=(const Mat2ExprMxM< FORT_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // C Matrix multiplication using BLAS
  Matrix& operator=(const Mat2ExprSxMxM< C_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // Fortran Matrix multiplication using BLAS
  Matrix& operator=(const Mat2ExprSxMxM< FORT_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // C / Fortran Matrix multiplication using BLAS
  Matrix& operator=(const Mat2ExprSxMxM< C_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // Fortran / C Matrix multiplication using BLAS
  Matrix& operator=(const Mat2ExprSxMxM< FORT_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // Vector x Vector^T
  Matrix& operator=(const Vec2ExprVxV<AllocatorType1,AllocatorType2>& vv);

  template <typename AllocatorType1,typename AllocatorType2> // C Matrix multiplication using BLAS
  Matrix& operator+=(const Mat2ExprMxM< C_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // Fortran Matrix multiplication using BLAS
  Matrix& operator+=(const Mat2ExprMxM< FORT_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // C / Fortran Matrix multiplication using BLAS
  Matrix& operator+=(const Mat2ExprMxM< C_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // Fortran / C Matrix multiplication using BLAS
  Matrix& operator+=(const Mat2ExprMxM< FORT_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // C Matrix multiplication using BLAS
  Matrix& operator+=(const Mat2ExprSxMxM< C_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // Fortran Matrix multiplication using BLAS
  Matrix& operator+=(const Mat2ExprSxMxM< FORT_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // C / Fortran Matrix multiplication using BLAS
  Matrix& operator+=(const Mat2ExprSxMxM< C_MatrixStorage<AllocatorType1>,FORT_MatrixStorage<AllocatorType2> >& mmm); 

  template <typename AllocatorType1,typename AllocatorType2> // Fortran / C Matrix multiplication using BLAS
  Matrix& operator+=(const Mat2ExprSxMxM< FORT_MatrixStorage<AllocatorType1>,C_MatrixStorage<AllocatorType2> >& mmm); 

  Matrix& operator=(const DiagonalMatrix<data_type>& diag) 
  { assert(rows()==columns()); *this = 0.; data_type val=diag.value(); for(int_type i=0;i<rows();i++) get_(i,i) = val; return *this; }
  Matrix& operator+=(const DiagonalMatrix<data_type>& diag) 
  { assert(rows()==columns()); data_type val=diag.value(); for(int_type i=0;i<rows();i++) get_(i,i) += val; return *this; }
  Matrix& operator-=(const DiagonalMatrix<data_type>& diag)
  { assert(rows()==columns()); data_type val=diag.value(); for(int_type i=0;i<rows();i++) get_(i,i) -= val; return *this; }

  // more special class to compute s*A^t*B*C using BLAS(or optimized) matrix multiplication call
  //template <typename AllocatorType1,typename AllocatorType2,typename AllocatorType3> 
  //Matrix& operator+=(Mat3ExprSxMtxMxM<AllocatorType1,AllocatorType2,AllocatorType3>& mmm); 
};

typedef Matrix< C_MatrixStorage< DynamicAllocator<real_type> > >          RealCMatrix;
typedef Matrix< FORT_MatrixStorage< DynamicAllocator<real_type> > >       RealMatrix;
typedef Matrix< C_MatrixStorage< Static2D_Allocator<real_type,2,2> > >    Real2x2CMatrix;
typedef Matrix< FORT_MatrixStorage< Static2D_Allocator<real_type,2,2> > > Real2x2Matrix;
typedef Matrix< C_MatrixStorage< Static2D_Allocator<real_type,3,3> > >    Real3x3CMatrix;
typedef Matrix< FORT_MatrixStorage< Static2D_Allocator<real_type,3,3> > > Real3x3Matrix;
typedef Matrix< C_MatrixStorage< Static2D_Allocator<real_type,6,6> > >    Real6x6CMatrix;
typedef Matrix< FORT_MatrixStorage< Static2D_Allocator<real_type,6,6> > > Real6x6Matrix;
typedef Matrix< C_MatrixStorage< Shared2D_Allocator<real_type> > >        RealCMatrixRef;
typedef Matrix< FORT_MatrixStorage< Shared2D_Allocator<real_type> > >     RealMatrixRef;


#define RealFixedMatrix(M,N)  Matrix< FORT_MatrixStorage< Static2D_Allocator<real_type,M,N> > >


template <typename AllocatorType>
inline Vector< SharedAllocator<typename AllocatorType::member_type> > C_MatrixStorage<AllocatorType>::get_row(int_type ir,const Range& ic)
{
  return Vector< SharedAllocator<typename AllocatorType::member_type> >(get_p(ir,ic.first()),ic.count(columns()-1));
}

template <typename AllocatorType>
inline Vector< SharedAllocator<typename AllocatorType::member_type> > FORT_MatrixStorage<AllocatorType>::get_column(const Range& ir,int_type ic)
{
  return Vector< SharedAllocator<typename AllocatorType::member_type> >(get_p(ir.first(),ic),ir.count(rows()-1));
}


template <typename StorageType>
inline Matrix<StorageType>::Matrix(const Matrix<StorageType>& mat):StorageType(mat.rows(),mat.columns())
{
  allocate_(mat.size());
  //copy_mat_(mat);
  init_mat_copy(mat,*this);
}

template <typename StorageType>
inline typename StorageType::SharedMatrixType Matrix<StorageType>::operator()(const Range& ir,const Range& ic)
{
  int_type nrows=ir.count(rows()-1);
  int_type ncols=ic.count(columns()-1);
  return typename StorageType::SharedMatrixType( const_cast<typename StorageType::data_type*>(get_p(ir.first(),ic.first())),nrows,ncols,get_ld() );
}


template <typename AllocatorType>
inline Matrix< C_MatrixStorage< Shared2D_Allocator<typename AllocatorType::member_type> > > Transpose(const Matrix< FORT_MatrixStorage<AllocatorType> >& mat)
{
  return Matrix< C_MatrixStorage< Shared2D_Allocator<typename AllocatorType::member_type> > >
              (const_cast<typename AllocatorType::member_type*>(mat.data()),mat.columns(),mat.rows(),mat.get_ld());
}

template <typename AllocatorType>
inline Matrix< FORT_MatrixStorage< Shared2D_Allocator<typename AllocatorType::member_type> > > Transpose(const Matrix< C_MatrixStorage<AllocatorType> >& mat)
{
  return Matrix< FORT_MatrixStorage< Shared2D_Allocator<typename AllocatorType::member_type> > >
              (const_cast<typename AllocatorType::member_type*>(mat.data()),mat.columns(),mat.rows(),mat.get_ld());
}

template <typename StorageType>
istream& operator>>(istream& is,Matrix<StorageType>& mat);

template <typename StorageType>
ostream& operator<<(ostream&,const Matrix<StorageType>&);


namespace BLAS_ArrayInfo {

template <typename StorageType>
inline int_type get_ld(const Matrix<StorageType>& mat) { return mat.get_ld(); }

template <typename AllocatorType>
inline int_type get_rows(const C_MatrixStorage<AllocatorType>& mat) { return mat.columns(); }

template <typename AllocatorType>
inline int_type get_rows(const FORT_MatrixStorage<AllocatorType>& mat) { return mat.rows(); }

template <typename AllocatorType>
inline int_type get_columns(const C_MatrixStorage<AllocatorType>& mat) { return mat.rows(); }

template <typename AllocatorType>
inline int_type get_columns(const FORT_MatrixStorage<AllocatorType>& mat) { return mat.columns(); }

}

#endif