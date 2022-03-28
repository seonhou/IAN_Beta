// only Vector.h should include this file

template <typename AllocatorType>
class Vector;

template <typename MemberType>
class Scal2Vec {
public:
  typedef MemberType data_type;
  const data_type& _s;
  Scal2Vec(const data_type& s):_s(s) {}
  data_type operator[](int_type i) const { return _s; }
};

template <typename VectorType1,typename VectorType2,typename OprType>
class Vec2Expr {
private:
  const VectorType1& _v1;
  const VectorType2& _v2;

public:
  typedef typename VectorType1::data_type data_type;
  Vec2Expr(const VectorType1& v1,const VectorType2& v2):_v1(v1),_v2(v2) {}
  data_type operator[](int_type i) const { return OprType::compute(_v1[i],_v2[i]); }
  int_type size(void) const { return _v1.size(); }
}; 


#define DEF_VEC_UPDATE(opr) \
Vector& operator opr (const data_type& v1) \
{ \
  data_type* v2=data(); \
  for(int_type i=0;i<_size;i++) v2[i] opr v1; \
  return *this; \
} \
template <typename AllocatorType> \
Vector& operator opr (const Vector<AllocatorType>& vec) \
{ \
  assert(_size==vec.size());  \
  const data_type* v1=vec.data(); \
  data_type* v2=data(); \
  for(int_type i=0;i<_size;i++) v2[i] opr v1[i]; \
  return *this; \
} \
template <typename VectorType1,typename VectorType2,typename OprType> \
Vector& operator opr (const Vec2Expr<VectorType1,VectorType2,OprType>& vov) \
{ \
  data_type* v=data(); \
  for(int_type i=0;i<_size;i++) v[i] opr vov[i]; \
  return *this; \
}

template <typename StorageType>
class Matrix; 

template <typename AllocatorType>
class C_MatrixStorage;

template <typename AllocatorType>
class FORT_MatrixStorage;

template <typename AllocatorType1,typename AllocatorType2>
struct MatMulVec {
  const Matrix< FORT_MatrixStorage<AllocatorType1> >& _m;
  const Vector<AllocatorType2>& _v;
  MatMulVec(const Matrix< FORT_MatrixStorage<AllocatorType1> >& m,const Vector<AllocatorType2>& v):_m(m),_v(v) {}
};

template <typename AllocatorType1,typename AllocatorType2>
struct CMatMulVec {
  const Matrix< C_MatrixStorage<AllocatorType1> >& _m;
  const Vector<AllocatorType2>& _v;
  CMatMulVec(const Matrix< C_MatrixStorage<AllocatorType1> >& m,const Vector<AllocatorType2>& v):_m(m),_v(v) {}
};

//template <typename AllocatorType>
//struct ScalMulVecAddVec {
//  const ScalMulVec<AllocatorType>& _sv;
//  const Vector<AllocatorType>& _v2;
//  ScalMulVecAddVec(const ScalMulVec<AllocatorType>& sv,const Vector<AllocatorType>& v2):_sv(sv),_v2(v2) {}
//};
template <typename AllocatorType1,typename AllocatorType2>
inline MatMulVec<AllocatorType1,AllocatorType2> operator * (const Matrix< FORT_MatrixStorage<AllocatorType1> >& m,const Vector<AllocatorType2>& v)
{
  return MatMulVec<AllocatorType1,AllocatorType2>(m,v);
}

template <typename AllocatorType1,typename AllocatorType2>
inline CMatMulVec<AllocatorType1,AllocatorType2> operator * (const Matrix< C_MatrixStorage<AllocatorType1> >& m,const Vector<AllocatorType2>& v)
{
  return CMatMulVec<AllocatorType1,AllocatorType2>(m,v);
}

#define DEF_VEC2EXPR(OprType,opr) \
struct OprType { template <typename data_type> static data_type compute(const data_type& v1,const data_type& v2) { return v1 opr v2; } }; \
\
template <typename VectorTypeR1,typename VectorTypeL1,typename OprType1, \
          typename VectorTypeR2,typename VectorTypeL2,typename OprType2> \
inline Vec2Expr<Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>,Vec2Expr<VectorTypeR2,VectorTypeL2,OprType2>,OprType> \
operator opr (const Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>& v1,const Vec2Expr<VectorTypeR2,VectorTypeL2,OprType2>& v2) \
{ return Vec2Expr<Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>,Vec2Expr<VectorTypeR2,VectorTypeL2,OprType2>,OprType>(v1,v2); } \
\
template <typename VectorTypeR1,typename VectorTypeL1,typename OprType1,typename AllocatorType> \
inline Vec2Expr<Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>,Vector<AllocatorType>,OprType> \
operator opr (const Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>& v1,const Vector<AllocatorType>& v2) \
{ return Vec2Expr<Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>,Vector<AllocatorType>,OprType>(v1,v2); } \
\
template <typename VectorTypeR1,typename VectorTypeL1,typename OprType1,typename AllocatorType> \
inline Vec2Expr<Vector<AllocatorType>,Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>,OprType> \
operator opr (const Vector<AllocatorType>& v1,const Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>& v2) \
{ return Vec2Expr<Vector<AllocatorType>,Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>,OprType>(v1,v2); } \
\
template <typename AllocatorType1,typename AllocatorType2> \
inline Vec2Expr<Vector<AllocatorType1>,Vector<AllocatorType2>,OprType> \
operator opr (const Vector<AllocatorType1>& v1,const Vector<AllocatorType2>& v2) \
{ return Vec2Expr<Vector<AllocatorType1>,Vector<AllocatorType2>,OprType>(v1,v2); } \
\
template <typename AllocatorType> \
inline Vec2Expr<Scal2Vec<typename AllocatorType::member_type>,Vector<AllocatorType>,OprType> \
operator opr (const Scal2Vec<typename AllocatorType::member_type>& v1,const Vector<AllocatorType>& v2) \
{ return Vec2Expr<Scal2Vec<typename AllocatorType::member_type>,Vector<AllocatorType>,OprType>(v1,v2); } \
\
template <typename VectorTypeR1,typename VectorTypeL1,typename OprType1> \
inline Vec2Expr<Scal2Vec<typename VectorTypeR1::data_type>,Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>,OprType> \
operator opr (const Scal2Vec<typename VectorTypeR1::data_type>& v1,const Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>& v2) \
{ return Vec2Expr<Scal2Vec<typename VectorTypeR1::data_type>,Vec2Expr<VectorTypeR1,VectorTypeL1,OprType1>,OprType>(v1,v2); } \

DEF_VEC2EXPR(VecAdd,+)
DEF_VEC2EXPR(VecSub,-)
DEF_VEC2EXPR(VecMul,*)
DEF_VEC2EXPR(VecDiv,/)


template <typename AllocatorType1,typename AllocatorType2>
struct Vec2ExprVxV {
  const Vector<AllocatorType1>& _v1;
  const Vector<AllocatorType2>& _v2;
  Vec2ExprVxV(const Vector<AllocatorType1>& v1,const Vector<AllocatorType2>& v2):_v1(v1),_v2(v2) {}
  operator typename AllocatorType1::member_type(void) { return vec_dot(_v1,_v2); }
};

// operator overloading for evaluation of matrix expressions

template <typename AllocatorType1,typename AllocatorType2>
inline Vec2ExprVxV<AllocatorType1,AllocatorType2> operator^(const Vector<AllocatorType1>& v1,const Vector<AllocatorType2>& v2) 
{ return Vec2ExprVxV<AllocatorType1,AllocatorType2>(v1,v2); }
