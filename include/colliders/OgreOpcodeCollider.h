// Copyright 2005-2006 by Lightfeather-Team
// Written by Reinhard Ostermeier
// This file is part of the Lightfeather 3D-Engine.
// The license under which this code is distributed can be found in the file COPYING

#ifndef __OgreOpcodeCollider_h__
#define __OgreOpcodeCollider_h__

//#include <lf/core/list.h>
//#include <lf/core/CRefCounted.h>
#include "shapes/OgreOpcodeShape.h"
#include "colliders/OgreOpcodeCollisionTypes.h"

namespace OgreOpcode
{
	namespace colliders
	{

		//! \brief base class for all collider.
		//! for every possible combination of two shapes a collider mus be created
		//! and added to the collider array.
		class Collider //: public CRefCounted
		{
		public:
			//! Destructor
			virtual ~Collider() {};
			
			//! \brief returns the id of shape 1
			virtual COLLISION_SHAPE_ID getShapeID1() = 0;

			//! \brief returns the id of shape 2
			virtual COLLISION_SHAPE_ID getShapeID2() = 0;
			
			//! \brief checks if and where the two world nodes collides.
			//! if the nodes are not in the correct order the get exchanged and the normals gets inverted.
			//! \param node1: 1st world node
			//! \param node2: 2nd world node
			//! \param contacts: pointer to list for contact information. can be 0.
			//! \retrun true if the world nodes collide, else false
			virtual bool collideNodes(CollisionObject* node1, CollisionObject* node2, std::list<ShapeContact>* contacts) = 0;
		};
	}  // namespace colliders
}  // namespace OgreOpcode

#endif // __OgreOpcodeCollider_h__


