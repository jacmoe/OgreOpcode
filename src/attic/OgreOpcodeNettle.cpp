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
// Copyright (C) 2002-2007 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "OgreOpcodeNettle.h"

namespace OgreOpcode
{
#if 0
	//! constructor
	NettleCollision::NettleCollision(Ogre::SceneManager* smanager)
		: SceneManager(smanager)
	{
	}



	//! destructor
	NettleCollision::~NettleCollision()
	{
	}



	//! Returns the scene node, which is currently visible under the overgiven
	//! screencoordinates, viewed from the currently active camera.
	Ogre::SceneNode* NettleCollision::getSceneNodeFromScreenCoordinatesBB(
		Ogre::Vector2 pos, int idBitMask, bool bNoDebugObjects)
	{
		Ray3 ln = getRayFromScreenCoordinates(pos, 0);

		if ( ln.start == ln.end )
			return 0;

		return getSceneNodeFromRayBB(ln, idBitMask, bNoDebugObjects);
	}



	//! Returns the nearest scene node which collides with a 3d ray and
	//! which id matches a bitmask.
	Ogre::SceneNode* NettleCollision::getSceneNodeFromRayBB(Ray3 ray,
		int idBitMask,
		bool bNoDebugObjects)
	{
		Ogre::SceneNode* best = 0;
		Ogre::Real dist = 9999999999.0f;

		getPickedNodeBB(SceneManager->getRootSceneNode(), ray, 
			idBitMask, bNoDebugObjects, dist, best);

		return best;
	}


	//! recursive method for going through all scene nodes
	void NettleCollision::getPickedNodeBB(Ogre::SceneNode* root,
		const Ray3& ray,
		int bits,
		bool bNoDebugObjects,
		Ogre::Real& outbestdistance,
		Ogre::SceneNode*& outbestnode)
	{
		Ogre::Vector3 edges[8];

		const std::list<Ogre::SceneNode*>& children = root->getChildren();

		std::list<Ogre::SceneNode*>::ConstIterator it = children.begin();
		for (; it != children.end(); ++it)
		{
			Ogre::SceneNode* current = *it;

			if (current->isVisible() &&
				(bNoDebugObjects ? !current->isDebugObject() : true) &&
				(bits==0 || (bits != 0 && (current->getID() & bits))))
			{
				// get world to object space transform
				core::matrix4 mat;
				if (!current->getAbsoluteTransformation().getInverse(mat))
					continue;

				// transform vector from world space to object space
				Ray3 line(ray);
				mat.transformVect(line.start);
				mat.transformVect(line.end);

				const core::aabbox3df& box = current->getBoundingBox();

				// do intersection test in object space
				if (box.intersectsWithLine(line))
				{
					box.getEdges(edges);
					Ogre::Real distance = 0.0f;

					for (int e=0; e<8; ++e)
					{
						Ogre::Real t = edges[e].getDistanceFromSQ(line.start);
						if (t > distance)
							distance = t;
					}

					if (distance < outbestdistance)
					{
						outbestnode = current;
						outbestdistance = distance;
					}
				}
			}

			getPickedNodeBB(current, ray, bits, bNoDebugObjects, outbestdistance, outbestnode);
		}
	} 



	//! Returns the scene node, at which the overgiven camera is looking at and
	//! which id matches the bitmask.
	Ogre::SceneNode* NettleCollision::getSceneNodeFromCameraBB(
		ICameraSceneNode* camera, int idBitMask, bool bNoDebugObjects)
	{
		if (!camera)
			return 0;

		Ogre::Vector3 start = camera->getAbsolutePosition();
		Ogre::Vector3 end = camera->getTarget();

		end = start + ((end - start).normalize() * camera->getFarValue());
		Ray3 line(start, end);

		return getSceneNodeFromRayBB(line, idBitMask, bNoDebugObjects);
	}



	//! Finds the collision point of a line and lots of triangles, if there is one.
	bool NettleCollision::getCollisionPoint(const Ray3& ray,
		ITriangleSelector* selector, Ogre::Vector3& outIntersection,
		Triangle& outTriangle)
	{
		if (!selector)
		{
			return false;
		}

		int totalcnt = selector->getTriangleCount();
		Triangles.set_used(totalcnt);

		int cnt = 0;
		selector->getTriangles(Triangles.pointer(), totalcnt, cnt, ray);

		const Ogre::Vector3 linevect = ray.getVector().normalize();
		Ogre::Vector3 intersection;
		Ogre::Real nearest = 9999999999999.0f;
		bool found = false;
		const Ogre::Real raylength = ray.getLengthSQ();

		for (int i=0; i<cnt; ++i)
		{
			if (Triangles[i].getIntersectionWithLine(ray.start, linevect, intersection))
			{
				const Ogre::Real tmp = intersection.getDistanceFromSQ(ray.start);
				const Ogre::Real tmp2 = intersection.getDistanceFromSQ(ray.end);

				if (tmp < raylength && tmp2 < raylength && tmp < nearest)
				{
					nearest = tmp;
					outTriangle = Triangles[i];
					outIntersection = intersection;
					found = true;
				}
			}
		}

		return found;
	}



	//! Collides a moving ellipsoid with a 3d world with gravity and returns
	//! the resulting new position of the ellipsoid.
	Ogre::Vector3 NettleCollision::getCollisionResultPosition(
		ITriangleSelector* selector,
		const Ogre::Vector3 &position, const Ogre::Vector3& radius,
		const Ogre::Vector3& direction,
		Triangle& triout,
		bool& outFalling,
		Ogre::Real slidingSpeed,
		const Ogre::Vector3& gravity)
	{
		if (!selector || radius.X == 0.0f || radius.Y == 0.0f || radius.Z == 0.0f)
			return position;

		return collideEllipsoidWithWorld(selector, position,
			radius, direction, slidingSpeed, gravity, triout, outFalling);
	}


	void NettleCollision::testTriangleIntersection(SCollisionData* colData,
		const Triangle& triangle)
	{
		const Plane trianglePlane = triangle.getPlane();

		// only check front facing polygons
		if ( !trianglePlane.isFrontFacing(colData->normalizedVelocity) )
			return;

		// get interval of plane intersection

		Ogre::Real t1, t0;
		bool embeddedInPlane = false;

		// calculate signed distance from sphere position to triangle plane
		Ogre::Real signedDistToTrianglePlane = trianglePlane.getDistanceTo(
			colData->basePoint);

		Ogre::Real normalDotVelocity =
			trianglePlane.Normal.dotProduct(colData->velocity);

		if ( core::iszero ( normalDotVelocity ) )
		{
			// sphere is traveling parallel to plane

			if (fabs(signedDistToTrianglePlane) >= 1.0f)
				return; // no collision possible
			else
			{
				// sphere is embedded in plane
				embeddedInPlane = true;
				t0 = 0.0;
				t1 = 1.0;
			}
		}
		else
		{
			normalDotVelocity = core::reciprocal ( normalDotVelocity );

			// N.D is not 0. Calculate intersection interval
			t0 = (-1.f - signedDistToTrianglePlane) * normalDotVelocity;
			t1 = (1.f - signedDistToTrianglePlane) * normalDotVelocity;

			// Swap so t0 < t1
			if (t0 > t1) { Ogre::Real tmp = t1; t1 = t0; t0 = tmp;	}

			// check if at least one value is within the range
			if (t0 > 1.0f || t1 < 0.0f)
				return; // both t values are outside 1 and 0, no collision possible

			// clamp to 0 and 1
			t0 = core::clamp ( t0, 0.f, 1.f );
			t1 = core::clamp ( t1, 0.f, 1.f );
		}

		// at this point we have t0 and t1, if there is any intersection, it
		// is between this interval
		Ogre::Vector3 collisionPoint;
		bool foundCollision = false;
		Ogre::Real t = 1.0f;

		// first check the easy case: Collision within the triangle;
		// if this happens, it must be at t0 and this is when the sphere
		// rests on the front side of the triangle plane. This can only happen
		// if the sphere is not embedded in the triangle plane.

		if (!embeddedInPlane)
		{
			Ogre::Vector3 planeIntersectionPoint =
				(colData->basePoint - trianglePlane.Normal)
				+ (colData->velocity * t0);

			if (triangle.isPointInsideFast(planeIntersectionPoint))
			{
				foundCollision = true;
				t = t0;
				collisionPoint = planeIntersectionPoint;
			}
		}

		// if we havent found a collision already we will have to sweep
		// the sphere against points and edges of the triangle. Note: A
		// collision inside the triangle will always happen before a
		// vertex or edge collision.

		if (!foundCollision)
		{
			Ogre::Vector3 velocity = colData->velocity;
			Ogre::Vector3 base = colData->basePoint;

			Ogre::Real velocitySqaredLength = velocity.getLengthSQ();
			Ogre::Real a,b,c;
			Ogre::Real newT;

			// for each edge or vertex a quadratic equation has to be solved:
			// a*t^2 + b*t + c = 0. We calculate a,b, and c for each test.

			// check against points
			a = velocitySqaredLength;

			// p1
			b = 2.0f * (velocity.dotProduct(base - triangle.pointA));
			c = (triangle.pointA-base).getLengthSQ() - 1.f;
			if (getLowestRoot(a,b,c,t, &newT))
			{
				t = newT;
				foundCollision = true;
				collisionPoint = triangle.pointA;
			}

			// p2
			if (!foundCollision)
			{
				b = 2.0f * (velocity.dotProduct(base - triangle.pointB));
				c = (triangle.pointB-base).getLengthSQ() - 1.f;
				if (getLowestRoot(a,b,c,t, &newT))
				{
					t = newT;
					foundCollision = true;
					collisionPoint = triangle.pointB;
				}
			}

			// p3
			if (!foundCollision)
			{
				b = 2.0f * (velocity.dotProduct(base - triangle.pointC));
				c = (triangle.pointC-base).getLengthSQ() - 1.f;
				if (getLowestRoot(a,b,c,t, &newT))
				{
					t = newT;
					foundCollision = true;
					collisionPoint = triangle.pointC;
				}
			}

			// check against edges:

			// p1 --- p2
			Ogre::Vector3 edge = triangle.pointB - triangle.pointA;
			Ogre::Vector3 baseToVertex = triangle.pointA - base;
			Ogre::Real edgeSqaredLength = edge.getLengthSQ();
			Ogre::Real edgeDotVelocity = edge.dotProduct(velocity);
			Ogre::Real edgeDotBaseToVertex = edge.dotProduct(baseToVertex);

			// calculate parameters for equation
			a = edgeSqaredLength* -velocitySqaredLength +
				edgeDotVelocity*edgeDotVelocity;
			b = edgeSqaredLength* (2.f *velocity.dotProduct(baseToVertex)) -
				2.0f*edgeDotVelocity*edgeDotBaseToVertex;
			c = edgeSqaredLength* (1.f -baseToVertex.getLengthSQ()) +
				edgeDotBaseToVertex*edgeDotBaseToVertex;

			// does the swept sphere collide against infinite edge?
			if (getLowestRoot(a,b,c,t,&newT))
			{
				Ogre::Real f = (edgeDotVelocity*newT - edgeDotBaseToVertex) / edgeSqaredLength;
				if (f >=0.0f && f <= 1.0f)
				{
					// intersection took place within segment
					t = newT;
					foundCollision = true;
					collisionPoint = triangle.pointA + (edge*f);
				}
			}

			// p2 --- p3
			edge = triangle.pointC-triangle.pointB;
			baseToVertex = triangle.pointB - base;
			edgeSqaredLength = edge.getLengthSQ();
			edgeDotVelocity = edge.dotProduct(velocity);
			edgeDotBaseToVertex = edge.dotProduct(baseToVertex);

			// calculate parameters for equation
			a = edgeSqaredLength* -velocitySqaredLength +
				edgeDotVelocity*edgeDotVelocity;
			b = edgeSqaredLength* (2*velocity.dotProduct(baseToVertex)) -
				2.0f*edgeDotVelocity*edgeDotBaseToVertex;
			c = edgeSqaredLength* (1-baseToVertex.getLengthSQ()) +
				edgeDotBaseToVertex*edgeDotBaseToVertex;

			// does the swept sphere collide against infinite edge?
			if (getLowestRoot(a,b,c,t,&newT))
			{
				Ogre::Real f = (edgeDotVelocity*newT-edgeDotBaseToVertex) /
					edgeSqaredLength;
				if (f >=0.0f && f <= 1.0f)
				{
					// intersection took place within segment
					t = newT;
					foundCollision = true;
					collisionPoint = triangle.pointB + (edge*f);
				}
			}


			// p3 --- p1
			edge = triangle.pointA-triangle.pointC;
			baseToVertex = triangle.pointC - base;
			edgeSqaredLength = edge.getLengthSQ();
			edgeDotVelocity = edge.dotProduct(velocity);
			edgeDotBaseToVertex = edge.dotProduct(baseToVertex);

			// calculate parameters for equation
			a = edgeSqaredLength* -velocitySqaredLength +
				edgeDotVelocity*edgeDotVelocity;
			b = edgeSqaredLength* (2*velocity.dotProduct(baseToVertex)) -
				2.0f*edgeDotVelocity*edgeDotBaseToVertex;
			c = edgeSqaredLength* (1-baseToVertex.getLengthSQ()) +
				edgeDotBaseToVertex*edgeDotBaseToVertex;

			// does the swept sphere collide against infinite edge?
			if (getLowestRoot(a,b,c,t,&newT))
			{
				Ogre::Real f = (edgeDotVelocity*newT-edgeDotBaseToVertex) /
					edgeSqaredLength;
				if (f >=0.0f && f <= 1.0f)
				{
					// intersection took place within segment
					t = newT;
					foundCollision = true;
					collisionPoint = triangle.pointC + (edge*f);
				}
			}
		}// end no collision found

		// set result:
		if (foundCollision)
		{
			// distance to collision is t
			Ogre::Real distToCollision = t*colData->velocity.getLength();

			// does this triangle qualify for closest hit?
			if (!colData->foundCollision ||
				distToCollision	< colData->nearestDistance)
			{
				colData->nearestDistance = distToCollision;
				colData->intersectionPoint = collisionPoint;
				colData->foundCollision = true;
				colData->intersectionTriangle = triangle;
				++colData->triangleHits;
			}

		}// end found collision
	}



	//! Collides a moving ellipsoid with a 3d world with gravity and returns
	//! the resulting new position of the ellipsoid.
	Ogre::Vector3 NettleCollision::collideEllipsoidWithWorld(
		ITriangleSelector* selector, const Ogre::Vector3 &position,
		const Ogre::Vector3& radius,  const Ogre::Vector3& velocity,
		Ogre::Real slidingSpeed,
		const Ogre::Vector3& gravity,
		Triangle& triout, bool& outFalling)
	{
		if (!selector || radius.X == 0.0f || radius.Y == 0.0f || radius.Z == 0.0f)
			return position;

		// This code is based on the paper "Improved Collision detection and Response"
		// by Kasper Fauerby, but some parts are modified.

		SCollisionData colData;
		colData.R3Position = position;
		colData.R3Velocity = velocity;
		colData.eRadius = radius;
		colData.nearestDistance = 9999999999999.0f;
		colData.selector = selector;
		colData.slidingSpeed = slidingSpeed;
		colData.triangleHits = 0;

		Ogre::Vector3 eSpacePosition = colData.R3Position / colData.eRadius;
		Ogre::Vector3 eSpaceVelocity = colData.R3Velocity / colData.eRadius;

		// iterate until we have our final position

		Ogre::Vector3 finalPos = collideWithWorld(colData, eSpacePosition, eSpaceVelocity);

		outFalling = false;

		// add gravity

		if (gravity != Ogre::Vector3(0,0,0))
		{
			colData.R3Position = finalPos * colData.eRadius;
			colData.R3Velocity = gravity;
			colData.triangleHits = 0;

			eSpaceVelocity = gravity/colData.eRadius;

			finalPos = collideWithWorld(0, colData,
				finalPos, eSpaceVelocity);

			outFalling = (colData.triangleHits == 0);
		}

		if (colData.triangleHits)
		{
			triout = colData.intersectionTriangle;
			triout.pointA *= colData.eRadius;
			triout.pointB *= colData.eRadius;
			triout.pointC *= colData.eRadius;
		}

		finalPos *= colData.eRadius;
		return finalPos;
	}

	/*** Ben ***/
	Ogre::Vector3 NettleCollision::collideWithWorld(
			SCollisionData &colData, Ogre::Vector3 pos, Ogre::Vector3 vel)
	{
		Ogre::Real veryCloseDistance = colData.slidingSpeed;
		colData.velocity = vel;
		colData.normalizedVelocity = vel;
		colData.normalizedVelocity.normalize();
		colData.basePoint = pos;
		colData.foundCollision = false;
		colData.nearestDistance = 9999999999999.0f;

		for(int i = 0; i < 5 ; i++)
		{
			core::aabbox3d<Ogre::Real> box(colData.R3Position);
			box.addInternalPoint(colData.R3Position + colData.R3Velocity);
			box.MinEdge -= colData.eRadius;
			box.MaxEdge += colData.eRadius;
			int totalTriangleCnt = colData.selector->getTriangleCount();
			Triangles.set_used(totalTriangleCnt);

			core::matrix4 scaleMatrix;
			scaleMatrix.setScale(
				Ogre::Vector3(1.0f / colData.eRadius.X, 
				1.0f / colData.eRadius.Y,
				1.0f / colData.eRadius.Z)
				);
			int triangleCnt = 0;
			colData.selector->getTriangles(Triangles.pointer(), totalTriangleCnt, triangleCnt, box, &scaleMatrix);
			for (int i=0; i<triangleCnt; ++i)
			{
				testTriangleIntersection(&colData, Triangles[i]);
			}
			if (!colData.foundCollision)
			{
				return pos + vel;
			}
			// original destination point
			Ogre::Vector3 destinationPoint = pos + vel;
			Ogre::Vector3 newBasePoint = pos;
			// only update if we are not already very close
			// and if so only move very close to intersection, not to the
			// exact point
			if (colData.nearestDistance >= veryCloseDistance)
			{
				Ogre::Vector3 v = vel;
				v.setLength( colData.nearestDistance - veryCloseDistance );
				newBasePoint = colData.basePoint + v;

				v.normalize();
				colData.intersectionPoint -= (v * veryCloseDistance);
			}

			// calculate sliding plane

			Ogre::Vector3 slidePlaneOrigin = colData.intersectionPoint;
			Ogre::Vector3 slidePlaneNormal = newBasePoint - colData.intersectionPoint;
			slidePlaneNormal.normalize();
			Plane slidingPlane(slidePlaneOrigin, slidePlaneNormal);

			Ogre::Vector3 newDestinationPoint =
				destinationPoint -
				(slidePlaneNormal * slidingPlane.getDistanceTo(destinationPoint));

			// generate slide vector

			Ogre::Vector3 newVelocityVector = newDestinationPoint -
				colData.intersectionPoint;

			if (newVelocityVector.getLength() < veryCloseDistance)
			{
				return newBasePoint;
			}
			colData.basePoint = newBasePoint;
			colData.velocity = newVelocityVector;
			colData.normalizedVelocity = newVelocityVector;
			colData.normalizedVelocity.normalize();
		}
		return colData.basePoint;
	}
	/*** end Ben ***/
	Ogre::Vector3 NettleCollision::collideWithWorld(int recursionDepth,
		SCollisionData &colData, Ogre::Vector3 pos, Ogre::Vector3 vel)
	{
		Ogre::Real veryCloseDistance = colData.slidingSpeed;

		if (recursionDepth > 5)
			return pos;

		colData.velocity = vel;
		colData.normalizedVelocity = vel;
		colData.normalizedVelocity.normalize();
		colData.basePoint = pos;
		colData.foundCollision = false;
		colData.nearestDistance = 9999999999999.0f;

		//------------------ collide with world

		// get all triangles with which we might collide
		core::aabbox3d<Ogre::Real> box(colData.R3Position);
		box.addInternalPoint(colData.R3Position + colData.R3Velocity);
		box.MinEdge -= colData.eRadius;
		box.MaxEdge += colData.eRadius;

		int totalTriangleCnt = colData.selector->getTriangleCount();
		Triangles.set_used(totalTriangleCnt);

		core::matrix4 scaleMatrix;
		scaleMatrix.setScale(
			Ogre::Vector3(1.0f / colData.eRadius.X, 
			1.0f / colData.eRadius.Y,
			1.0f / colData.eRadius.Z)
			);

		int triangleCnt = 0;
		colData.selector->getTriangles(Triangles.pointer(), totalTriangleCnt, triangleCnt, box, &scaleMatrix);
		//colData.selector->getTriangles(Triangles.pointer(), totalTriangleCnt, triangleCnt, &scaleMatrix);

		for (int i=0; i<triangleCnt; ++i)
			testTriangleIntersection(&colData, Triangles[i]);

		//---------------- end collide with world

		if (!colData.foundCollision)
			return pos + vel;

		// original destination point
		Ogre::Vector3 destinationPoint = pos + vel;
		Ogre::Vector3 newBasePoint = pos;

		// only update if we are not already very close
		// and if so only move very close to intersection, not to the
		// exact point
		if (colData.nearestDistance >= veryCloseDistance)
		{
			Ogre::Vector3 v = vel;
			v.setLength( colData.nearestDistance - veryCloseDistance );
			newBasePoint = colData.basePoint + v;

			v.normalize();
			colData.intersectionPoint -= (v * veryCloseDistance);
		}

		// calculate sliding plane

		Ogre::Vector3 slidePlaneOrigin = colData.intersectionPoint;
		Ogre::Vector3 slidePlaneNormal = newBasePoint - colData.intersectionPoint;
		slidePlaneNormal.normalize();
		Plane slidingPlane(slidePlaneOrigin, slidePlaneNormal);

		Ogre::Vector3 newDestinationPoint =
			destinationPoint -
			(slidePlaneNormal * slidingPlane.getDistanceTo(destinationPoint));

		// generate slide vector

		Ogre::Vector3 newVelocityVector = newDestinationPoint -
			colData.intersectionPoint;

		if (newVelocityVector.getLength() < veryCloseDistance)
			return newBasePoint;

		return collideWithWorld(recursionDepth+1, colData,
			newBasePoint, newVelocityVector);
	}


	//! Returns a 3d ray which would go through the 2d screen coodinates.
	Ray3 NettleCollision::getRayFromScreenCoordinates(
		Ogre::Vector2 pos, ICameraSceneNode* camera)
	{
		Ray3 ln(0,0,0,0,0,0);

		if (!SceneManager)
			return ln;

		if (!camera)
			camera = SceneManager->getActiveCamera();

		if (!camera)
			return ln;

		const scene::SViewFrustum* f = camera->getViewFrustum();

		Ogre::Vector3 farLeftUp = f->getFarLeftUp();
		Ogre::Vector3 lefttoright = f->getFarRightUp() - farLeftUp;
		Ogre::Vector3 uptodown = f->getFarLeftDown() - farLeftUp;

		core::rect<int> viewPort = Driver->getViewPort();
		core::dimension2d<int> screenSize(viewPort.getWidth(), viewPort.getHeight());

		Ogre::Real dx = pos.X / (Ogre::Real)screenSize.Width;
		Ogre::Real dy = pos.Y / (Ogre::Real)screenSize.Height;

		if (camera->isOrthogonal())
			ln.start = f->cameraPosition + (lefttoright * (dx-0.5f)) + (uptodown * (dy-0.5f));
		else
			ln.start = f->cameraPosition;

		ln.end = farLeftUp + (lefttoright * dx) + (uptodown * dy);

		return ln;
	}



	//! Calculates 2d screen position from a 3d position.
	Ogre::Vector2 NettleCollision::getScreenCoordinatesFrom3DPosition(
		Ogre::Vector3 pos3d, ICameraSceneNode* camera)
	{
		Ogre::Vector2 pos2d(-1000,-1000);

		if (!SceneManager || !Driver)
			return pos2d;

		if (!camera)
			camera = SceneManager->getActiveCamera();

		if (!camera)
			return pos2d;

		core::rect<int> viewPort = Driver->getViewPort();
		core::dimension2d<int> dim(viewPort.getWidth(), viewPort.getHeight());

		dim.Width /= 2;
		dim.Height /= 2;

		Ogre::Real transformedPos[4];

		core::matrix4 trans = camera->getProjectionMatrix();
		trans *= camera->getViewMatrix();

		transformedPos[0] = pos3d.X;
		transformedPos[1] = pos3d.Y;
		transformedPos[2] = pos3d.Z;
		transformedPos[3] = 1.0f;

		trans.multiplyWith1x4Matrix(transformedPos);

		if (transformedPos[3] < 0)
			return Ogre::Vector2(-10000,-10000);

		Ogre::Real zDiv = transformedPos[3] == 0.0f ? 1.0f :
			(1.0f / transformedPos[3]);

		pos2d.X = (int)(dim.Width * transformedPos[0] * zDiv) + dim.Width;
		pos2d.Y = ((int)(dim.Height - (dim.Height * (transformedPos[1] * zDiv))));

		return pos2d;
	}

	inline bool NettleCollision::getLowestRoot(Ogre::Real a, Ogre::Real b, Ogre::Real c, Ogre::Real maxR, Ogre::Real* root)
	{
		// check if solution exists
		Ogre::Real determinant = b*b - 4.0f*a*c;

		// if determinant is negative, no solution
		if (determinant < 0.0f) return false;

		// calculate two roots: (if det==0 then x1==x2
		// but lets disregard that slight optimization)
		// burningwater: sqrt( 0) is an illegal operation.... smth should be done...

		Ogre::Real sqrtD = (Ogre::Real)sqrt(determinant);

		Ogre::Real r1 = (-b - sqrtD) / (2*a);
		Ogre::Real r2 = (-b + sqrtD) / (2*a);

		// sort so x1 <= x2
		if (r1 > r2) { Ogre::Real tmp=r2; r2=r1; r1=tmp; }

		// get lowest root
		if (r1 > 0 && r1 < maxR)
		{
			*root = r1;
			return true;
		}

		// its possible that we want x2, this can happen if x1 < 0
		if (r2 > 0 && r2 < maxR)
		{
			*root = r2;
			return true;
		}

		return false;
	}

#endif // if 0
} // end namespace OgreOpcode

