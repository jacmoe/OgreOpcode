// Copyright 2005-2006 by Lightfeather-Team
// Written by Reinhard Ostermeier
// This file is part of the Lightfeather 3D-Engine.
// The license under which this code is distributed can be found in the file COPYING

#ifndef _C_COLLISION_TYPES_H_
#define _C_COLLISION_TYPES_H_


#include "math/OgreOpcodeVector3.h"

namespace OgreOpcode
{
	class CollisionObject;

	namespace colliders
	{

		enum COLLISION_SHAPE_ID
		{
			CSID_SPHERE		= 0,
			CSID_BOX,
			CSID_PLANE,
			CSID_RAY,
			CSID_CYLINDER,
			CSID_CCYLINDER,
			CSID_MODEL,
			
			CSID_USER0,
			CSID_USER1,
			CSID_USER2,
			CSID_USER3,
			CSID_USER4,
			CSID_USER5,
			CSID_USER6,
			CSID_USER7,
			CSID_USER8,
			CSID_USER9,
			
			CSID_MAX
		};


		//! \brief contact information struct for collision
		struct ShapeContact
		{
			ShapeContact() : depth( 0.0f ), node1( 0 ), node2( 0 ) {}
			
			math::Vector3_r		pos;		//! position of collision
			math::Vector3_r		normal;	//! normal directs from node2 towards node1
			math::real			depth;	//! penetration depth of collision
			CollisionObject*	node1;	//! 1st world node (pointer is not grabed!)
			CollisionObject*	node2;	//! 2nd world node (pointer is not grabed!)
		};

	}	// namespace colliders
}	// namespace OgreOpcode

#endif // _C_COLLISION_TYPES_H_


