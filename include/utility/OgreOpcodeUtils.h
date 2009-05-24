/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreOpcodeUtils.h
///  @brief This header file contains utility methods for OgreOpcode. Most of
///         them are for type conversions between IceMaths and Ogre.
///
///  @author The OgreOpcode Team
///
/// ////////////////////////////////////////////////////////////////////////////
///  
///  This file is part of OgreOpcode.
///  
///
/// Copyright (c) 2009 The OgreOpcode Team.
///
/// This software is provided 'as-is', without any express or implied
/// warranty. In no event will the authors be held liable for any damages
/// arising from the use of this software.
///
/// Permission is granted to anyone to use this software for any purpose,
/// including commercial applications, and to alter it and redistribute it
/// freely, subject to the following restrictions:
///
/// 1. The origin of this software must not be misrepresented; you must not
/// claim that you wrote the original software. If you use this software
/// in a product, an acknowledgment in the product documentation would be
/// appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such, and must not be
/// misrepresented as being the original software.
///
/// 3. This notice may not be removed or altered from any source
/// distribution.
///
///  
/// ////////////////////////////////////////////////////////////////////////////
#ifndef __OgreOpcodeUtils_h__
#define __OgreOpcodeUtils_h__

#include "math/OgreOpcodeVector3.h"
#include "math/OgreOpcodeMatrix.h"
#include "math/OgreOpcodeQuaternion.h"
#include "Opcode/Opcode.h"

namespace OgreOpcode
{
	namespace utility
	{
		/// This utility class is used to convert types from/to OgreOpcode and Opcode.
		/// Thus, it contributes for better, cleaner code and ease of maintenance in the project.
		class TypeConverter
		{
		public:

			/// Converts from an Ogre's vector into an IceMaths' one
			static void vector3ToIcePoint( const math::Vector3_r& vec, Opcode::Point& opcPoint )
			{
				opcPoint.x = vec[0];
				opcPoint.y = vec[1];
				opcPoint.z = vec[2];
			}

			/// Converts from an OgreOpcode Matrix_r into an IceMaths Matrix4x4
			static void matrixToIceMatrix4( const math::Matrix_r& mat, Opcode::Matrix4x4& opcMatrix )
			{
				for(unsigned int i = 0; i < 4; i++)
				{
					opcMatrix.m[0][i] = mat.m44[i][0];
					opcMatrix.m[1][i] = mat.m44[i][1];
					opcMatrix.m[2][i] = mat.m44[i][2];
					opcMatrix.m[3][i] = mat.m44[i][3];
				}
			}

			/// Converts from an IceMaths Matrix4x4 into an OgreOpcode Matrix_r
			static void iceMatrix4ToMatrix( const Opcode::Matrix4x4& opcMatrix, math::Matrix_r& mat)
			{
				for(unsigned int i = 0; i < 4; i++)
				{
					mat.m44[i][0] = opcMatrix.m[0][i];
					mat.m44[i][1] = opcMatrix.m[1][i];
					mat.m44[i][2] = opcMatrix.m[2][i];
					mat.m44[i][3] = opcMatrix.m[3][i];
				}
			}

			/// Converts from an Ogre's ray into an IceMaths' one
			//static void ogreToIceRay(  const Ogre::Ray& from, IceMaths::Ray& opcRay )
			//{
			//	opcRay.mOrig.x = from.getOrigin().x;
			//	opcRay.mOrig.y = from.getOrigin().y;
			//	opcRay.mOrig.z = from.getOrigin().z;

			//	opcRay.mDir.x = from.getDirection().x;
			//	opcRay.mDir.y = from.getDirection().y;
			//	opcRay.mDir.z = from.getDirection().z;
			//	opcRay.mDir.Normalize();
			//}

			///// Converts from an Ogre's sphere into an IceMaths' one
			//static void ogreToIceSphere(  const Ogre::Sphere& from, IceMaths::Sphere& to )
			//{
			//	to.Set( IceMaths::Point(from.getCenter().x,from.getCenter().y,from.getCenter().z), from.getRadius() );
			//}

		};
	} // namespace utility
} // namespace OgreOpcode


#endif // __OgreOpcodeUtils_h__
