/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreOpcodeCollisionContext.h
///  @brief Contains the definition of the CollisionContext class.
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
#ifndef __OgreCollisionContext_h__
#define __OgreCollisionContext_h__


#include "OgreOpcodeCollisionReporter.h"
#include "OgreOpcodeCollisionTypes.h"
#include "Opcode/Opcode.h"

namespace OgreOpcode
{
	/// Defines a collision space.
	/// A CollisionContext creates a collision context, defined by
	/// a collection of CollisionObject%s which can collide with
	/// each other. CollisionObject%s can be added and removed
	/// from the context at any time.
	//   class _OgreOpcode_Export CollisionContext : public nNode
	class _OgreOpcode_Export CollisionContext
	{
	public:
		/// constructor
		CollisionContext(const std::string& name);
		/// destructor
		virtual ~CollisionContext();
	};
}

#endif // __OgreCollisionContext_h__
