/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreOpcodeNettle.h
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
#ifndef __OgreOpcodeNettle_h__
#define __OgreOpcodeNettle_h__
// Copyright (C) 2002-2007 Nikolaus Gebhardt
// This file was part of the "Irrlicht Engine".
#if 0
namespace Ogre
{
	class SceneManager;
	class SceneNode;
	class Real;
}

namespace OgreOpcode
{

	//!	The Scene Collision Manager provides methods for performing collision tests and picking on scene nodes.
	class NettleCollision
	{
	public:

		//! constructor
		NettleCollision(Ogre::SceneManager* smanager);

		//! destructor
		virtual ~NettleCollision();

		//! Returns the scene node, which is currently visible under the overgiven 
		//! screencoordinates, viewed from the currently active camera. 
		virtual Ogre::SceneNode* getSceneNodeFromScreenCoordinatesBB(Ogre::Vector2 pos,
			int idBitMask=0, bool bNoDebugObjects = false);

		//! Returns the nearest scene node which collides with a 3d ray and 
		//! which id matches a bitmask. 
		virtual Ogre::SceneNode* getSceneNodeFromRayBB(Ray3 ray, int idBitMask=0, 
												  bool bNoDebugObjects = false);

		//! Returns the scene node, at which the overgiven camera is looking at and
		//! which id matches the bitmask.
		virtual Ogre::SceneNode* getSceneNodeFromCameraBB(Ogre::Camera* camera, int idBitMask=0,
													 bool bNoDebugObjects = false);

		//! Finds the collision point of a line and lots of triangles, if there is one.
		virtual bool getCollisionPoint(const Ray3& ray,
			ITriangleSelector* selector, Ogre::Vector3& outCollisionPoint,
			Triangle& outTriangle);

		//! Collides a moving ellipsoid with a 3d world with gravity and returns
		//! the resulting new position of the ellipsoid. 
		virtual Ogre::Vector3 getCollisionResultPosition(
			ITriangleSelector* selector,
			const Ogre::Vector3 &ellipsoidPosition,	const Ogre::Vector3& ellipsoidRadius, 
			const Ogre::Vector3& ellipsoidDirectionAndSpeed,
			Triangle& triout,
			bool& outFalling,
			Ogre::Real slidingSpeed,
			const Ogre::Vector3& gravityDirectionAndSpeed);

		//! Returns a 3d ray which would go through the 2d screen coodinates.
		virtual Ray3 getRayFromScreenCoordinates(
			Ogre::Vector2 pos, Ogre::Camera* camera = 0);

		//! Calculates 2d screen position from a 3d position.
		virtual Ogre::Vector2 getScreenCoordinatesFrom3DPosition(
			Ogre::Vector3 pos, Ogre::Camera* camera=0);

	private:

		//! recursive method for going through all scene nodes
		void getPickedNodeBB(Ogre::SceneNode* root,
					   const Ray3& ray,
					   int bits,
					   bool bNoDebugObjects,
					   Ogre::Real& outbestdistance,
					   Ogre::SceneNode*& outbestnode);

		struct SCollisionData
		{
			Ogre::Vector3 eRadius;

			Ogre::Vector3 R3Velocity; 
			Ogre::Vector3 R3Position;

			Ogre::Vector3 velocity;
			Ogre::Vector3 normalizedVelocity;
			Ogre::Vector3 basePoint;

			bool foundCollision;
			Ogre::Real nearestDistance;
			Ogre::Vector3 intersectionPoint;

			Triangle intersectionTriangle;
			int triangleHits;

			Ogre::Real slidingSpeed;

			ITriangleSelector* selector;
		};

		void testTriangleIntersection(SCollisionData* colData, 
			const Triangle& triangle);

		//! recursive method for doing collision response
		Ogre::Vector3 collideEllipsoidWithWorld(ITriangleSelector* selector, 
			const Ogre::Vector3 &position,
			const Ogre::Vector3& radius,  const Ogre::Vector3& velocity,
			Ogre::Real slidingSpeed,
			const Ogre::Vector3& gravity, Triangle& triout,
			bool& outFalling);

		Ogre::Vector3 collideWithWorld(SCollisionData &colData,
			Ogre::Vector3 pos, Ogre::Vector3 vel);
		Ogre::Vector3 collideWithWorld(int recursionDepth, SCollisionData &colData,
			Ogre::Vector3 pos, Ogre::Vector3 vel);

		inline bool getLowestRoot(Ogre::Real a, Ogre::Real b, Ogre::Real c, Ogre::Real maxR, Ogre::Real* root);

		Ogre::SceneManager* SceneManager;
		std::vector<Triangle> Triangles; // triangle buffer 
	};

} // end namespace OgreOpcode
#endif // if 0

#endif // __OgreOpcodeNettle_h__

