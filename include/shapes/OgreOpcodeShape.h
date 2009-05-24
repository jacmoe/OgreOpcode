/// ////////////////////////////////////////////////////////////////////////////
///  @file IOgreCollisionShape.h
///  @brief Abstract base class for collision shapes
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
#ifndef __IOgreCollisionShape_h__
# define __IOgreCollisionShape_h__



#include "OgreOpcodeExports.h"

#include "OgreOpcodeCollisionTypes.h"
#include "Opcode/Opcode.h"
#include "OgreOpcodeCollisionReporter.h"

namespace OgreOpcode
{
	/// Describes shapes for collision system.
	/// Holds a triangle list describing a collision shape.
	class _OgreOpcode_Export CollisionShape
	{
	public:
		/// Constructs a ICollisionShape
		CollisionShape(const std::string& name);
		virtual ~CollisionShape();
	};

}; // namespace OgreOpcode

#endif // __IOgreCollisionShape_h__
