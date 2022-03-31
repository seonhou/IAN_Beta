// only Matrix.h should include this file

template <typename StorageType>
class Matrix;

template <typename MemberType>
class Scal2Mat {
public:
  typedef MemberType data_type;
  data_type _s;
  Scal2Mat(const data_type& s):_s(s) {}
  data_type operator()(int_type i,int_type j) const { return _s; }
};

template <typename MatrixType1,typename MatrixType2,typename OprType>
struct Mat2Expr {
  const MatrixType1& _m1;
  const MatrixType2& _m2;
  typedef typename MatrixType1::data_type data_type;
  Mat2Expr(const MatrixType1& m1,const MatrixType2& m2):_m1(m1),_m2(m2) {}
  data_type operator()(int_type i,int_type j) const { return OprType::compute(_m1(i,j),_m2(i,j)); }
}; 

#define DEF_MAT_UPDATE(opr) \
Matrix& operator opr (const data_type& d) \
{ \
  for(int_type i=0;i<rows();i++) for(int_type j=0;j<columns();j++) get_(i,j) opr d; \
  return *this; \
} \
template <typename StorageType1> \
Matrix& operator opr (const Matrix<StorageType1>& mat) \
{ \
  assert(rows()==mat.rows() && columns()==mat.columns());  \
  for(int_type i=0;i<rows();i++) for(int_type j=0;j<columns();j++) get_(i,j) opr mat(i,j); \
  return *this; \
} \
template <typename MatrixType1,typename MatrixType2,typename OprType> \
Matrix& operator opr (const Mat2Expr<MatrixType1,MatrixType2,OprType>& mom) \
{ \
  for(int_type i=0;i<rows();i++) for(int_type j=0;j<columns();j++) get_(i,j) opr mom(i,j); \
  return *this; \
}


#define DEF_MAT2EXPR(OprType,opr) \
struct OprType { template <typename data_type> static data_type compute(const data_type& m1,const data_type& m2) { return m1 opr m2; } }; \
\
template <typename MatrixTypeR1,typename MatrixTypeL1,typename OprType1, \
          typename MatrixTypeR2,typename MatrixTypeL2,typename OprType2> \
inline Mat2Expr<Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>,Mat2Expr<MatrixTypeR2,MatrixTypeL2,OprType2>,OprType> \
operator opr (const Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>& m1,const Mat2Expr<MatrixTypeR2,MatrixTypeL2,OprType2>& m2) \
{ return Mat2Expr<Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>,Mat2Expr<MatrixTypeR2,MatrixTypeL2,OprType2>,OprType>(m1,m2); } \
\
template <typename MatrixTypeR1,typename MatrixTypeL1,typename OprType1,typename StorageType> \
inline Mat2Expr<Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>,Matrix<StorageType>,OprType> \
operator opr (const Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>& m1,const Matrix<StorageType>& m2) \
{ return Mat2Expr<Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>,Matrix<StorageType>,OprType>(m1,m2); } \
\
template <typename MatrixTypeR1,typename MatrixTypeL1,typename OprType1,typename StorageType> \
inline Mat2Expr<Matrix<StorageType>,Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>,OprType> \
operator opr (const Matrix<StorageType>& m1,const Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>& m2) \
{ return Mat2Expr<Matrix<StorageType>,Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>,OprType>(m1,m2); } \
\
template <typename StorageType1,typename StorageType2> \
inline Mat2Expr<Matrix<StorageType1>,Matrix<StorageType2>,OprType> \
operator opr (const Matrix<StorageType1>& m1,const Matrix<StorageType2>& m2) \
{ return Mat2Expr<Matrix<StorageType1>,Matrix<StorageType2>,OprType>(m1,m2); } \
\
template <typename StorageType> \
inline Mat2Expr<Scal2Mat<typename StorageType::member_type>,Matrix<StorageType>,OprType> \
operator opr (const Scal2Mat<typename StorageType::member_type>& m1,const Matrix<StorageType>& m2) \
{ return Mat2Expr<Scal2Mat<typename StorageType::member_type>,Matrix<StorageType>,OprType>(m1,m2); } \
\
template <typename MatrixTypeR1,typename MatrixTypeL1,typename OprType1> \
inline Mat2Expr<Scal2Mat<typename MatrixTypeR1::data_type>,Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>,OprType> \
operator opr (const Scal2Mat<typename MatrixTypeR1::member_type>& m1,const Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>& m2) \
{ return Mat2Expr<Scal2Mat<typename MatrixTypeR1::data_type>,Mat2Expr<MatrixTypeR1,MatrixTypeL1,OprType1>,OprType>(m1,m2); } \

DEF_MAT2EXPR(MatAdd,+)
DEF_MAT2EXPR(MatSub,-)
DEF_MAT2EXPR(MatMul,*)
DEF_MAT2EXPR(MatDiv,/)


template <typename StorageType1,typename StorageType2>
struct Mat2ExprMxM {
  const Matrix<StorageType1>& _m1;
  const Matrix<StorageType2>& _m2;
  Mat2ExprMxM(const Matrix<StorageType1>& m1,const Matrix<StorageType2>& m2):_m1(m1),_m2(m2) {}
};

template <typename StorageType1,typename StorageType2>
struct Mat2ExprSxMxM {
  const Mat2Expr<Scal2Mat<typename StorageType1::member_type>,Matrix<StorageType1>,MatMul>& _m1;
  const Matrix<StorageType2>& _m2;
  Mat2ExprSxMxM(const Mat2Expr<Scal2Mat<typename StorageType1::member_type>,Matrix<StorageType1>,MatMul>& m1,
                const Matrix<StorageType2>& m2):_m1(m1),_m2(m2) {}
};


// operator overloading for evaluation of matrix expressions

template <typename StorageType1,typename StorageType2>
inline Mat2ExprMxM<StorageType1,StorageType2> operator^(const Matrix<StorageType1>& m1,const Matrix<StorageType2>& m2) 
{ return Mat2ExprMxM<StorageType1,StorageType2>(m1,m2); }

template <typename StorageType1,typename StorageType2>
inline Mat2ExprSxMxM<StorageType1,StorageType2> operator^(const Mat2Expr<Scal2Mat<typename StorageType1::member_type>,Matrix<StorageType1>,MatMul>& m1,
                                                          const Matrix<StorageType2>& m2) 
{ return Mat2ExprSxMxM<StorageType1,StorageType2>(m1,m2); }

//template <typename AllocatorType1,typename AllocatorType2,typename AllocatorType3>
//inline Mat3ExprSxMtxMxM<AllocatorType1,AllocatorType2,AllocatorType3> operator^
//                                        (const Mat2ExprSxMxM< C_MatrixStorage<AllocatorType1>, FORT_MatrixStorage<AllocatorType2> >& m1,
//                                         const Matrix< FORT_MatrixStorage<AllocatorType3> >& m2) 
//{ return Mat3ExprSxMtxMxM<AllocatorType1,AllocatorType2,AllocatorType3>(m1,m2); }
