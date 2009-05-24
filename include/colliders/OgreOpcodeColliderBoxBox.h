// Copyright 2005-2006 by Lightfeather-Team
// Written by Reinhard Ostermeier
// This file is part of the Lightfeather 3D-Engine.
// The license under which this code is distributed can be found in the file COPYING

#ifndef _C_COLLIDER_BOX_BOX_H_
#define _C_COLLIDER_BOX_BOX_H_


//#include <lf/core/list.h>
#include <colliders/OgreOpcodeCollider.h>
#include <shapes/OgreOpcodeShape.h>
#include "colliders/OgreOpcodeCollisionTypes.h"

namespace OgreOpcode
{
	class CollisionObject;
	
	namespace colliders
	{
		//! \brief collider for 2 boxes.
		//! collider which is used by the collison manager to compute if 
		//! and where two boxes colides.
		//! parts of the used code are adapted from ODE.
		//! this collider is tested but the normal directions must be checked again!
		class ColliderBoxBox : public Collider
		{
		public:
			//! Constrcutor
			ColliderBoxBox();

			//! Destructor
			virtual ~ColliderBoxBox();

			//! \brief returns the id of shape 1
			COLLISION_SHAPE_ID getShapeID1();

			//! \brief returns the id of shape 2
			COLLISION_SHAPE_ID getShapeID2();

			//! \brief checks if and where the two world nodes collides.
			//! if the nodes are not in the correct order the get exchanged and the normals gets inverted.
			//! \param node1: 1st world node
			//! \param node2: 2nd world node
			//! \param contacts: pointer to list for contact information. can be 0.
			//! \retrun true if the nodes collide, else false
			bool collideNodes(CollisionObject* node1, CollisionObject* node2, std::list<ShapeContact>* contacts);
		};
	}	// namespace colliders
}	// namespace OgreOpcode

#endif // _C_COLLIDER_BOX_BOX_H_


