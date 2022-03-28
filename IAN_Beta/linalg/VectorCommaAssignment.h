#ifndef __VECTOR_COMMA_ASSIGNMENT_H
#define __VECTOR_COMMA_ASSIGNMENT_H

#include "typedefs.h"

template <typename AllocatorType>
class Vector;

template <typename AllocatorType>
class VectorCommaAssignment {
private:
  typedef typename AllocatorType::member_type data_type;

  Vector<AllocatorType>* _pvec;
  int_type    _ip;
  data_type   _val;

public:
  VectorCommaAssignment(Vector<AllocatorType> *pvec,int_type ip,const data_type& val):_pvec(pvec),_ip(ip),_val(val) {}

  ~VectorCommaAssignment(void) { 
    if(_pvec) for(int_type i=_ip;i<_pvec->size();i++) (*_pvec)(i)=_val;
  }

  operator data_type(void) { return _val; }

  VectorCommaAssignment operator,(data_type val) {
    Vector<AllocatorType>* pvec=_pvec;
    if(_ip<_pvec->size()) {
      (*_pvec)(_ip)=val;
      _pvec=NULL;
    }
    return VectorCommaAssignment(pvec,_ip+1,val);
  }
};

#endif