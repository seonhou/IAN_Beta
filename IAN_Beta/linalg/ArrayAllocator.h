#ifndef __ARRAY_ALLOCATOR_H
#define __ARRAY_ALLOCATOR_H

#include "typedefs.h"
#include "mkl.h"
#include <iostream>

#ifdef _DEBUG
#ifndef _CHECK_RANGE
#define _CHECK_RANGE
#endif
#endif


template <typename data_type>
class DynamicAllocator {
private:
  data_type* _data;

protected:
  DynamicAllocator(void):_data(NULL) {}
  DynamicAllocator(int_type size) { allocate_(size); }
  DynamicAllocator(data_type* data,int_type ld) { assert(false); }

  void swap(DynamicAllocator& dalc) { std::swap(_data,dalc._data); }
  
  void allocate_(int_type size); //{ _data=new data_type[size]; }
  void deallocate_(void); //{ if(_data!=NULL) { delete _data; _data=NULL; } }   
  int_type get_ld_(int_type ld) const { return ld; }
  template <typename MatrixType>
  void init_mat_copy(const MatrixType& src,MatrixType& dest) { dest=src; }

  enum { DEFAULT_SIZE=0, DEFAULT_ROWS=0, DEFAULT_COLUMNS=0 };

public:
  typedef data_type member_type;  
  data_type* data(int_type i=0) { return _data+i; }  
  const data_type* data(int_type i=0) const { return _data+i; }  
};

template <typename data_type>
inline void DynamicAllocator<data_type>::allocate_(int_type size) { _data=new data_type[size]; }

template <typename data_type>
inline void DynamicAllocator<data_type>::deallocate_(void) { if(_data!=NULL) { delete _data; _data=NULL; } }  

template <>
inline void DynamicAllocator<real_type>::allocate_(int_type size) { _data=(real_type*)MKL_malloc(size*sizeof(double), 64); }

template <>
inline void DynamicAllocator<real_type>::deallocate_(void) { if(_data!=NULL) { MKL_free(_data); _data=NULL; } }  


template <typename data_type,int_type N=3>
class StaticAllocator {
private:
  data_type _data[N];

protected:
  StaticAllocator(void) {}
  StaticAllocator(int_type size) { allocate_(size); }
  StaticAllocator(data_type* data,int_type ld) { assert(false); }
  
  void allocate_(int_type size) { assert(size<=N); }
  void deallocate_(void) {}   
  int_type get_ld_(int_type ld) const { return ld; }
  template <typename MatrixType>
  void init_mat_copy(const MatrixType& src,MatrixType& dest) { dest=src; }
 
  enum { DEFAULT_SIZE=N };

public:
  typedef data_type member_type;
  data_type* data(int_type i=0) { return _data+i; }  
  const data_type* data(int_type i=0) const { return _data+i; }    
};


template <typename data_type>
class SharedAllocator {
private:
  data_type* _data;

protected:
  SharedAllocator(void) { assert(false); }
  SharedAllocator(int_type size) { assert(false); }
  SharedAllocator(data_type* data):_data(data) {}
  
  void swap(SharedAllocator& salc) { std::swap(_data,salc._data); }

  void allocate_(int_type size) { assert(false); }
  void deallocate_(void) {}   
  template <typename MatrixType>
  void init_mat_copy(const MatrixType& src,MatrixType& dest) { _data=src.data(); }
 
  enum { DEFAULT_SIZE=0 };

public:
  typedef data_type member_type;  
  data_type* data(int_type i=0) { return _data+i; }  
  const data_type* data(int_type i=0) const { return _data+i; }    
};

#endif