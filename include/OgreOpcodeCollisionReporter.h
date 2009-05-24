/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreCollisionReporter.h
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
#ifndef __OgreCollisionReporter_h__
#define __OgreCollisionReporter_h__


#include "OgreOpcodeExports.h"
#include <set>
#include <iostream>
#include <list>
#include <iosfwd>

namespace OgreOpcode
{
	/// Collect and manage CollisionPair%s.
	/// Manages a set of collision pairs. Makes sure that each collision
	/// between 2 objects is only tested/reported once, to help 
	/// the CollisionContext avoid redundant checks.
	class _OgreOpcode_Export CollisionReporter
	{
	public:
		CollisionReporter() {}
	};
}

#endif // __OgreCollisionReporter_h__
