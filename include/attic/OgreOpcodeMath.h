/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreOpcodeMath.h
///  @brief <TODO: insert file description here>
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
#ifndef __OgreOpcodeMath_h__
#define __OgreOpcodeMath_h__

#include <Ogre.h>

namespace OgreOpcode
{
	// -----------------------------------------------------------------------
	// Overridden operators

	/// Dot product operator
	inline Ogre::Real operator | ( const Ogre::Vector3& u,  const Ogre::Vector3& v ) 
	{
		return (u.x*v.x + u.y*v.y + u.z*v.z);
	}

	/// Cross product operator
	inline Ogre::Vector3 operator ^ ( const Ogre::Vector3& u,  const Ogre::Vector3& v ) 
	{
		return u.crossProduct( v );
	}

	// forward declarations
	class Capsule;
	class Line;
	class OrientedBox;
}

#endif // __OgreOpcodeMath_h__
