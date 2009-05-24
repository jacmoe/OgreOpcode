/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreCollisionTypes.h
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
#ifndef __OgreCollisionTypes_h__
#define __OgreCollisionTypes_h__

namespace OgreOpcode
{

	/// Define the collision types for collision queries.
	enum CollisionType
	{
		COLLTYPE_IGNORE     = 1,    ///< no collisions
		COLLTYPE_QUICK      = 2,    ///< quick sphere-2-sphere collision
		COLLTYPE_BBOX		= 3,    ///< OBB collision
		COLLTYPE_CONTACT    = 4,    ///< first contact only
		COLLTYPE_EXACT      = 5,    ///< all contacts
	};

	/// special case values for the CollClass check.
	enum CollisionTypeOverride
	{
		COLLTYPE_ALWAYS_IGNORE  = -1,
		COLLTYPE_ALWAYS_QUICK   = -2,
		COLLTYPE_ALWAYS__BBOX	= -3,
		COLLTYPE_ALWAYS_CONTACT = -4,
		COLLTYPE_ALWAYS_EXACT   = -5,
	};

}


#endif // __OgreCollisionTypes_h__
