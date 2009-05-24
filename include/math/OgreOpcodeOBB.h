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
       notice, this list of conditions and the following disclaimer.           *
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

#ifndef DCOLLIDE_OBB_H
#define DCOLLIDE_OBB_H

#include "math/OgreOpcodeVector3.h"
#include "math/OgreOpcodeMatrix.h"
#include "math/OgreOpcodeVertex.h"
#include "math/OgreOpcodeBoundingvolume.h"

#include <list>
#include <vector>
#include <math.h>

#define OBB_DEBUG 1
#undef OBB_DEBUG

namespace OgreOpcode
{
	namespace math
	{

		class Vertex;

		/*!
		 * \brief struct to represent a element in a outside set
		 * used by the algorithm that creates the convex hull.
		 * note that the furthestPoint is not allowed to be in the list of the
		 * points!
		 */
		struct OutsideSet {
			Triangle* triangle;
			std::list<std::pair<Vector3_r,real> > points;
			std::pair<Vector3_r,real> furthestPoint;
			inline OutsideSet(Triangle* tri, 
					std::list<std::pair<Vector3_r,real> > ps,
					std::pair<Vector3_r,real> furthest);
			inline OutsideSet(const struct OutsideSet& copy);
		};

		inline OutsideSet::OutsideSet(Triangle* tri, 
					std::list<std::pair<Vector3_r,real> > ps,
					std::pair<Vector3_r,real> furthest) {
			triangle = tri;
			points = ps;
			furthestPoint = furthest;
		}

		inline OutsideSet::OutsideSet(const struct OutsideSet& copy) {
			triangle = copy.triangle;
			points = copy.points;
			furthestPoint = copy.furthestPoint;
		}

		/*!
		 * \brief Object Oriented Bounding Box
		 */
		class Obb : public BoundingVolume {
			private:
				Vector3_r mDimension;
				Matrix_r mState;
				Vector3_r mReferencePoint;
				friend class ObbTest;

			public:
				Obb();
				Obb(const Vector3_r& center, const Vector3_r& dimension, 
						const Matrix_r& rotation, const Vector3_r& referencePoint);
				Obb(const Vector3_r& dimension, const Matrix_r& state);

				explicit Obb(const std::list<Vector3_r>& points);
				Obb(const Obb& copy);
				~Obb();

				/*!
				 * @return @ref BoundingVolume::BV_TYPE_OBB
				 **/
				virtual BoundingVolumeType getVolumeType() const {
					return BV_TYPE_OBB;
				}

				virtual bool collidesWith(const BoundingVolume& other) const;

				virtual void mergeWith(const BoundingVolume* otherBV);

				Obb* intersectWith(const Obb& other) const;
				static Obb* calculateIntersection( const Obb& obb1,
						const Obb& obb2);

				inline const Vector3_r getCenter() const;
				inline const Vector3_r& getDimension() const;
				inline const Vector3_r& getReferencePoint() const;
				inline const Matrix_r getRotation() const;
				inline const Matrix_r& getState() const;

				inline void translate(const Vector3_r& translateBy);
				inline void rotate(const Matrix_r& rotateBy);
				inline void transform(const Matrix_r& transformBy);

				Vector3_r getSurroundingAabbExtents() const;
				Vector3_r getSurroundingAabbMin() const;
				Vector3_r getSurroundingAabbMax() const;

				inline real calculateVolume() const;

				inline Obb& operator=(const Obb& otherObb);
				inline bool operator==(const Obb& otherObb) const;

				void adjustToTriangle(const Triangle* triangle);
				Vector3_r* getVertices() const;

			protected:
				bool collidesWithInternal(const Obb& other) const;

				//void adjustToBox(const Matrix_r* worldState, const Box* box);
				//void adjustToCone(const Matrix_r* worldState, const Cone* cone);
				//void adjustToCylinder(const Matrix_r* worldState,
				//					  const Cylinder* meshPart);
				//void adjustToSphere(const Matrix_r* worldState, const Sphere* sphere);
				//void adjustToWedge(const Matrix_r* worldState, const Wedge* wedge);
				//void adjustToMesh(const Mesh* mesh);
				//void adjustToMeshPart(const MeshPart* meshpart);

				void adjustToPoints(const Matrix_r* worldState, const std::list<Vector3_r>& points);

				virtual void reset(const std::list<Vector3_r>& points);
				virtual void reset(const std::vector<Vertex*>& vertices);

			private:
				void adjustToConeOrCylinderInternal(const Matrix_r* worldState, 
						const real& radius, const real& height);

				void adjustToTriangles(const std::vector<Triangle*>& triangles,
						const std::vector<Vertex*>& vertices);
				void computeSpan(const Vector3_r* vertices, const Vector3_r& axis, real&
						min, real& max) const;
				inline bool overlap(float min1, float max1, 
						float min2, float max2) const;
				void performVectorIteration(const Matrix_r& A,Vector3_r* x,int sizeOf);
				std::vector<Triangle*> calculateConvexHull(
						const std::vector<Triangle*>& triangles,
						const std::vector<Vertex*>& vertices) const;

		};


		/*!
		 * \returns The center of the obb
		 */
		const Vector3_r Obb::getCenter() const {
			return Vector3_r(mState.m44[3][0], mState.m44[3][1], mState.m44[3][2]);
		}

		/*!
		 * \returns The dimension of the obb
		 */
		const Vector3_r& Obb::getDimension() const {
			return mDimension;
		}

		/*!
		 * \returns The reference üoint of the obb
		 */
		const Vector3_r& Obb::getReferencePoint() const {
			return mReferencePoint;
		}

		/*!
		 * \returns The rotation matrix of the obb
		 */
		const Matrix_r Obb::getRotation() const {
			return mState.GetRotationMatrix();
		}

		/*!
		 * \returns The state matrix of the obb
		 */
		const Matrix_r& Obb::getState() const {
			return mState;
		}

		/*!
		 * \brief translate this obb by \p translateBy
		 */
		void Obb::translate(const Vector3_r& translateBy) {
	#ifdef OBB_DEBUG
			std::cout << "CB: " << mState.getPosition();
	#endif
			mState.Translate(translateBy);
	#ifdef OBB_DEBUG
			std::cout << "; CA: " << mState.getPosition() << std::endl;
	#endif
		}

		/*!
		 * \brief rotate this obb by \p rotateBy
		 * ATTENTION: This MUST be a valid rotation matrix!
		 */
		void Obb::rotate(const Matrix_r& rotateBy) {
			mState.Translate(-mReferencePoint);
			mState *= rotateBy;
			mState.Translate(mReferencePoint);
		}

		/*!
		 * \brief transform this obb by \p transformBy
		 * ATTENTION: be aware that you can do nasty stuff with this method, even
		 * deformation of the obb is possible!!
		 */
		void Obb::transform(const Matrix_r& transformBy) {
			mState *= transformBy;
		}

		Obb& Obb::operator=(const Obb& otherObb) {
			mDimension = otherObb.getDimension();
			mState = otherObb.getState();
			mReferencePoint = otherObb.getReferencePoint();
			return *this;
		}

		/*!
		 *  \brief checks if 2 OBBs are the same
		 *  \return true, if they are the same, false otherwise
		 */
		inline bool Obb::operator==(const Obb& otherObb) const {
			if (    (mDimension == otherObb.getDimension()) &&
					(mReferencePoint == otherObb.getReferencePoint()) &&
					(IsEqual(mState, otherObb.getState()))) {
				return true;
			} else {
				return false;
			}
		}

		real Obb::calculateVolume() const {

			Vector3_r* vs = getVertices();
			real volume =
				Length(vs[0]-vs[1]) * Length(vs[0]-vs[4])* Length(vs[0]-vs[2]);
			delete[] vs;
			return volume;
		}

		/*!
		 * \brief Determine if given intervals overlap.
		 */
		inline bool Obb::overlap(float min1, float max1,
				float min2, float max2) const {
			return !(min1 > max2 || max1 < min2);
		}

		std::ostream& operator<<(std::ostream& os, const OgreOpcode::math::Obb& v);

	} // namespace math
} // namespace OgreOpcode


#endif

/*
 * vim: et sw=4 ts=4
 */
