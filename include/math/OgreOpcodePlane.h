/*
	Twilight Prophecy SDK
	A multi-platform development system for virtual reality and multimedia.

	Copyright (C) 1997-2003 Twilight 3D Finland Oy Ltd.
*/
#ifndef __OgreOpcodePlane_h__
#define __OgreOpcodePlane_h__


#include "math/OgreOpcodeReal.h"
#include "math/OgreOpcodeVector3.h"


namespace OgreOpcode
{
	namespace math
	{
		template <typename T>
		struct Plane
		{

			// members

			Vector3<T>	normal;
			T			dist;
			
			// constructors

			Plane() 
			{
			}

			Plane(const Vector3<T>& n, const T& d)
			: normal(n), dist(d)
			{
			}

			Plane(const Vector3<T>& n, const Vector3<T>& point)
			: normal(n), dist(DotProduct(n,point))
			{
			}

			Plane(const Vector3<T>& v1, const Vector3<T>& v2, const Vector3<T>& v3)
			: normal(Normalize(CrossProduct(v2-v1,v3-v1))), dist(DotProduct(v1,normal))
			{
			}

			Plane(const Plane& plane)
			: normal(plane.normal), dist(plane.dist)
			{
			}

			// methods		

			T GetOffset(const Vector3<T>& point) const
			{
				return DotProduct(normal,point) - dist;
			}

			bool IsFront(const Vector3<T>& point) const
			{
				return GetOffset(point) > 0;
			}

			bool IsBack(const Vector3<T>& point) const
			{
				return GetOffset(point) < 0;
			}
		};
		#ifndef OGREOPCODEMATH_NOTYPENAME

		typedef Plane<real> Plane_r;

		#endif // OGREOPCODEMATH_NOTYPENAME
	} // namespace math
} // namespace OgreOpcode


#endif // __OgreOpcodePlane_h__
