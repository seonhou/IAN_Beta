#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#include "Vector.h"

template <typename data_type>
class SparseMatrix {
private:
  int_type _nrow,_ncol;
  Vector< DynamicAllocator<data_type> > _val;
  IntVector _irow;
  IntVector _icol;

public:
  SparseMatrix(void):_nrow(0),_ncol(0) {}
  int_type num_rows(void) const { return _nrow; }
  void resize(int_type nr,int_type nc) { _nrow=nr; _ncol=nc; _irow.resize(nr+1); }
  Vector< DynamicAllocator<data_type> >& value(void) { return _val; }
  IntVector&  irow(void) { return _irow; }
  IntVector&  icol(void) { return _icol; }
  void dec_idx(void) { _irow-=1; _icol-=1; }
  void inc_idx(void) { _irow+=1; _icol+=1; }
};

typedef SparseMatrix<real_type> RealSparseMatrix;

#endif