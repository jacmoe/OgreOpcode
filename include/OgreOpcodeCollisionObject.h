/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreCollisionObject.h
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
#ifndef __OgreCollisionObject_h__
#define __OgreCollisionObject_h__


#include "OgreOpcodeCollisionManager.h"
#include "OgreOpcodeCollisionContext.h"

namespace OgreOpcode
{
	/// Collision system object.
	/// CollisionObject is an actual collision system object which can
	/// be positioned and oriented in space. It points to an
	/// EntityCollisionShape which describes the actual shape of the
	/// object.
	/// CollisionObject%s are kept in sorted list (one for each dimension)
	/// by the CollisionContext they belong to.
	class _OgreOpcode_Export CollisionObject
	{
		friend class CollisionContext;

	public:
		CollisionObject(const std::string& name)
		{
		}

		virtual ~CollisionObject()
		{
		}
	};
}

#endif // __OgreCollisionObject_h__
