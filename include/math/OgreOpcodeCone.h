/*
	Twilight Prophecy SDK
	A multi-platform development system for virtual reality and multimedia.

	Copyright (C) 1997-2003 Twilight 3D Finland Oy Ltd.
*/
#ifndef __OgreOpcodeCone_h__
#define __OgreOpcodeCone_h__


#include "math/OgreOpcodeReal.h"
#include "math/OgreOpcodeVector3.h"


namespace OgreOpcode
{
	namespace math
	{
		template <typename T>	
		struct Cone
		{

			// members

			Vector3<T>	origin;
			Vector3<T>	target;
			T			angle;

			// constructors

			Cone()
			{
			}

			Cone(const Vector3<T>& o, const Vector3<T>& t, const T& a)
			: origin(o), target(t), angle(a)
			{
			}
		};
		#ifndef OGREOPCODEMATH_NOTYPENAME

		typedef Cone<real> Cone_r;

		#endif // OGREOPCODEMATH_NOTYPENAME
	} // namespace math
} // namespace OgreOpcode

#endif // __OgreOpcodeCone_h__
