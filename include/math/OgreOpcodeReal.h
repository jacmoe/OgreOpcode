/*******************************************************************************
 *  Copyright (C) 2007 by the members of PG 510, University of Dortmund:       *
 *              d-collide-users@lists.sourceforge.net                          *
 *     Andreas Beckermann, Christian Bode, Marcel Ens, Sebastian Ens,          *
 *     Martin Fassbach, Maximilian Hegele, Daniel Haus, Oliver Horst,         *
 *     Gregor Jochmann, Timo Loist, Marcel Nienhaus and Marc Schulz            *
 *                                                                             *
 *  All rights reserved.                                                       *
 *                                                                             *
 *  Redistribution and use in source and binary forms, with or without         *
 *  modification, are permitted provided that the following conditions are met:*
 *   - Redistributions of source code must retain the above copyright          *
 *     notice, this list of conditions and the following disclaimer.           *
 *   - Redistributions in binary form must reproduce the above copyright       *
 *     notice, this list of conditions and the following disclaimer in the     *
 *     documentation and/or other materials provided with the distribution.    *
 *   - Neither the name of the PG510 nor the names of its contributors may be  *
 *     used to endorse or promote products derived from this software without  *
 *     specific prior written permission.                                      *
 *                                                                             *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER *
 *  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,   *
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,        *
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR         *
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF     *
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING       *
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS         *
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE                *
 *******************************************************************************/

#ifndef __OgreOpcodereal_h__
#define __OgreOpcodereal_h__

namespace OgreOpcode
{
	namespace math
	{
#ifndef OGREOPCODE_USE_DOUBLE
		typedef float real;
		#define Oop_REAL(x) (x ## f)					/* form a constant */
		#define Oop_dRecip(x) ((1.0f/(x)))				/* reciprocal */
		#define Oop_dSqrt(x) (sqrtf(x))			/* square root */
		#define Oop_dRecipSqrt(x) ((1.0f/sqrtf(x)))		/* reciprocal square root */
		#define Oop_dSin(x) (sinf(x))				/* sine */
		#define Oop_dCos(x) (cosf(x))				/* cosine */
		#define Oop_dFabs(x) (fabsf(x))			/* absolute value */
		#define Oop_dAtan2(y,x) (atan2f(y,x))		/* arc tangent with 2 args */
		#define Oop_dFMod(a,b) (fmodf(a,b))		/* modulo */
		#define Oop_dFloor(x) floorf(x)			/* floor */
#else // OGREOPCODE_USE_DOUBLE
	    typedef double real;
		#define Oop_REAL(x) (x)
		#define Oop_dRecip(x) (1.0/(x))
		#define Oop_dSqrt(x) sqrt(x)
		#define Oop_dRecipSqrt(x) (1.0/sqrt(x))
		#define Oop_dSin(x) sin(x)
		#define Oop_dCos(x) cos(x)
		#define Oop_dFabs(x) fabs(x)
		#define Oop_dAtan2(y,x) atan2((y),(x))
		#define Oop_dFMod(a,b) (fmod((a),(b)))
		#define Oop_dFloor(x) floor(x)
#endif
	} // namespace math
} // namespace OgreOpcode

#endif

/*
 * vim: et sw=4 ts=4
 */
