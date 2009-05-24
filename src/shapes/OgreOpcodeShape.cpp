/// ////////////////////////////////////////////////////////////////////////////
///  @file IOgreCollisionShape.cpp
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

#include "OgreOpcodeExports.h"
#include "shapes/OgreOpcodeShape.h"
#include "OgreOpcodeCollisionReporter.h"
#include "OgreOpcodeCollisionManager.h"
#include "utility/OgreOpcodeUtils.h"
#include "math/OgreOpcodeVector3.h"

namespace OgreOpcode
{
	template<class NodeT>
	inline void GetOpcodeNodeCenter(const NodeT &n, math::Vector3_r &ctr)
	{
		ctr[0] = n.mAABB.mCenter.x;
		ctr[1] = n.mAABB.mCenter.y;
		ctr[2] = n.mAABB.mCenter.z;
	}
	template<class TreeT, class NodeT>
	inline void GetOpcodeQuantizedNodeCenter(const TreeT &tree, const NodeT &n, math::Vector3_r &ctr)
	{
		ctr = math::Vector3_r(float(n.mAABB.mCenter[0]),  float(n.mAABB.mCenter[1]), float(n.mAABB.mCenter[2]));
		ctr[0] *= tree.mCenterCoeff.x;
		ctr[1] *= tree.mCenterCoeff.y;
		ctr[2] *= tree.mCenterCoeff.z;
	}
	template<class NodeT>
	inline void GetOpcodeNodeMinMaxBox(const NodeT &n, math::Vector3_r &bmin, math::Vector3_r &bMax)
	{
		math::Vector3_r center(n.mAABB.mCenter.x,  n.mAABB.mCenter.y,  n.mAABB.mCenter.z);
		math::Vector3_r extent(n.mAABB.mExtents.x, n.mAABB.mExtents.y, n.mAABB.mExtents.z);

		bmin  = center;
		bmin -= extent;
		bMax  = center;
		bMax += extent;
	}
	template<class TreeT, class NodeT>
	inline void GetOpcodeQuantizedNodeMinMaxBox(const TreeT &tree, const NodeT &n, math::Vector3_r &bmin, math::Vector3_r &bMax)
	{
		math::Vector3_r center(float(n.mAABB.mCenter[0]),  float(n.mAABB.mCenter[1]), float(n.mAABB.mCenter[2]));
		math::Vector3_r extent(float(n.mAABB.mExtents[0]), float(n.mAABB.mExtents[1]), float(n.mAABB.mExtents[2]));

		extent.x *= tree.mExtentsCoeff.x;
		extent.y *= tree.mExtentsCoeff.y;
		extent.z *= tree.mExtentsCoeff.z;

		center.x *= tree.mCenterCoeff.x;
		center.y *= tree.mCenterCoeff.y;
		center.z *= tree.mCenterCoeff.z;

		bmin  = center;
		bmin -= extent;
		bMax  = center;
		bMax += extent;
	}

	inline void GetOpcodeRootCenter(const Opcode::Model &mdl, math::Vector3_r &ctr)
	{
		if (mdl.IsQuantized()) {
			if (mdl.HasLeafNodes()) {
				const Opcode::AABBQuantizedTree& tree = *static_cast<const Opcode::AABBQuantizedTree*>(mdl.GetTree());
				GetOpcodeQuantizedNodeCenter(tree, *tree.GetNodes(), ctr);
			}
			else{
				const Opcode::AABBQuantizedNoLeafTree& tree = *static_cast<const Opcode::AABBQuantizedNoLeafTree*>(mdl.GetTree());
				GetOpcodeQuantizedNodeCenter(tree, *tree.GetNodes(), ctr);
			}
		}
		else{
			if (mdl.HasLeafNodes()) {
				const Opcode::AABBCollisionNode& root = *static_cast<const Opcode::AABBCollisionTree*>(mdl.GetTree())->GetNodes();
				GetOpcodeNodeCenter(root, ctr);
			}
			else{
				const Opcode::AABBNoLeafNode& root = *static_cast<const Opcode::AABBNoLeafTree*>(mdl.GetTree())->GetNodes();
				GetOpcodeNodeCenter(root, ctr);
			}
		}
	}
	inline void GetOpcodeRootMinMaxBox(const Opcode::Model &mdl, math::Vector3_r &bmin, math::Vector3_r &bMax)
	{
		if (mdl.IsQuantized()) {
			if (mdl.HasLeafNodes()) {
				const Opcode::AABBQuantizedTree& tree = *static_cast<const Opcode::AABBQuantizedTree*>(mdl.GetTree());
				GetOpcodeQuantizedNodeMinMaxBox(tree, *tree.GetNodes(), bmin, bMax);
			}
			else{
				const Opcode::AABBQuantizedNoLeafTree& tree = *static_cast<const Opcode::AABBQuantizedNoLeafTree*>(mdl.GetTree());
				GetOpcodeQuantizedNodeMinMaxBox(tree, *tree.GetNodes(), bmin, bMax);
			}
		}
		else{
			if (mdl.HasLeafNodes()) {
				const Opcode::AABBCollisionNode& root = *static_cast<const Opcode::AABBCollisionTree*>(mdl.GetTree())->GetNodes();
				GetOpcodeNodeMinMaxBox(root, bmin, bMax);
			}
			else{
				const Opcode::AABBNoLeafNode& root = *static_cast<const Opcode::AABBNoLeafTree*>(mdl.GetTree())->GetNodes();
				GetOpcodeNodeMinMaxBox(root, bmin, bMax);
			}
		}
	}

	CollisionShape::CollisionShape(const std::string& name)
	{
	}

	//------------------------------------------------------------------------
	CollisionShape::~CollisionShape()
	{
	}

}

//------------------------------------------------------------------------
