/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreCollisionManager.h
///  @brief Collision Manager
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
#ifndef __OgreCollisionManager_h__
#define __OgreCollisionManager_h__

#include "OgreOpcodeExports.h"

#include "OgreOpcodeCollisionTypes.h"
#include "OgreOpcodeCollisionContext.h"
#include "Opcode/Opcode.h"
#include "shapes/OgreOpcodeShape.h"

#include <list>
#include <map>

/// Main %OgreOpcode namespace
namespace OgreOpcode
{
	/// Collision manager.
	/// The CollisionManager object serves as factory object of the
	/// different classes of the collision system, namely
	/// CollisionContext and ICollisionShape. A CollisionContext
	/// serves as factory for CollisionObject%s.
	class _OgreOpcode_Export CollisionManager
	{
		//friend class EntityCollisionShape;
	public:
		///TODO: Put these back into the private section!!
		Opcode::AABBTreeCollider opcTreeCollider; ///<
		Opcode::RayCollider      opcRayCollider; ///<
		Opcode::SphereCollider   opcSphereCollider; ///<
		Opcode::PlanesCollider   opcPlanesCollider; ///<
		Opcode::LSSCollider      opcSweptSphereCollider; ///<
		Opcode::BVTCache         opcTreeCache; ///<
		Opcode::CollisionFaces   opcFaceCache; ///<
		Opcode::SphereCache      opcSphereCache; ///<
		Opcode::PlanesCache      opcPlanesCache; ///<
		Opcode::LSSCache         opcSweptSphereCache; ///<

		CollisionManager();
		virtual ~CollisionManager();

	};

}; // namespace OgreOpcode

#endif // __OgreCollisionManager_h__
