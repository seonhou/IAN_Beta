#ifndef __MATRIX_COMMA_ASSIGNMENT_H
#define __MATRIX_COMMA_ASSIGNMENT_H

#include "typedefs.h"

template <typename StorageType>
class Matrix; 

template <typename StorageType>
class MatrixCommaAssignment {
private:
  typedef typename StorageType::data_type data_type;

  Matrix<StorageType>* _pmat;
  int_type    _ip;
  data_type   _val;

  void get_crd(int_type& ir,int_type& ic) { ir=_ip%_pmat->rows(); ic=_ip/_pmat->rows(); }

public:
  MatrixCommaAssignment(Matrix<StorageType> *pmat,int_type ip,data_type val):_pmat(pmat),_ip(ip),_val(val) {}

  ~MatrixCommaAssignment(void) { 
    if(_pmat && _ip<_pmat->size()) {
      int_type i,j,ir,ic;
      get_crd(ir,ic);
      //for(i=ir;i<_pmat->rows();i++) (*_pmat)(i,ic)=_val;
      //for(j=ic+1;j<_pmat->columns();j++)
      //  for(i=0;i<_pmat->rows();i++)
      //    (*_pmat)(i,j)=_val;

  // valid for FORT_MatrixStorage only
      data_type* pd=_pmat->data();
      int_type ld=_pmat->get_ld();
      int_type nr=_pmat->rows();
      int_type nc=_pmat->columns();
      pd += ic*ld;
      for(i=ir;i<nr;i++) pd[i]=_val;
      for(j=ic+1;j<nc;j++) {
        pd+=ld;
        for(i=0;i<nr;i++)
          pd[i]=_val;
      }
    }
  }

  operator data_type(void) { return _val; }

  MatrixCommaAssignment operator,(const data_type& val) {
    Matrix<StorageType>* pmat=_pmat;
    if(_ip<_pmat->size()) {
      int_type ir,ic;
      get_crd(ir,ic);
      (*_pmat)(ir,ic) = val;
      _pmat=NULL;
    }
    return MatrixCommaAssignment(pmat,_ip+1,val);
  }
};

#endif