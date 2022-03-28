#ifndef __RANGE_H_
#define __RANGE_H_

#include "typedefs.h"

class Range {
private:
  int_type _first;
  int_type _last;

  enum { TO_END=-1 };

public:
  //Range(int_type first):_first(first),_last(first) {}
  Range(int_type first,int_type last):_first(first),_last(last) {}

  int_type first(void) const { return _first; }
  int_type last(int_type to_end) const { if(_last==TO_END) return to_end; return _last; }
  int_type count(int_type to_end) const { return last(to_end)-first()+1; }

  static Range all(void) { return Range(0,TO_END); }
};

#endif