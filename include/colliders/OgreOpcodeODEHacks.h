// Copyright 2005-2006 by Lightfeather-Team
// Written by Reinhard Ostermeier
// This file is part of the Lightfeather 3D-Engine.
// The license under which this code is distributed can be found in the file COPYING

#ifndef __OgreOpcodeODEHacks_h__
#define __OgreOpcodeODEHacks_h__


#include "math/OgreOpcodeReal.h"

namespace OgreOpcode
{
	namespace colliders
	{
		typedef math::real Oop_dMatrix3[4*3];
		typedef math::real Oop_dVector3[4];
		#define Oop_dInfinity 3E37f
		#define Oop_dDOTpq(a,b,p,q) ((a)[0]*(b)[0] + (a)[p]*(b)[q] + (a)[2*(p)]*(b)[2*(q)])
		#define Oop_dDOT(a,b)   Oop_dDOTpq(a,b,1,1)
		#define Oop_dDOT13(a,b) Oop_dDOTpq(a,b,1,3)
		#define Oop_dDOT31(a,b) Oop_dDOTpq(a,b,3,1)
		#define Oop_dDOT33(a,b) Oop_dDOTpq(a,b,3,3)
		#define Oop_dDOT14(a,b) Oop_dDOTpq(a,b,1,4)
		#define Oop_dDOT41(a,b) Oop_dDOTpq(a,b,4,1)
		#define Oop_dDOT44(a,b) Oop_dDOTpq(a,b,4,4)
		#define Oop_dMULTIPLYOP0_331(A,op,B,C) \
		do { \
		  (A)[0] op Oop_dDOT((B),(C)); \
		  (A)[1] op Oop_dDOT((B+4),(C)); \
		  (A)[2] op Oop_dDOT((B+8),(C)); \
		} while(0)
		#define Oop_dMULTIPLYOP1_331(A,op,B,C) \
		do { \
		  (A)[0] op Oop_dDOT41((B),(C)); \
		  (A)[1] op Oop_dDOT41((B+1),(C)); \
		  (A)[2] op Oop_dDOT41((B+2),(C)); \
		} while(0)
		#define Oop_dMULTIPLYOP0_133(A,op,B,C) \
		do { \
		  (A)[0] op Oop_dDOT14((B),(C)); \
		  (A)[1] op Oop_dDOT14((B),(C+1)); \
		  (A)[2] op Oop_dDOT14((B),(C+2)); \
		} while(0)
		#define Oop_dMULTIPLYOP0_333(A,op,B,C) \
		do { \
		  (A)[0] op Oop_dDOT14((B),(C)); \
		  (A)[1] op Oop_dDOT14((B),(C+1)); \
		  (A)[2] op Oop_dDOT14((B),(C+2)); \
		  (A)[4] op Oop_dDOT14((B+4),(C)); \
		  (A)[5] op Oop_dDOT14((B+4),(C+1)); \
		  (A)[6] op Oop_dDOT14((B+4),(C+2)); \
		  (A)[8] op Oop_dDOT14((B+8),(C)); \
		  (A)[9] op Oop_dDOT14((B+8),(C+1)); \
		  (A)[10] op Oop_dDOT14((B+8),(C+2)); \
		} while(0)
		#define Oop_dMULTIPLYOP1_333(A,op,B,C) \
		do { \
		  (A)[0] op Oop_dDOT44((B),(C)); \
		  (A)[1] op Oop_dDOT44((B),(C+1)); \
		  (A)[2] op Oop_dDOT44((B),(C+2)); \
		  (A)[4] op Oop_dDOT44((B+1),(C)); \
		  (A)[5] op Oop_dDOT44((B+1),(C+1)); \
		  (A)[6] op Oop_dDOT44((B+1),(C+2)); \
		  (A)[8] op Oop_dDOT44((B+2),(C)); \
		  (A)[9] op Oop_dDOT44((B+2),(C+1)); \
		  (A)[10] op Oop_dDOT44((B+2),(C+2)); \
		} while(0)
		#define Oop_dMULTIPLYOP2_333(A,op,B,C) \
		do { \
		  (A)[0] op Oop_dDOT((B),(C)); \
		  (A)[1] op Oop_dDOT((B),(C+4)); \
		  (A)[2] op Oop_dDOT((B),(C+8)); \
		  (A)[4] op Oop_dDOT((B+4),(C)); \
		  (A)[5] op Oop_dDOT((B+4),(C+4)); \
		  (A)[6] op Oop_dDOT((B+4),(C+8)); \
		  (A)[8] op Oop_dDOT((B+8),(C)); \
		  (A)[9] op Oop_dDOT((B+8),(C+4)); \
		  (A)[10] op Oop_dDOT((B+8),(C+8)); \
		} while(0)

		#ifdef __GNUC__
		#define Oop_PURE_INLINE extern inline
		#else
		#define Oop_PURE_INLINE inline
		#endif
		#define Oop_DECL template <class TA, class TB, class TC> Oop_PURE_INLINE void

		/* 
		Note: NEVER call any of these functions/macros with the same variable for A and C, 
		it is not equivalent to A*=B.
		*/

		Oop_DECL Oop_dMULTIPLY0_331(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP0_331(A,=,B,C); }
		Oop_DECL Oop_dMULTIPLY1_331(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP1_331(A,=,B,C); }
		Oop_DECL Oop_dMULTIPLY0_133(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP0_133(A,=,B,C); }
		Oop_DECL Oop_dMULTIPLY0_333(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP0_333(A,=,B,C); }
		Oop_DECL Oop_dMULTIPLY1_333(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP1_333(A,=,B,C); }
		Oop_DECL Oop_dMULTIPLY2_333(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP2_333(A,=,B,C); }

		Oop_DECL Oop_dMULTIPLYADD0_331(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP0_331(A,+=,B,C); }
		Oop_DECL Oop_dMULTIPLYADD1_331(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP1_331(A,+=,B,C); }
		Oop_DECL Oop_dMULTIPLYADD0_133(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP0_133(A,+=,B,C); }
		Oop_DECL Oop_dMULTIPLYADD0_333(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP0_333(A,+=,B,C); }
		Oop_DECL Oop_dMULTIPLYADD1_333(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP1_333(A,+=,B,C); }
		Oop_DECL Oop_dMULTIPLYADD2_333(TA *A, const TB *B, const TC *C) { Oop_dMULTIPLYOP2_333(A,+=,B,C); }

		#undef Oop_DECL

	}	// namespace colliders
}	// namespace OgreOpcode

#endif // __OgreOpcodeODEHacks_h__


