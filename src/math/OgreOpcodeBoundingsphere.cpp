/*******************************************************************************
 *  Copyright (C) 2007 by the members of PG 510, University of Dortmund:       *
 *              d-collide-users@lists.sourceforge.net                          *
 *     Andreas Beckermann, Christian Bode, Marcel Ens, Sebastian Ens,          *
 *     Martin Fassbach, Maximilian Hegele, Daniel Haus, Oliver Horst,          *
 *     Gregor Jochmann, Timo Loist, Marcel Nienhaus and Marc Schulz            *
 *                                                                             *
 *  All rights reserved.                                                       *
 *                                                                             *
 *  Redistribution and use in source and binary forms, with or without         *
 *  modification, are permitted provided that the following conditions are met:*
 *   - Redistributions of source code must retain the above copyright          *
 *     notice, this list of conditions and the following disclaimer.           *
 *   - Redistributions in binary form must reproduce the above copyright       *
 *     notice, this list of conditions and the following disclaimer in the     *
 *     documentation and/or other materials provided with the distribution.    *
 *   - Neither the name of the PG510 nor the names of its contributors may be  *
 *     used to endorse or promote products derived from this software without  *
 *     specific prior written permission.                                      *
 *                                                                             *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER *
 *  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,   *
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,        *
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR         *
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF     *
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING       *
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS         *
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE                *
 *******************************************************************************/

#include "math/OgreOpcodeBoundingsphere.h"

#include "math/OgreOpcodeAABB.h"
#include "types/OgreOpcodeArray.h"
#include "math/OgreOpcodeTriangle.h"
//#include "shapes/shapes.h"
//#include "debug.h"

#include <math.h>

namespace OgreOpcode
{
	namespace math
	{
		/*!
		 * TODO: Implement correct/faster collision detection methods for
		 *       collisions between different types of bounding volumes.
		 */
		bool BoundingSphere::collidesWith(const BoundingVolume& other) const {
			if (other.getVolumeType() == BV_TYPE_SPHERE) {
				const BoundingSphere& otherSphere = (const BoundingSphere&) other;

				real distance = DotProduct((getCenterVector() - otherSphere.getCenterVector()),(getCenterVector() - otherSphere.getCenterVector()));
				real radii = (mRadius + otherSphere.getRadius()) * (mRadius + otherSphere.getRadius());

				//std::cout << "2. Distanz : " << distance << "     2. radius: " << radii << std::endl;
	            
				if (distance > radii) {
					return 0;
				} else {
					//std::cout << "Kollision" << std::endl;
					return 1;
				}
			} else {
				Aabb thisAabb(getSurroundingAabbMin(), getSurroundingAabbMax());
				return
					thisAabb.collidesWith(
						Aabb(other.getSurroundingAabbMin(),
							 other.getSurroundingAabbMax()));
			}
		}

		void BoundingSphere::mergeWith(const BoundingVolume* other) {

			if (other->getVolumeType() == BV_TYPE_SPHERE) {
				return mergeWith((const BoundingSphere*) other);

			} else {
				Vector3_r min = other->getSurroundingAabbMin();
				Vector3_r max = other->getSurroundingAabbMax();

				Vector3_r radius = (max-min)/2;

				BoundingSphere other(radius + min, Length(radius));

				mergeWith(&other);
			}
		}

		/*!
		 * This method merges this bounding sphere with another bounding sphere, so
		 * that afterwards this bounding sphere includes all the space that was
		 * previously included by the other bounding sphere.
		 */
		void BoundingSphere::mergeWith(const BoundingSphere* other) {

			Vector3_r span = other->getCenterVector() - getCenterVector();
			real distance = Length(span);


			if (   (mRadius >= (distance + other->getRadius()))
				|| (    (fabs(distance) <= 0.0001)
					 && (fabs(other->getRadius() - mRadius) <= 0.0001))) {
				// nothing to do since this bounding sphere includes the other one,
				// or the bounding spheres are identical

			} else if (other->getRadius() > (distance + mRadius)) {
				mRadius = other->getRadius();
				mCenterVertex = other->getCenterVertex();
				//FIXME mCenterVertex can be a null pointer

			} else {
				real radius, length;
				Vector3_r direction;

				radius  = distance + mRadius + other->getRadius();
				radius /= 2;

				length = (radius - mRadius) / distance;

				mRadius  = radius;
				mCenterVector += span * length;
				//the old center in the Vertex must be deleted
				mCenterVertex = 0;
			}

		}

		void BoundingSphere::mergeWith(const std::list<BoundingSphere*> others) {

			for (std::list<BoundingSphere*>::const_iterator iter = others.begin();
				iter != others.end();
				++iter) {

				mergeWith(*iter);
			}
		}

		void BoundingSphere::translate(const Vector3_r& translateBy) {
			mCenterVector += translateBy;
		}

	    
		/*!
		 * \internal
		 * 
		 * This method adjusts the boundig sphere to the given list of points.
		 * Therefor an algorithm by Jack Ritter (Versatec Inc.) is implemented.
		 *
		 * NOTICE:
		 * This is an adaption of the algorithm proposed by Jack Ritter in
		 * "Graphics Gems", Academic Press, 1990
		 */
		template<typename Container>
		static inline void resetInternal(const Container& points, Vector3_r& mCenterVector, real& mRadius) {

			//TODO: Profile this and replace it when needed!

			// when no points are given nothing has to be done
			if (!points.empty()) {

				Vector3_r minX, minY, minZ;
				Vector3_r maxX, maxY, maxZ;
				typename Container::const_iterator iter = points.begin();

				minX = minY = minZ = BoundingVolume::retrieveVector3FromIterator(iter);
				maxX = maxY = maxZ = BoundingVolume::retrieveVector3FromIterator(iter);
				++iter;


				// find the points in the list which has the greatest and smallest
				// values on x,y or z axis
				while(iter != points.end()) {

					const Vector3_r& point 
						= BoundingVolume::retrieveVector3FromIterator(iter);
	                
					if (point.x < minX.x) {
						minX = point;
					}
					if (point.y < minY.y) {
						minY = point;
					}
					if (point.z < minZ.z) {
						minZ = point;
					}

					if (point.x > maxX.x) {
						maxX = point;
					}
					if (point.y > maxY.y) {
						maxY = point;
					}
					if (point.z > maxZ.z) {
						maxZ = point;
					}

					++iter;
				}


				// which pair has the greatest distance to each other?
				real spanX = DotProduct((maxX - minX),(maxX - minX));
				real spanY = DotProduct((maxY - minY),(maxY - minY));
				real spanZ = DotProduct((maxZ - minZ),(maxZ - minZ));


				// which is the bigest span?
				real maxSpan = spanX;
				Vector3_r& min = minX;
				Vector3_r& max = maxX;

				if (spanY > maxSpan) {
					maxSpan = spanY;
					min = minY;
					max = maxY;
				}

				if (spanZ > maxSpan) {
					maxSpan = spanZ;
					min = minZ;
					max = maxZ;
				}


				// calculate first approximation of the bounding sphere parameters
				Vector3_r center = (min + max) / 2;
				real squareRadius = DotProduct((max - center),(max - center));
				real radius = sqrt(squareRadius);


				// go through the list of points and recalculate the bounding sphere
				// parameters if a point lies outside the previously calculated
				// bounding sphere

				real distance, squareDistance;

				iter = points.begin();
				while(iter != points.end()) {

					const Vector3_r& point 
						= BoundingVolume::retrieveVector3FromIterator(iter);

					squareDistance = DotProduct((point - center),(point - center));

					if (squareDistance > squareRadius) {

						distance = sqrt(squareDistance);

						radius = (real) ((radius + distance) / 2.0);
						squareRadius = radius*radius;

						center = (center - point) * (radius / distance) + point;
					}

					++iter;
				}

				// set boundingsphere parameters to the newly calculated ones
				mRadius = radius;
				mCenterVector = center;
			}
		}

		void BoundingSphere::reset(const std::list<Vector3_r>& points) {
			resetInternal(points, mCenterVector, mRadius);
		}

		void BoundingSphere::reset(const std::vector<Vertex*>& vertices) {
			resetInternal(vertices, mCenterVector, mRadius);
		}


		/* As this methods are only needed if we do a top down processing of a
		 * proxy we didn't need to implement this for now, as the deformable group
		 * uses a bottom up implementation and the rigid group didn't use bounding
		 * spheres.
		 */

		//void BoundingSphere::adjustToBox(const Matrix* worldState, const Box* box) {

		//	Vector3_r lower;
		//	Vector3_r upper;

		//	const Vector3_r& dimension = box->getDimension();


		//	worldState->transform(&lower, Vector3_r(0,0,0));
		//	worldState->transform(&upper, dimension);

		//	mCenterVector = (lower + upper) / 2;
		//	mRadius = (mCenterVector - lower).length();
		//}

		//void BoundingSphere::adjustToCylinder(const Matrix* worldState,
		//									  const Cylinder* cylinder) {
		//	resetToApproximatedAabbOfCylinder(worldState, cylinder);
		//}

		//void BoundingSphere::adjustToCone(const Matrix* worldState, const Cone* cone) {
		//	resetToApproximatedAabbOfCone(worldState, cone);
		//}

		/*!
		 * Calculate respectivly collects the positions of all vertices of the mesh
		 * triangles and thena calls the reset method of the BoundingSphere to
		 * adjust the sphere to this points.
		 */
		//void BoundingSphere::adjustToMesh(const Mesh* mesh) {

		//	std::list<Vector3_r> vertices;
		//	const std::vector<Vertex*>& meshVertices = mesh->getVertices();

		//	for (std::vector<Vertex*>::const_iterator iter = meshVertices.begin();
		//		 iter != meshVertices.end();
		//		 ++iter) {

		//		vertices.push_back((*iter)->getWorldPosition());
		//	}

		//	reset(vertices);
		//}

		//void BoundingSphere::adjustToMeshPart(const MeshPart* meshPart) {

		//	std::list<Vector3_r> vertices;
		//	const std::vector<Vertex*>& meshVertices = meshPart->getVertices();

		//	for (std::vector<Vertex*>::const_iterator iter = meshVertices.begin();
		//		 iter != meshVertices.end();
		//		 ++iter) {

		//		vertices.push_back((*iter)->getWorldPosition());
		//	}

		//	reset(vertices);
		//}

		/*!
		 * WARNING:
		 * The new radius isn't actually the same as the radius of the Shape, but we
		 * ignore this fact for the moment.
		 */
	//	void BoundingSphere::adjustToSphere(const Matrix* worldState,
	//										const Sphere* sphere) {

	//		mRadius = sphere->getRadius();
	//		worldState->transform(&mCenterVector, Vector3_r(0,0,0));

	//#       ifdef __GNUC__
	//#           warning BoundingSphere::adjustToSphere - correct radius calculation
	//#       endif
	//	}

		//void BoundingSphere::adjustToWedge(const Matrix* worldState,
		//								   const Wedge* wedge) {
		//	//DCOLLIDE_UNUSED(worldState);

		//	// AB: taken from Aabb::adjustToWedge()

		//	const Vector3_r* vertices = const_cast<Wedge*>(wedge)->getVertices();

		//	std::list<Vector3_r> aabbVertices;
		//	for (int i = 0; i < 6; i++) {
		//		aabbVertices.push_back(vertices[i]);
		//	}
		//	reset(aabbVertices);
		//}

		void BoundingSphere::adjustToTriangle(const Triangle* triangle) {

			std::list<Vector3_r> vertices;
			const types::array<Vertex*,3>& meshVertices = triangle->getVertices();

			vertices.push_back(meshVertices[0]->getWorldPosition());
			vertices.push_back(meshVertices[1]->getWorldPosition());
			vertices.push_back(meshVertices[2]->getWorldPosition());

			reset(vertices);
		}

		const Vector3_r& BoundingSphere::getCenterVector() const {
			if (mCenterVertex == 0) {
				return mCenterVector;
			} else {
				return mCenterVertex->getWorldPosition();
			}
		}

		Vector3_r BoundingSphere::getSurroundingAabbMin() const {
			if (!mCenterVertex) {
				return Vector3_r(mCenterVector - Vector3_r(mRadius, mRadius, mRadius));
			} else {
				return Vector3_r(mCenterVertex->getWorldPosition() - Vector3_r(mRadius, mRadius, mRadius));
			}
		}

		Vector3_r BoundingSphere::getSurroundingAabbMax() const {
			if (!mCenterVertex) {
				return Vector3_r(mCenterVector + Vector3_r(mRadius, mRadius, mRadius));
			} else {
				return Vector3_r(mCenterVertex->getWorldPosition() + Vector3_r(mRadius, mRadius, mRadius));
			}
		}

	} // namespace math
} // namespace OgreOpcode

/*
 * vim: et sw=4 ts=4
 */
