/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreOpcodeCapsule.cpp
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

#include "OgreOpcodeCapsule.h"
#include "OgreOpcodeLine.h"

using namespace Ogre;
namespace OgreOpcode
{
	//------------------------------------------------------------------------
	bool Capsule::contains( const Vector3& point ) const
	{
		Line line( start, end );

		return line.squaredDistance(point) <= (radius*radius);
	}
	//------------------------------------------------------------------------
	//bool Capsule::intersects( const Aabb& aabb ) const
	//{
	//	// TODO: optimize this code for the AABB case.
	//	OrientedBox obb( aabb );
	//	return intersects( obb );
	//}
	//------------------------------------------------------------------------
	//bool Capsule::intersects( const sphere& s ) const
	//{
	//	Line line( start, end);
	//	Real sqrDist = line.squaredDistance( s.p );
	//	Real rsum = radius + s.r;
	//		
	//	return sqrDist <= (rsum*rsum);
	//}
	//------------------------------------------------------------------------
	bool Capsule::intersects( const OrientedBox& obb ) const
	{
		Line line( start, end );

		return line.squaredDistance(obb) <= (radius*radius);
	}
	//------------------------------------------------------------------------
	bool Capsule::intersects( const Capsule& cap ) const
	{
		Line me( start, end );
		Line it( cap.start, cap.end );

		Real sqrDist = me.squaredDistance( it );
		Real rsum = radius + cap.radius;

		return sqrDist <= (rsum*rsum);;
	}		
	//------------------------------------------------------------------------
}

