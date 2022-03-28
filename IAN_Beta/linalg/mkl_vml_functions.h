/* file: mkl_vml_functions.h */
/*
//  Copyright(C) 2006-2011 Intel Corporation. All Rights Reserved.
//  
//  The source code, information  and  material ("Material") contained herein is
//  owned  by Intel Corporation or its suppliers or licensors, and title to such
//  Material remains  with Intel Corporation  or its suppliers or licensors. The
//  Material  contains proprietary information  of  Intel or  its  suppliers and
//  licensors. The  Material is protected by worldwide copyright laws and treaty
//  provisions. No  part  of  the  Material  may  be  used,  copied, reproduced,
//  modified, published, uploaded, posted, transmitted, distributed or disclosed
//  in any way  without Intel's  prior  express written  permission. No  license
//  under  any patent, copyright  or  other intellectual property rights  in the
//  Material  is  granted  to  or  conferred  upon  you,  either  expressly,  by
//  implication, inducement,  estoppel or  otherwise.  Any  license  under  such
//  intellectual  property  rights must  be express  and  approved  by  Intel in
//  writing.
//  
//  *Third Party trademarks are the property of their respective owners.
//  
//  Unless otherwise  agreed  by Intel  in writing, you may not remove  or alter
//  this  notice or  any other notice embedded  in Materials by Intel or Intel's
//  suppliers or licensors in any way.
*/
/*
//++
//  User-level VML function declarations
//--
*/

#ifndef __MKL_VML_FUNCTIONS_H__
#define __MKL_VML_FUNCTIONS_H__

#include "mkl_vml_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
//++
//  EXTERNAL API MACROS.
//  Used to construct VML function declaration. Change them if you are going to
//  provide different API for VML functions.
//--
*/
#if defined(MKL_VML_STDCALL)
/*
  #define _Vml_Api(rtype,name,arg) extern rtype __stdcall name    arg;
  #define _vml_api(rtype,name,arg) extern rtype __stdcall name    arg;
  #define _VML_API(rtype,name,arg) extern rtype __stdcall name    arg;
*/
  #error The new pure dynamic linking model used by linking to libmkl_rt does not support this interface
#else /* MKL_VML_CDECL */
  #define _Vml_Api(rtype,name,arg) extern rtype __cdecl   name    arg;
  #define _vml_api(rtype,name,arg) extern rtype __cdecl   name    arg;
  #define _VML_API(rtype,name,arg) extern rtype __cdecl   name    arg;
#endif

/*
//++
//  VML ELEMENTARY FUNCTION DECLARATIONS.
//--
*/
/* Absolute value: r[i] = |a[i]| */
_VML_API(void,VSABS,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDABS,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsabs,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdabs,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsAbs,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdAbs,(const MKL_INT n,  const double a[], double r[]))

/* Complex absolute value: r[i] = |a[i]| */
_VML_API(void,VCABS,(const MKL_INT *n, const MKL_Complex8  a[], float  r[]))
_VML_API(void,VZABS,(const MKL_INT *n, const MKL_Complex16 a[], double r[]))
_vml_api(void,vcabs,(const MKL_INT *n, const MKL_Complex8  a[], float  r[]))
_vml_api(void,vzabs,(const MKL_INT *n, const MKL_Complex16 a[], double r[]))
_Vml_Api(void,vcAbs,(const MKL_INT n,  const MKL_Complex8  a[], float  r[]))
_Vml_Api(void,vzAbs,(const MKL_INT n,  const MKL_Complex16 a[], double r[]))

/* Argument of complex value: r[i] = carg(a[i]) */
_VML_API(void,VCARG,(const MKL_INT *n, const MKL_Complex8  a[], float  r[]))
_VML_API(void,VZARG,(const MKL_INT *n, const MKL_Complex16 a[], double r[]))
_vml_api(void,vcarg,(const MKL_INT *n, const MKL_Complex8  a[], float  r[]))
_vml_api(void,vzarg,(const MKL_INT *n, const MKL_Complex16 a[], double r[]))
_Vml_Api(void,vcArg,(const MKL_INT n,  const MKL_Complex8  a[], float  r[]))
_Vml_Api(void,vzArg,(const MKL_INT n,  const MKL_Complex16 a[], double r[]))

/* Argument of complex value: r[i] = carg(a[i]) */
_VML_API(void,VMCARG,(const MKL_INT *n, const MKL_Complex8  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMZARG,(const MKL_INT *n, const MKL_Complex16 a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmcarg,(const MKL_INT *n, const MKL_Complex8  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmzarg,(const MKL_INT *n, const MKL_Complex16 a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmcArg,(const MKL_INT n,  const MKL_Complex8  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmzArg,(const MKL_INT n,  const MKL_Complex16 a[], double r[], MKL_INT64 mode))

/* Addition: r[i] = a[i] + b[i] */
_VML_API(void,VSADD,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_VML_API(void,VDADD,(const MKL_INT *n, const double a[], const double b[], double r[]))
_vml_api(void,vsadd,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_vml_api(void,vdadd,(const MKL_INT *n, const double a[], const double b[], double r[]))
_Vml_Api(void,vsAdd,(const MKL_INT n,  const float  a[], const float  b[], float  r[]))
_Vml_Api(void,vdAdd,(const MKL_INT n,  const double a[], const double b[], double r[]))

/* Complex addition: r[i] = a[i] + b[i] */
_VML_API(void,VCADD,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_VML_API(void,VZADD,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_vml_api(void,vcadd,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_vml_api(void,vzadd,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_Vml_Api(void,vcAdd,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_Vml_Api(void,vzAdd,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))

_VML_API(void,VMCADD,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZADD,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcadd,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzadd,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcAdd,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzAdd,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 mode))

/* Subtraction: r[i] = a[i] - b[i] */
_VML_API(void,VSSUB,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_VML_API(void,VDSUB,(const MKL_INT *n, const double a[], const double b[], double r[]))
_vml_api(void,vssub,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_vml_api(void,vdsub,(const MKL_INT *n, const double a[], const double b[], double r[]))
_Vml_Api(void,vsSub,(const MKL_INT n,  const float  a[], const float  b[], float  r[]))
_Vml_Api(void,vdSub,(const MKL_INT n,  const double a[], const double b[], double r[]))

/* Complex subtraction: r[i] = a[i] - b[i] */
_VML_API(void,VCSUB,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_VML_API(void,VZSUB,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_vml_api(void,vcsub,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_vml_api(void,vzsub,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_Vml_Api(void,vcSub,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_Vml_Api(void,vzSub,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))

_VML_API(void,VMCSUB,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZSUB,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcsub,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzsub,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcSub,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzSub,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 mode))

/* Reciprocal: r[i] = 1.0 / a[i] */
_VML_API(void,VSINV,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDINV,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsinv,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdinv,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsInv,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdInv,(const MKL_INT n,  const double a[], double r[]))

/* Reciprocal: r[i] = 1.0 / a[i] */
_VML_API(void,VMSINV,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDINV,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsinv,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdinv,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsInv,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdInv,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Square Root: r[i] = a[i]^0.5 */
_VML_API(void,VSSQRT,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDSQRT,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vssqrt,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdsqrt,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsSqrt,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdSqrt,(const MKL_INT n,  const double a[], double r[]))

/* Square Root: r[i] = a[i]^0.5 */
_VML_API(void,VMSSQRT,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDSQRT,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmssqrt,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdsqrt,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsSqrt,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdSqrt,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Square Root: r[i] = a[i]^0.5 */
_VML_API(void,VCSQRT,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZSQRT,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcsqrt,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzsqrt,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcSqrt,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzSqrt,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Square Root: r[i] = a[i]^0.5 */
_VML_API(void,VMCSQRT,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZSQRT,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcsqrt,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzsqrt,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcSqrt,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzSqrt,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Reciprocal Square Root: r[i] = 1/a[i]^0.5 */
_VML_API(void,VSINVSQRT,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDINVSQRT,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsinvsqrt,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdinvsqrt,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsInvSqrt,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdInvSqrt,(const MKL_INT n,  const double a[], double r[]))

/* Reciprocal Square Root: r[i] = 1/a[i]^0.5 */
_VML_API(void,VMSINVSQRT,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDINVSQRT,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsinvsqrt,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdinvsqrt,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsInvSqrt,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdInvSqrt,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Cube Root: r[i] = a[i]^(1/3) */
_VML_API(void,VSCBRT,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDCBRT,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vscbrt,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdcbrt,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsCbrt,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdCbrt,(const MKL_INT n,  const double a[], double r[]))

/* Cube Root: r[i] = a[i]^(1/3) */
_VML_API(void,VMSCBRT,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDCBRT,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmscbrt,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdcbrt,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsCbrt,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdCbrt,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Reciprocal Cube Root: r[i] = 1/a[i]^(1/3) */
_VML_API(void,VSINVCBRT,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDINVCBRT,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsinvcbrt,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdinvcbrt,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsInvCbrt,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdInvCbrt,(const MKL_INT n,  const double a[], double r[]))

/* Reciprocal Cube Root: r[i] = 1/a[i]^(1/3) */
_VML_API(void,VMSINVCBRT,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDINVCBRT,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsinvcbrt,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdinvcbrt,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsInvCbrt,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdInvCbrt,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Squaring: r[i] = a[i]^2 */
_VML_API(void,VSSQR,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDSQR,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vssqr,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdsqr,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsSqr,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdSqr,(const MKL_INT n,  const double a[], double r[]))

/* Exponential Function: r[i] = e^a[i] */
_VML_API(void,VSEXP,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDEXP,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsexp,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdexp,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsExp,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdExp,(const MKL_INT n,  const double a[], double r[]))

/* Exponential Function: r[i] = e^a[i] */
_VML_API(void,VMSEXP,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDEXP,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsexp,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdexp,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsExp,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdExp,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* : r[i] = e^(a[i]-1) */
_VML_API(void,VSEXPM1,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDEXPM1,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsexpm1,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdexpm1,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsExpm1,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdExpm1,(const MKL_INT n,  const double a[], double r[]))

/* : r[i] = e^(a[i]-1) */
_VML_API(void,VMSEXPM1,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDEXPM1,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsexpm1,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdexpm1,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsExpm1,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdExpm1,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Exponential Function: r[i] = e^a[i] */
_VML_API(void,VCEXP,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZEXP,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcexp,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzexp,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcExp,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzExp,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Exponential Function: r[i] = e^a[i] */
_VML_API(void,VMCEXP,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZEXP,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcexp,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzexp,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcExp,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzExp,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Logarithm (base e): r[i] = ln(a[i]) */
_VML_API(void,VSLN,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDLN,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsln,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdln,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsLn,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdLn,(const MKL_INT n,  const double a[], double r[]))

/* Logarithm (base e): r[i] = ln(a[i]) */
_VML_API(void,VMSLN,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDLN,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsln,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdln,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsLn,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdLn,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Logarithm (base e): r[i] = ln(a[i]) */
_VML_API(void,VCLN,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZLN,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcln,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzln,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcLn,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzLn,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Logarithm (base e): r[i] = ln(a[i]) */
_VML_API(void,VMCLN,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZLN,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcln,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzln,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcLn,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzLn,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Logarithm (base 10): r[i] = lg(a[i]) */
_VML_API(void,VSLOG10,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDLOG10,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vslog10,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdlog10,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsLog10,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdLog10,(const MKL_INT n,  const double a[], double r[]))

/* Logarithm (base 10): r[i] = lg(a[i]) */
_VML_API(void,VMSLOG10,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDLOG10,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmslog10,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdlog10,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsLog10,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdLog10,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Logarithm (base 10): r[i] = lg(a[i]) */
_VML_API(void,VCLOG10,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZLOG10,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vclog10,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzlog10,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcLog10,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzLog10,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Logarithm (base 10): r[i] = lg(a[i]) */
_VML_API(void,VMCLOG10,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZLOG10,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmclog10,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzlog10,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcLog10,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzLog10,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* : r[i] = log(1+a[i]) */
_VML_API(void,VSLOG1P,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDLOG1P,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vslog1p,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdlog1p,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsLog1p,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdLog1p,(const MKL_INT n,  const double a[], double r[]))

/* : r[i] = log(1+a[i]) */
_VML_API(void,VMSLOG1P,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDLOG1P,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmslog1p,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdlog1p,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsLog1p,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdLog1p,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Cosine: r[i] = cos(a[i]) */
_VML_API(void,VSCOS,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDCOS,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vscos,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdcos,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsCos,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdCos,(const MKL_INT n,  const double a[], double r[]))

/* Cosine: r[i] = cos(a[i]) */
_VML_API(void,VMSCOS,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDCOS,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmscos,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdcos,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsCos,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdCos,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Cosine: r[i] = ccos(a[i]) */
_VML_API(void,VCCOS,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZCOS,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vccos,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzcos,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcCos,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzCos,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Cosine: r[i] = ccos(a[i]) */
_VML_API(void,VMCCOS,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZCOS,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmccos,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzcos,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcCos,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzCos,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Sine: r[i] = sin(a[i]) */
_VML_API(void,VSSIN,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDSIN,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vssin,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdsin,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsSin,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdSin,(const MKL_INT n,  const double a[], double r[]))

/* Sine: r[i] = sin(a[i]) */
_VML_API(void,VMSSIN,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDSIN,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmssin,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdsin,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsSin,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdSin,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Sine: r[i] = sin(a[i]) */
_VML_API(void,VCSIN,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZSIN,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcsin,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzsin,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcSin,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzSin,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Sine: r[i] = sin(a[i]) */
_VML_API(void,VMCSIN,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZSIN,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcsin,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzsin,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcSin,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzSin,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Tangent: r[i] = tan(a[i]) */
_VML_API(void,VSTAN,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDTAN,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vstan,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdtan,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsTan,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdTan,(const MKL_INT n,  const double a[], double r[]))

/* Tangent: r[i] = tan(a[i]) */
_VML_API(void,VMSTAN,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDTAN,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmstan,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdtan,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsTan,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdTan,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Tangent: r[i] = tan(a[i]) */
_VML_API(void,VCTAN,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZTAN,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vctan,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vztan,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcTan,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzTan,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Tangent: r[i] = tan(a[i]) */
_VML_API(void,VMCTAN,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZTAN,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmctan,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmztan,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcTan,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzTan,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Hyperbolic Cosine: r[i] = ch(a[i]) */
_VML_API(void,VSCOSH,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDCOSH,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vscosh,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdcosh,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsCosh,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdCosh,(const MKL_INT n,  const double a[], double r[]))

/* Hyperbolic Cosine: r[i] = ch(a[i]) */
_VML_API(void,VMSCOSH,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDCOSH,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmscosh,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdcosh,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsCosh,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdCosh,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Hyperbolic Cosine: r[i] = ch(a[i]) */
_VML_API(void,VCCOSH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZCOSH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vccosh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzcosh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcCosh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzCosh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Hyperbolic Cosine: r[i] = ch(a[i]) */
_VML_API(void,VMCCOSH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZCOSH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmccosh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzcosh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcCosh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzCosh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Hyperbolic Sine: r[i] = sh(a[i]) */
_VML_API(void,VSSINH,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDSINH,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vssinh,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdsinh,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsSinh,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdSinh,(const MKL_INT n,  const double a[], double r[]))

/* Hyperbolic Sine: r[i] = sh(a[i]) */
_VML_API(void,VMSSINH,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDSINH,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmssinh,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdsinh,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsSinh,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdSinh,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Hyperbolic Sine: r[i] = sh(a[i]) */
_VML_API(void,VCSINH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZSINH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcsinh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzsinh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcSinh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzSinh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Hyperbolic Sine: r[i] = sh(a[i]) */
_VML_API(void,VMCSINH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZSINH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcsinh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzsinh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcSinh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzSinh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Hyperbolic Tangent: r[i] = th(a[i]) */
_VML_API(void,VSTANH,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDTANH,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vstanh,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdtanh,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsTanh,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdTanh,(const MKL_INT n,  const double a[], double r[]))

/* Hyperbolic Tangent: r[i] = th(a[i]) */
_VML_API(void,VMSTANH,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDTANH,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmstanh,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdtanh,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsTanh,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdTanh,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Hyperbolic Tangent: r[i] = th(a[i]) */
_VML_API(void,VCTANH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZTANH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vctanh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vztanh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcTanh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzTanh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Hyperbolic Tangent: r[i] = th(a[i]) */
_VML_API(void,VMCTANH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZTANH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmctanh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmztanh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcTanh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzTanh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Arc Cosine: r[i] = arccos(a[i]) */
_VML_API(void,VSACOS,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDACOS,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsacos,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdacos,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsAcos,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdAcos,(const MKL_INT n,  const double a[], double r[]))

/* Arc Cosine: r[i] = arccos(a[i]) */
_VML_API(void,VMSACOS,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDACOS,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsacos,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdacos,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsAcos,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdAcos,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Arc Cosine: r[i] = arccos(a[i]) */
_VML_API(void,VCACOS,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZACOS,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcacos,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzacos,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcAcos,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzAcos,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Arc Cosine: r[i] = arccos(a[i]) */
_VML_API(void,VMCACOS,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZACOS,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcacos,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzacos,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcAcos,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzAcos,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Arc Sine: r[i] = arcsin(a[i]) */
_VML_API(void,VSASIN,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDASIN,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsasin,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdasin,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsAsin,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdAsin,(const MKL_INT n,  const double a[], double r[]))

/* Arc Sine: r[i] = arcsin(a[i]) */
_VML_API(void,VMSASIN,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDASIN,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsasin,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdasin,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsAsin,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdAsin,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Arc Sine: r[i] = arcsin(a[i]) */
_VML_API(void,VCASIN,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZASIN,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcasin,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzasin,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcAsin,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzAsin,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Arc Sine: r[i] = arcsin(a[i]) */
_VML_API(void,VMCASIN,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZASIN,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcasin,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzasin,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcAsin,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzAsin,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Arc Tangent: r[i] = arctan(a[i]) */
_VML_API(void,VSATAN,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDATAN,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsatan,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdatan,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsAtan,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdAtan,(const MKL_INT n,  const double a[], double r[]))

/* Arc Tangent: r[i] = arctan(a[i]) */
_VML_API(void,VMSATAN,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDATAN,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsatan,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdatan,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsAtan,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdAtan,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Arc Tangent: r[i] = arctan(a[i]) */
_VML_API(void,VCATAN,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZATAN,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcatan,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzatan,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcAtan,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzAtan,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Arc Tangent: r[i] = arctan(a[i]) */
_VML_API(void,VMCATAN,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZATAN,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcatan,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzatan,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcAtan,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzAtan,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Hyperbolic Arc Cosine: r[i] = arcch(a[i]) */
_VML_API(void,VSACOSH,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDACOSH,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsacosh,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdacosh,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsAcosh,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdAcosh,(const MKL_INT n,  const double a[], double r[]))

/* Hyperbolic Arc Cosine: r[i] = arcch(a[i]) */
_VML_API(void,VMSACOSH,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDACOSH,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsacosh,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdacosh,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsAcosh,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdAcosh,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Hyperbolic Arc Cosine: r[i] = arcch(a[i]) */
_VML_API(void,VCACOSH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZACOSH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcacosh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzacosh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcAcosh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzAcosh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Hyperbolic Arc Cosine: r[i] = arcch(a[i]) */
_VML_API(void,VMCACOSH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZACOSH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcacosh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzacosh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcAcosh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzAcosh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Hyperbolic Arc Sine: r[i] = arcsh(a[i]) */
_VML_API(void,VSASINH,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDASINH,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsasinh,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdasinh,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsAsinh,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdAsinh,(const MKL_INT n,  const double a[], double r[]))

/* Hyperbolic Arc Sine: r[i] = arcsh(a[i]) */
_VML_API(void,VMSASINH,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDASINH,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsasinh,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdasinh,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsAsinh,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdAsinh,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Hyperbolic Arc Sine: r[i] = arcsh(a[i]) */
_VML_API(void,VCASINH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZASINH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcasinh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzasinh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcAsinh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzAsinh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Hyperbolic Arc Sine: r[i] = arcsh(a[i]) */
_VML_API(void,VMCASINH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZASINH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcasinh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzasinh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcAsinh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzAsinh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/* Hyperbolic Arc Tangent: r[i] = arcth(a[i]) */
_VML_API(void,VSATANH,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDATANH,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsatanh,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdatanh,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsAtanh,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdAtanh,(const MKL_INT n,  const double a[], double r[]))

/* Hyperbolic Arc Tangent: r[i] = arcth(a[i]) */
_VML_API(void,VMSATANH,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDATANH,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsatanh,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdatanh,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsAtanh,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdAtanh,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Complex Hyperbolic Arc Tangent: r[i] = arcth(a[i]) */
_VML_API(void,VCATANH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZATANH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcatanh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzatanh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcAtanh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzAtanh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* Complex Hyperbolic Arc Tangent: r[i] = arcth(a[i]) */
_VML_API(void,VMCATANH,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZATANH,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcatanh,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzatanh,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcAtanh,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzAtanh,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[], MKL_INT64 mode))

/*  Error Function: r[i] = erf(a[i]) */
_VML_API(void,VSERF,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDERF,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vserf,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vderf,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsErf,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdErf,(const MKL_INT n,  const double a[], double r[]))

/*  Error Function: r[i] = erf(a[i]) */
_VML_API(void,VMSERF,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDERF,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmserf,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmderf,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsErf,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdErf,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/*  Inverse Error Function: r[i] = erf(a[i]) */
_VML_API(void,VSERFINV,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDERFINV,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vserfinv,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vderfinv,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsErfInv,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdErfInv,(const MKL_INT n,  const double a[], double r[]))

/*  Inverse Error Function: r[i] = erf(a[i]) */
_VML_API(void,VMSERFINV,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDERFINV,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmserfinv,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmderfinv,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsErfInv,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdErfInv,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/*   */
_VML_API(void,VSHYPOT,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_VML_API(void,VDHYPOT,(const MKL_INT *n, const double a[], const double b[], double r[]))
_vml_api(void,vshypot,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_vml_api(void,vdhypot,(const MKL_INT *n, const double a[], const double b[], double r[]))
_Vml_Api(void,vsHypot,(const MKL_INT n,  const float  a[], const float  b[], float  r[]))
_Vml_Api(void,vdHypot,(const MKL_INT n,  const double a[], const double b[], double r[]))

/*   */
_VML_API(void,VMSHYPOT,(const MKL_INT *n, const float  a[], const float  b[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDHYPOT,(const MKL_INT *n, const double a[], const double b[], double r[], MKL_INT64 *mode))
_vml_api(void,vmshypot,(const MKL_INT *n, const float  a[], const float  b[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdhypot,(const MKL_INT *n, const double a[], const double b[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsHypot,(const MKL_INT n,  const float  a[], const float  b[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdHypot,(const MKL_INT n,  const double a[], const double b[], double r[], MKL_INT64 mode))

/*  Complementary Error Function: r[i] = 1 - erf(a[i]) */
_VML_API(void,VSERFC,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDERFC,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vserfc,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vderfc,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsErfc,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdErfc,(const MKL_INT n,  const double a[], double r[]))

/*  Complementary Error Function: r[i] = 1 - erf(a[i]) */
_VML_API(void,VMSERFC,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDERFC,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmserfc,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmderfc,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsErfc,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdErfc,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/*   */
_VML_API(void,VSERFCINV,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDERFCINV,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vserfcinv,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vderfcinv,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsErfcInv,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdErfcInv,(const MKL_INT n,  const double a[], double r[]))

/*   */
_VML_API(void,VMSERFCINV,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDERFCINV,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmserfcinv,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmderfcinv,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsErfcInv,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdErfcInv,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/*   */
_VML_API(void,VSCDFNORM,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDCDFNORM,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vscdfnorm,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdcdfnorm,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsCdfNorm,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdCdfNorm,(const MKL_INT n,  const double a[], double r[]))

/*   */
_VML_API(void,VMSCDFNORM,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDCDFNORM,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmscdfnorm,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdcdfnorm,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsCdfNorm,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdCdfNorm,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/*   */
_VML_API(void,VSCDFNORMINV,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDCDFNORMINV,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vscdfnorminv,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdcdfnorminv,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsCdfNormInv,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdCdfNormInv,(const MKL_INT n,  const double a[], double r[]))

/*   */
_VML_API(void,VMSCDFNORMINV,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDCDFNORMINV,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmscdfnorminv,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdcdfnorminv,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsCdfNormInv,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdCdfNormInv,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* LGamma  */
_VML_API(void,VSLGAMMA,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDLGAMMA,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vslgamma,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdlgamma,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsLGamma,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdLGamma,(const MKL_INT n,  const double a[], double r[]))

_VML_API(void,VMSLGAMMA,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDLGAMMA,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmslgamma,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdlgamma,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsLGamma,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdLGamma,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* TGamma  */
_VML_API(void,VSTGAMMA,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDTGAMMA,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vstgamma,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdtgamma,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsTGamma,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdTGamma,(const MKL_INT n,  const double a[], double r[]))

_VML_API(void,VMSTGAMMA,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDTGAMMA,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmstgamma,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdtgamma,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsTGamma,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdTGamma,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Arc Tangent of a/b: r[i] = arctan(a[i]/b[i]) */
_VML_API(void,VSATAN2,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_VML_API(void,VDATAN2,(const MKL_INT *n, const double a[], const double b[], double r[]))
_vml_api(void,vsatan2,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_vml_api(void,vdatan2,(const MKL_INT *n, const double a[], const double b[], double r[]))
_Vml_Api(void,vsAtan2,(const MKL_INT n,  const float  a[], const float  b[], float  r[]))
_Vml_Api(void,vdAtan2,(const MKL_INT n,  const double a[], const double b[], double r[]))

/* Arc Tangent of a/b: r[i] = arctan(a[i]/b[i]) */
_VML_API(void,VMSATAN2,(const MKL_INT *n, const float  a[], const float  b[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDATAN2,(const MKL_INT *n, const double a[], const double b[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsatan2,(const MKL_INT *n, const float  a[], const float  b[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdatan2,(const MKL_INT *n, const double a[], const double b[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsAtan2,(const MKL_INT n,  const float  a[], const float  b[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdAtan2,(const MKL_INT n,  const double a[], const double b[], double r[], MKL_INT64 mode))

/* Multiplicaton: r[i] = a[i] * b[i] */
_VML_API(void,VSMUL,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_VML_API(void,VDMUL,(const MKL_INT *n, const double a[], const double b[], double r[]))
_vml_api(void,vsmul,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_vml_api(void,vdmul,(const MKL_INT *n, const double a[], const double b[], double r[]))
_Vml_Api(void,vsMul,(const MKL_INT n,  const float  a[], const float  b[], float  r[]))
_Vml_Api(void,vdMul,(const MKL_INT n,  const double a[], const double b[], double r[]))

/* Complex multiplication: r[i] = a[i] * b[i] */
_VML_API(void,VCMUL,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_VML_API(void,VZMUL,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_vml_api(void,vcmul,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_vml_api(void,vzmul,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_Vml_Api(void,vcMul,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_Vml_Api(void,vzMul,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))

/* Complex multiplication: r[i] = a[i] * b[i] */
_VML_API(void,VMCMUL,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZMUL,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcmul,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzmul,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcMul,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzMul,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 mode))

/* Division: r[i] = a[i] / b[i] */
_VML_API(void,VSDIV,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_VML_API(void,VDDIV,(const MKL_INT *n, const double a[], const double b[], double r[]))
_vml_api(void,vsdiv,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_vml_api(void,vddiv,(const MKL_INT *n, const double a[], const double b[], double r[]))
_Vml_Api(void,vsDiv,(const MKL_INT n,  const float  a[], const float  b[], float  r[]))
_Vml_Api(void,vdDiv,(const MKL_INT n,  const double a[], const double b[], double r[]))

/* Division: r[i] = a[i] / b[i] */
_VML_API(void,VMSDIV,(const MKL_INT *n, const float  a[], const float  b[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDDIV,(const MKL_INT *n, const double a[], const double b[], double r[], MKL_INT64 *mode))
_vml_api(void,vmsdiv,(const MKL_INT *n, const float  a[], const float  b[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmddiv,(const MKL_INT *n, const double a[], const double b[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsDiv,(const MKL_INT n,  const float  a[], const float  b[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdDiv,(const MKL_INT n,  const double a[], const double b[], double r[], MKL_INT64 mode))

/* Complex division: r[i] = a[i] / b[i] */
_VML_API(void,VCDIV,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_VML_API(void,VZDIV,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_vml_api(void,vcdiv,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_vml_api(void,vzdiv,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_Vml_Api(void,vcDiv,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_Vml_Api(void,vzDiv,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))

/* Complex division: r[i] = a[i] / b[i] */
_VML_API(void,VMCDIV,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZDIV,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcdiv,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzdiv,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcDiv,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzDiv,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 mode))

/* Power Function: r[i] = a[i]^b[i] */
_VML_API(void,VSPOW,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_VML_API(void,VDPOW,(const MKL_INT *n, const double a[], const double b[], double r[]))
_vml_api(void,vspow,(const MKL_INT *n, const float  a[], const float  b[], float  r[]))
_vml_api(void,vdpow,(const MKL_INT *n, const double a[], const double b[], double r[]))
_Vml_Api(void,vsPow,(const MKL_INT n,  const float  a[], const float  b[], float  r[]))
_Vml_Api(void,vdPow,(const MKL_INT n,  const double a[], const double b[], double r[]))

/* Power Function: r[i] = a[i]^b[i] */
_VML_API(void,VMSPOW,(const MKL_INT *n, const float  a[], const float  b[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDPOW,(const MKL_INT *n, const double a[], const double b[], double r[], MKL_INT64 *mode))
_vml_api(void,vmspow,(const MKL_INT *n, const float  a[], const float  b[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdpow,(const MKL_INT *n, const double a[], const double b[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsPow,(const MKL_INT n,  const float  a[], const float  b[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdPow,(const MKL_INT n,  const double a[], const double b[], double r[], MKL_INT64 mode))

/* Complex Power Function: r[i] = a[i]^b[i] */
_VML_API(void,VCPOW,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_VML_API(void,VZPOW,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_vml_api(void,vcpow,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_vml_api(void,vzpow,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_Vml_Api(void,vcPow,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_Vml_Api(void,vzPow,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))

/* Complex Power Function: r[i] = a[i]^b[i] */
_VML_API(void,VMCPOW,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZPOW,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcpow,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzpow,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcPow,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzPow,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 mode))

/* Power Function: r[i] = a[i]^(3/2) */
_VML_API(void,VSPOW3O2,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDPOW3O2,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vspow3o2,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdpow3o2,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsPow3o2,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdPow3o2,(const MKL_INT n,  const double a[], double r[]))

/* Power Function: r[i] = a[i]^(3/2) */
_VML_API(void,VMSPOW3O2,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDPOW3O2,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmspow3o2,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdpow3o2,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsPow3o2,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdPow3o2,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Power Function: r[i] = a[i]^(2/3) */
_VML_API(void,VSPOW2O3,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDPOW2O3,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vspow2o3,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdpow2o3,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsPow2o3,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdPow2o3,(const MKL_INT n,  const double a[], double r[]))

/* Power Function: r[i] = a[i]^(2/3) */
_VML_API(void,VMSPOW2O3,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_VML_API(void,VMDPOW2O3,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_vml_api(void,vmspow2o3,(const MKL_INT *n, const float  a[], float  r[], MKL_INT64 *mode))
_vml_api(void,vmdpow2o3,(const MKL_INT *n, const double a[], double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsPow2o3,(const MKL_INT n,  const float  a[], float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdPow2o3,(const MKL_INT n,  const double a[], double r[], MKL_INT64 mode))

/* Power Function with Fixed Degree: r[i] = a[i]^b */
_VML_API(void,VSPOWX,(const MKL_INT *n, const float  a[], const float  *b, float  r[]))
_VML_API(void,VDPOWX,(const MKL_INT *n, const double a[], const double *b, double r[]))
_vml_api(void,vspowx,(const MKL_INT *n, const float  a[], const float  *b, float  r[]))
_vml_api(void,vdpowx,(const MKL_INT *n, const double a[], const double *b, double r[]))
_Vml_Api(void,vsPowx,(const MKL_INT n,  const float  a[], const float   b, float  r[]))
_Vml_Api(void,vdPowx,(const MKL_INT n,  const double a[], const double  b, double r[]))

/* Power Function with Fixed Degree: r[i] = a[i]^b */
_VML_API(void,VMSPOWX,(const MKL_INT *n, const float  a[], const float  *b, float  r[], MKL_INT64 *mode))
_VML_API(void,VMDPOWX,(const MKL_INT *n, const double a[], const double *b, double r[], MKL_INT64 *mode))
_vml_api(void,vmspowx,(const MKL_INT *n, const float  a[], const float  *b, float  r[], MKL_INT64 *mode))
_vml_api(void,vmdpowx,(const MKL_INT *n, const double a[], const double *b, double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsPowx,(const MKL_INT n,  const float  a[], const float   b, float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdPowx,(const MKL_INT n,  const double a[], const double  b, double r[], MKL_INT64 mode))

/* Complex Power Function with Fixed Degree: r[i] = a[i]^b */
_VML_API(void,VCPOWX,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  *b, MKL_Complex8  r[]))
_VML_API(void,VZPOWX,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 *b, MKL_Complex16 r[]))
_vml_api(void,vcpowx,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  *b, MKL_Complex8  r[]))
_vml_api(void,vzpowx,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 *b, MKL_Complex16 r[]))
_Vml_Api(void,vcPowx,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8   b, MKL_Complex8  r[]))
_Vml_Api(void,vzPowx,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16  b, MKL_Complex16 r[]))

/* Complex Power Function with Fixed Degree: r[i] = a[i]^b */
_VML_API(void,VMCPOWX,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  *b, MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZPOWX,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 *b, MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcpowx,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  *b, MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzpowx,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 *b, MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcPowx,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8   b, MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzPowx,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16  b, MKL_Complex16 r[], MKL_INT64 mode))

/* Sine & Cosine: r1[i] = sin(a[i]), r2[i]=cos(a[i]) */
_VML_API(void,VSSINCOS,(const MKL_INT *n, const float  a[], float  r1[], float  r2[]))
_VML_API(void,VDSINCOS,(const MKL_INT *n, const double a[], double r1[], double r2[]))
_vml_api(void,vssincos,(const MKL_INT *n, const float  a[], float  r1[], float  r2[]))
_vml_api(void,vdsincos,(const MKL_INT *n, const double a[], double r1[], double r2[]))
_Vml_Api(void,vsSinCos,(const MKL_INT n,  const float  a[], float  r1[], float  r2[]))
_Vml_Api(void,vdSinCos,(const MKL_INT n,  const double a[], double r1[], double r2[]))

/* Sine & Cosine: r1[i] = sin(a[i]), r2[i]=cos(a[i]) */
_VML_API(void,VMSSINCOS,(const MKL_INT *n, const float  a[], float  r1[], float  r2[], MKL_INT64 *mode))
_VML_API(void,VMDSINCOS,(const MKL_INT *n, const double a[], double r1[], double r2[], MKL_INT64 *mode))
_vml_api(void,vmssincos,(const MKL_INT *n, const float  a[], float  r1[], float  r2[], MKL_INT64 *mode))
_vml_api(void,vmdsincos,(const MKL_INT *n, const double a[], double r1[], double r2[], MKL_INT64 *mode))
_Vml_Api(void,vmsSinCos,(const MKL_INT n,  const float  a[], float  r1[], float  r2[], MKL_INT64 mode))
_Vml_Api(void,vmdSinCos,(const MKL_INT n,  const double a[], double r1[], double r2[], MKL_INT64 mode))

/* Linear Fraction: r[i] = (a[i]*scalea + shifta)/(b[i]*scaleb + shiftb) */
_VML_API(void,VSLINEARFRAC,(const MKL_INT *n, const float  a[], const float  b[], const float  *scalea, const float  *shifta, const float  *scaleb, const float  *shiftb, float  r[]))
_VML_API(void,VDLINEARFRAC,(const MKL_INT *n, const double a[], const double b[], const double *scalea, const double *shifta, const double *scaleb, const double *shiftb, double r[]))
_vml_api(void,vslinearfrac,(const MKL_INT *n, const float  a[], const float  b[], const float  *scalea, const float  *shifta, const float  *scaleb, const float  *shiftb, float  r[]))
_vml_api(void,vdlinearfrac,(const MKL_INT *n, const double a[], const double b[], const double *scalea, const double *shifta, const double *scaleb, const double *shiftb, double r[]))
_Vml_Api(void,vsLinearFrac,(const MKL_INT n,  const float  a[], const float  b[], const float  scalea, const float  shifta, const float  scaleb, const float  shiftb, float  r[]))
_Vml_Api(void,vdLinearFrac,(const MKL_INT n,  const double a[], const double b[], const double scalea, const double shifta, const double scaleb, const double shiftb, double r[]))

/* Linear Fraction: r[i] = (a[i]*scalea + shifta)/(b[i]*scaleb + shiftb) */
_VML_API(void,VMSLINEARFRAC,(const MKL_INT *n, const float  a[], const float  b[], const float  *scalea, const float  *shifta, const float  *scaleb, const float  *shiftb, float  r[], MKL_INT64 *mode))
_VML_API(void,VMDLINEARFRAC,(const MKL_INT *n, const double a[], const double b[], const double *scalea, const double *shifta, const double *scaleb, const double *shiftb, double r[], MKL_INT64 *mode))
_vml_api(void,vmslinearfrac,(const MKL_INT *n, const float  a[], const float  b[], const float  *scalea, const float  *shifta, const float  *scaleb, const float  *shiftb, float  r[], MKL_INT64 *mode))
_vml_api(void,vmdlinearfrac,(const MKL_INT *n, const double a[], const double b[], const double *scalea, const double *shifta, const double *scaleb, const double *shiftb, double r[], MKL_INT64 *mode))
_Vml_Api(void,vmsLinearFrac,(const MKL_INT n,  const float  a[], const float  b[], const float  scalea, const float  shifta, const float  scaleb, const float  shiftb, float  r[], MKL_INT64 mode))
_Vml_Api(void,vmdLinearFrac,(const MKL_INT n,  const double a[], const double b[], const double scalea, const double shifta, const double scaleb, const double shiftb, double r[], MKL_INT64 mode))

/*  */
_VML_API(void,VSCEIL,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDCEIL,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsceil,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdceil,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsCeil,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdCeil,(const MKL_INT n,  const double a[], double r[]))

/*  */
_VML_API(void,VSFLOOR,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDFLOOR,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsfloor,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdfloor,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsFloor,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdFloor,(const MKL_INT n,  const double a[], double r[]))

/*  */
_VML_API(void,VSMODF,(const MKL_INT *n, const float  a[], float  r1[], float  r2[]))
_VML_API(void,VDMODF,(const MKL_INT *n, const double a[], double r1[], double r2[]))
_vml_api(void,vsmodf,(const MKL_INT *n, const float  a[], float  r1[], float  r2[]))
_vml_api(void,vdmodf,(const MKL_INT *n, const double a[], double r1[], double r2[]))
_Vml_Api(void,vsModf,(const MKL_INT n,  const float  a[], float  r1[], float  r2[]))
_Vml_Api(void,vdModf,(const MKL_INT n,  const double a[], double r1[], double r2[]))

/*  */
_VML_API(void,VSNEARBYINT,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDNEARBYINT,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsnearbyint,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdnearbyint,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsNearbyInt,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdNearbyInt,(const MKL_INT n,  const double a[], double r[]))

/*  */
_VML_API(void,VSRINT,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDRINT,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsrint,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdrint,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsRint,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdRint,(const MKL_INT n,  const double a[], double r[]))

/*  */
_VML_API(void,VSROUND,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDROUND,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vsround,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdround,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsRound,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdRound,(const MKL_INT n,  const double a[], double r[]))

/*  */
_VML_API(void,VSTRUNC,(const MKL_INT *n, const float  a[], float  r[]))
_VML_API(void,VDTRUNC,(const MKL_INT *n, const double a[], double r[]))
_vml_api(void,vstrunc,(const MKL_INT *n, const float  a[], float  r[]))
_vml_api(void,vdtrunc,(const MKL_INT *n, const double a[], double r[]))
_Vml_Api(void,vsTrunc,(const MKL_INT n,  const float  a[], float  r[]))
_Vml_Api(void,vdTrunc,(const MKL_INT n,  const double a[], double r[]))

/* : r[i] =  */
_VML_API(void,VCCONJ,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_VML_API(void,VZCONJ,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_vml_api(void,vcconj,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  r[]))
_vml_api(void,vzconj,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 r[]))
_Vml_Api(void,vcConj,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzConj,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 r[]))

/* : r[i] =  */
_VML_API(void,VCMULBYCONJ,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_VML_API(void,VZMULBYCONJ,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_vml_api(void,vcmulbyconj,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_vml_api(void,vzmulbyconj,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))
_Vml_Api(void,vcMulByConj,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[]))
_Vml_Api(void,vzMulByConj,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[]))

/* : r[i] =  */
_VML_API(void,VMCMULBYCONJ,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZMULBYCONJ,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmcmulbyconj,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzmulbyconj,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcMulByConj,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_Complex8  b[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzMulByConj,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_Complex16 b[], MKL_Complex16 r[], MKL_INT64 mode))

/* : r[i] =  */
_VML_API(void,VCCIS,(const MKL_INT *n, const float  a[], MKL_Complex8  r[]))
_VML_API(void,VZCIS,(const MKL_INT *n, const double a[], MKL_Complex16 r[]))
_vml_api(void,vccis,(const MKL_INT *n, const float  a[], MKL_Complex8  r[]))
_vml_api(void,vzcis,(const MKL_INT *n, const double a[], MKL_Complex16 r[]))
_Vml_Api(void,vcCIS,(const MKL_INT n,  const float  a[], MKL_Complex8  r[]))
_Vml_Api(void,vzCIS,(const MKL_INT n,  const double a[], MKL_Complex16 r[]))

/* : r[i] =  */
_VML_API(void,VMCCIS,(const MKL_INT *n, const float  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_VML_API(void,VMZCIS,(const MKL_INT *n, const double a[], MKL_Complex16 r[], MKL_INT64 *mode))
_vml_api(void,vmccis,(const MKL_INT *n, const float  a[], MKL_Complex8  r[], MKL_INT64 *mode))
_vml_api(void,vmzcis,(const MKL_INT *n, const double a[], MKL_Complex16 r[], MKL_INT64 *mode))
_Vml_Api(void,vmcCIS,(const MKL_INT n,  const float  a[], MKL_Complex8  r[], MKL_INT64 mode))
_Vml_Api(void,vmzCIS,(const MKL_INT n,  const double a[], MKL_Complex16 r[], MKL_INT64 mode))

/*
//++
//  VML PACK FUNCTION DECLARATIONS.
//--
*/
/* Positive Increment Indexing */
_VML_API(void,VSPACKI,(const MKL_INT *n, const float  a[], const MKL_INT * incra, float  y[]))
_VML_API(void,VDPACKI,(const MKL_INT *n, const double a[], const MKL_INT * incra, double y[]))
_vml_api(void,vspacki,(const MKL_INT *n, const float  a[], const MKL_INT * incra, float  y[]))
_vml_api(void,vdpacki,(const MKL_INT *n, const double a[], const MKL_INT * incra, double y[]))
_Vml_Api(void,vsPackI,(const MKL_INT n,  const float  a[], const MKL_INT   incra, float  y[]))
_Vml_Api(void,vdPackI,(const MKL_INT n,  const double a[], const MKL_INT   incra, double y[]))

_VML_API(void,VCPACKI,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_INT * incra, MKL_Complex8  y[]))
_VML_API(void,VZPACKI,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_INT * incra, MKL_Complex16 y[]))
_vml_api(void,vcpacki,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_INT * incra, MKL_Complex8  y[]))
_vml_api(void,vzpacki,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_INT * incra, MKL_Complex16 y[]))
_Vml_Api(void,vcPackI,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_INT   incra, MKL_Complex8  y[]))
_Vml_Api(void,vzPackI,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_INT   incra, MKL_Complex16 y[]))

/* Index Vector Indexing */
_VML_API(void,VSPACKV,(const MKL_INT *n, const float  a[], const MKL_INT ia[], float  y[]))
_VML_API(void,VDPACKV,(const MKL_INT *n, const double a[], const MKL_INT ia[], double y[]))
_vml_api(void,vspackv,(const MKL_INT *n, const float  a[], const MKL_INT ia[], float  y[]))
_vml_api(void,vdpackv,(const MKL_INT *n, const double a[], const MKL_INT ia[], double y[]))
_Vml_Api(void,vsPackV,(const MKL_INT n,  const float  a[], const MKL_INT ia[], float  y[]))
_Vml_Api(void,vdPackV,(const MKL_INT n,  const double a[], const MKL_INT ia[], double y[]))

_VML_API(void,VCPACKV,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_INT ia[], MKL_Complex8  y[]))
_VML_API(void,VZPACKV,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_INT ia[], MKL_Complex16 y[]))
_vml_api(void,vcpackv,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_INT ia[], MKL_Complex8  y[]))
_vml_api(void,vzpackv,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_INT ia[], MKL_Complex16 y[]))
_Vml_Api(void,vcPackV,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_INT ia[], MKL_Complex8  y[]))
_Vml_Api(void,vzPackV,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_INT ia[], MKL_Complex16 y[]))

/* Mask Vector Indexing */
_VML_API(void,VSPACKM,(const MKL_INT *n, const float  a[], const MKL_INT ma[], float  y[]))
_VML_API(void,VDPACKM,(const MKL_INT *n, const double a[], const MKL_INT ma[], double y[]))
_vml_api(void,vspackm,(const MKL_INT *n, const float  a[], const MKL_INT ma[], float  y[]))
_vml_api(void,vdpackm,(const MKL_INT *n, const double a[], const MKL_INT ma[], double y[]))
_Vml_Api(void,vsPackM,(const MKL_INT n,  const float  a[], const MKL_INT ma[], float  y[]))
_Vml_Api(void,vdPackM,(const MKL_INT n,  const double a[], const MKL_INT ma[], double y[]))

_VML_API(void,VCPACKM,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_INT ma[], MKL_Complex8  y[]))
_VML_API(void,VZPACKM,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_INT ma[], MKL_Complex16 y[]))
_vml_api(void,vcpackm,(const MKL_INT *n, const MKL_Complex8  a[], const MKL_INT ma[], MKL_Complex8  y[]))
_vml_api(void,vzpackm,(const MKL_INT *n, const MKL_Complex16 a[], const MKL_INT ma[], MKL_Complex16 y[]))
_Vml_Api(void,vcPackM,(const MKL_INT n,  const MKL_Complex8  a[], const MKL_INT ma[], MKL_Complex8  y[]))
_Vml_Api(void,vzPackM,(const MKL_INT n,  const MKL_Complex16 a[], const MKL_INT ma[], MKL_Complex16 y[]))

/*
//++
//  VML UNPACK FUNCTION DECLARATIONS.
//--
*/
/* Positive Increment Indexing */
_VML_API(void,VSUNPACKI,(const MKL_INT *n, const float  a[], float  y[], const MKL_INT * incry))
_VML_API(void,VDUNPACKI,(const MKL_INT *n, const double a[], double y[], const MKL_INT * incry))
_vml_api(void,vsunpacki,(const MKL_INT *n, const float  a[], float  y[], const MKL_INT * incry))
_vml_api(void,vdunpacki,(const MKL_INT *n, const double a[], double y[], const MKL_INT * incry))
_Vml_Api(void,vsUnpackI,(const MKL_INT n,  const float  a[], float  y[], const MKL_INT incry  ))
_Vml_Api(void,vdUnpackI,(const MKL_INT n,  const double a[], double y[], const MKL_INT incry  ))

_VML_API(void,VCUNPACKI,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  y[], const MKL_INT * incry))
_VML_API(void,VZUNPACKI,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 y[], const MKL_INT * incry))
_vml_api(void,vcunpacki,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  y[], const MKL_INT * incry))
_vml_api(void,vzunpacki,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 y[], const MKL_INT * incry))
_Vml_Api(void,vcUnpackI,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  y[], const MKL_INT incry  ))
_Vml_Api(void,vzUnpackI,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 y[], const MKL_INT incry  ))

/* Index Vector Indexing */
_VML_API(void,VSUNPACKV,(const MKL_INT *n, const float  a[], float  y[], const MKL_INT iy[]   ))
_VML_API(void,VDUNPACKV,(const MKL_INT *n, const double a[], double y[], const MKL_INT iy[]   ))
_vml_api(void,vsunpackv,(const MKL_INT *n, const float  a[], float  y[], const MKL_INT iy[]   ))
_vml_api(void,vdunpackv,(const MKL_INT *n, const double a[], double y[], const MKL_INT iy[]   ))
_Vml_Api(void,vsUnpackV,(const MKL_INT n,  const float  a[], float  y[], const MKL_INT iy[]   ))
_Vml_Api(void,vdUnpackV,(const MKL_INT n,  const double a[], double y[], const MKL_INT iy[]   ))

_VML_API(void,VCUNPACKV,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  y[], const MKL_INT iy[]))
_VML_API(void,VZUNPACKV,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 y[], const MKL_INT iy[]))
_vml_api(void,vcunpackv,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  y[], const MKL_INT iy[]))
_vml_api(void,vzunpackv,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 y[], const MKL_INT iy[]))
_Vml_Api(void,vcUnpackV,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  y[], const MKL_INT iy[]))
_Vml_Api(void,vzUnpackV,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 y[], const MKL_INT iy[]))

/* Mask Vector Indexing */
_VML_API(void,VSUNPACKM,(const MKL_INT *n, const float  a[], float  y[], const MKL_INT my[]   ))
_VML_API(void,VDUNPACKM,(const MKL_INT *n, const double a[], double y[], const MKL_INT my[]   ))
_vml_api(void,vsunpackm,(const MKL_INT *n, const float  a[], float  y[], const MKL_INT my[]   ))
_vml_api(void,vdunpackm,(const MKL_INT *n, const double a[], double y[], const MKL_INT my[]   ))
_Vml_Api(void,vsUnpackM,(const MKL_INT n,  const float  a[], float  y[], const MKL_INT my[]   ))
_Vml_Api(void,vdUnpackM,(const MKL_INT n,  const double a[], double y[], const MKL_INT my[]   ))

_VML_API(void,VCUNPACKM,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  y[], const MKL_INT my[]))
_VML_API(void,VZUNPACKM,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 y[], const MKL_INT my[]))
_vml_api(void,vcunpackm,(const MKL_INT *n, const MKL_Complex8  a[], MKL_Complex8  y[], const MKL_INT my[]))
_vml_api(void,vzunpackm,(const MKL_INT *n, const MKL_Complex16 a[], MKL_Complex16 y[], const MKL_INT my[]))
_Vml_Api(void,vcUnpackM,(const MKL_INT n,  const MKL_Complex8  a[], MKL_Complex8  y[], const MKL_INT my[]))
_Vml_Api(void,vzUnpackM,(const MKL_INT n,  const MKL_Complex16 a[], MKL_Complex16 y[], const MKL_INT my[]))


/*
//++
//  VML ERROR HANDLING FUNCTION DECLARATIONS.
//--
*/
/* Set VML Error Status */
_VML_API(int,VMLSETERRSTATUS,(const MKL_INT * status))
_vml_api(int,vmlseterrstatus,(const MKL_INT * status))
_Vml_Api(int,vmlSetErrStatus,(const MKL_INT   status))

/* Get VML Error Status */
_VML_API(int,VMLGETERRSTATUS,(void))
_vml_api(int,vmlgeterrstatus,(void))
_Vml_Api(int,vmlGetErrStatus,(void))

/* Clear VML Error Status */
_VML_API(int,VMLCLEARERRSTATUS,(void))
_vml_api(int,vmlclearerrstatus,(void))
_Vml_Api(int,vmlClearErrStatus,(void))

/* Set VML Error Callback Function */
_VML_API(VMLErrorCallBack,VMLSETERRORCALLBACK,(const VMLErrorCallBack func))
_vml_api(VMLErrorCallBack,vmlseterrorcallback,(const VMLErrorCallBack func))
_Vml_Api(VMLErrorCallBack,vmlSetErrorCallBack,(const VMLErrorCallBack func))

/* Get VML Error Callback Function */
_VML_API(VMLErrorCallBack,VMLGETERRORCALLBACK,(void))
_vml_api(VMLErrorCallBack,vmlgeterrorcallback,(void))
_Vml_Api(VMLErrorCallBack,vmlGetErrorCallBack,(void))

/* Reset VML Error Callback Function */
_VML_API(VMLErrorCallBack,VMLCLEARERRORCALLBACK,(void))
_vml_api(VMLErrorCallBack,vmlclearerrorcallback,(void))
_Vml_Api(VMLErrorCallBack,vmlClearErrorCallBack,(void))


/*
//++
//  VML MODE FUNCTION DECLARATIONS.
//--
*/
/* Set VML Mode */
_VML_API(unsigned int,VMLSETMODE,(const MKL_UINT *newmode))
_vml_api(unsigned int,vmlsetmode,(const MKL_UINT *newmode))
_Vml_Api(unsigned int,vmlSetMode,(const MKL_UINT  newmode))

/* Get VML Mode */
_VML_API(unsigned int,VMLGETMODE,(void))
_vml_api(unsigned int,vmlgetmode,(void))
_Vml_Api(unsigned int,vmlGetMode,(void))

_VML_API(void,MKLFREETLS,(const MKL_UINT *fdwReason))
_vml_api(void,mklfreetls,(const MKL_UINT *fdwReason))
_Vml_Api(void,MKLFreeTls,(const MKL_UINT  fdwReason))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MKL_VML_FUNCTIONS_H__ */
