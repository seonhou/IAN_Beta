/*******************************************************************************
!   Copyright(C) 1999-2011 Intel Corporation. All Rights Reserved.
!   
!   The source code, information  and  material ("Material") contained herein is
!   owned  by Intel Corporation or its suppliers or licensors, and title to such
!   Material remains  with Intel Corporation  or its suppliers or licensors. The
!   Material  contains proprietary information  of  Intel or  its  suppliers and
!   licensors. The  Material is protected by worldwide copyright laws and treaty
!   provisions. No  part  of  the  Material  may  be  used,  copied, reproduced,
!   modified, published, uploaded, posted, transmitted, distributed or disclosed
!   in any way  without Intel's  prior  express written  permission. No  license
!   under  any patent, copyright  or  other intellectual property rights  in the
!   Material  is  granted  to  or  conferred  upon  you,  either  expressly,  by
!   implication, inducement,  estoppel or  otherwise.  Any  license  under  such
!   intellectual  property  rights must  be express  and  approved  by  Intel in
!   writing.
!   
!   *Third Party trademarks are the property of their respective owners.
!   
!   Unless otherwise  agreed  by Intel  in writing, you may not remove  or alter
!   this  notice or  any other notice embedded  in Materials by Intel or Intel's
!   suppliers or licensors in any way.
!
!*******************************************************************************
!  Content:
!      Intel(R) Math Kernel Library (MKL) interface
!******************************************************************************/

#ifndef _MKL_H_
#define _MKL_H_

#define __INTEL_MKL__ 10
#define __INTEL_MKL_MINOR__ 3
#define __INTEL_MKL_UPDATE__ 4

#define INTEL_MKL_VERSION (__INTEL_MKL__ * 10000 + \
     __INTEL_MKL_MINOR__ * 100 + __INTEL_MKL_UPDATE__)
#include "mkl_types.h"
#include "mkl_blas.h"
#include "mkl_dfti.h"
#include "mkl_cblas.h"
#include "mkl_lapack.h"
#include "mkl_solver.h"
#include "mkl_vml.h"
#include "mkl_vsl.h"
#include "mkl_service.h"

#endif /* _MKL_H_ */
