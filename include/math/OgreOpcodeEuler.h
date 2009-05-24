/*
	Twilight Prophecy SDK
	A multi-platform development system for virtual reality and multimedia.

	Copyright (C) 1997-2003 Twilight 3D Finland Oy Ltd.
*/
#ifndef __OgreOpcodeEuler_h__
#define __OgreOpcodeEuler_h__


namespace OgreOpcode
{
	namespace math
	{
		enum EulerOrder
		{
			EULER_XYZ,
			EULER_XZY,
			EULER_YXZ,
			EULER_YZX,
			EULER_ZXY,
			EULER_ZYX
		};

		const float pi = 3.14159265358979323846264338327950288419716939937510f;

		template <typename T>
		inline T DegToRad(const T& angle)
		{
			return static_cast<T>(angle * (pi / 180.0));
		}

		template <typename T>
		inline T RadToDeg(const T& angle)
		{
			return static_cast<T>(angle * (180.0 / pi));
		}
	} // namespace math
} // namespace OgreOpcode


#endif // __OgreOpcodeEuler_h__
