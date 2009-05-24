/*
	Twilight Prophecy SDK
	A multi-platform development system for virtual reality and multimedia.

	Copyright (C) 1997-2003 Twilight 3D Finland Oy Ltd.
*/
#ifndef __OgreOpcodeSphere_h__
#define __OgreOpcodeSphere_h__


#include <cmath>
#include "math/OgreOpcodeReal.h"
#include "math/OgreOpcodeVector3.h"
#include "math/OgreOpcodeBox.h"


namespace OgreOpcode
{
	namespace math
	{
		template <typename T>
		struct Sphere
		{
			
			// members

			Vector3<T>	center;
			T			radius;

			// constructors

			Sphere()
			{
			}

			Sphere(const Vector3<T>& c, const T& r)
			: center(c), radius(r)
			{
			}

			// methods

			bool IsInside(const Vector3<T>& point) const
			{
				return LengthSquared(point-center) < (radius*radius);
			}

			void Circumscribe(const Vector3<T>& boxmin, const Vector3<T>& boxmax)
			{
				center = (boxmin + boxmax) * static_cast<T>(0.5);
				Vector3<T> size = boxmax - boxmin;
				radius = static_cast<T>(sqrt(DotProduct(size,size)) * 0.5);
			}

			void Circumscribe(const Box<T>& box)
			{
				center = box.GetCenter();
				Vector3<T> size = box.GetSize();
				radius = static_cast<T>(sqrt(DotProduct(size,size)) * 0.5);
			}
		};

		#ifndef OGREMATH_NOTYPENAME

		typedef Sphere<real> Sphere_r;

		#endif // OGREMATH_NOTYPENAME
	} // namespace math
} // namespace OgreOpcode


#endif // __OgreOpcodeSphere_h__
