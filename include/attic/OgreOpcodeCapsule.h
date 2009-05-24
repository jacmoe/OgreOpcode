/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreCapsule.h
///  @brief This class represents a Capsule, which is defined by 2 endpoints and a radius.
///			You can interpret it as a sphere that is sweept along a line.
///
///  @author The OgreOpcode Team @date 23-02-2005
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
#ifndef __OgreOpcodeCapsule_h__
#define __OgreOpcodeCapsule_h__

#include "OgreOpcodeExports.h"
#include "OgreOpcodeMath.h"


namespace OgreOpcode
{
	/// Represents a Capsule defined by 2 endpoints and a radius
	/// TODO: add methods to this capsule.
	class _OgreOpcode_Export Capsule
	{
	public:

		/** Default constructor: degenerated as an unitary sphere at origin
		 */
		Capsule():start(),end(),radius(1.0)
		{
		}

		/** Copy-constructor
		 */
		Capsule(const Capsule& c):start(c.start),end(c.end),radius(c.radius)
		{
		}

		/** Complete constructor
		 */
		Capsule(const Ogre::Vector3& s, const Ogre::Vector3& e, Ogre::Real r ):start(s),end(e),radius(r)
		{
		}

		/** Complete, headache constructor
		 */
		Capsule( Ogre::Real sx, Ogre::Real sy, Ogre::Real sz,
			     Ogre::Real ex, Ogre::Real ey, Ogre::Real ez, 
				 Ogre::Real r
			   ):start(sx,sy,sz),end(ex,ey,ez),radius(r)
		{
		}

		/// Gets the length of this line segment
		Ogre::Real length() const {  return (start - end).length(); }
		/// Gets the squared length of this line segment
		Ogre::Real length2() const {  return (start - end).squaredLength(); }

		/// Gets the surface area of this capsule
		Ogre::Real area() const
		{					
			return Ogre::Math::TWO_PI*radius*(2.0*radius + length() );
		}

		/// Gets the volume are this capsule
		Ogre::Real volume() const
		{
			return Ogre::Math::PI*radius*radius*( 1.333333333333333*length() );
		}
// --------------------------------------------------------------------
// intersection tests

		/** Does this capsule contain the given point?
		 */
		bool contains( const Ogre::Vector3& point ) const;

		/** Tests intersection between this capsule and the given Axis-Aligned
		 *  Bounding Box
         */
		//bool intersects( const Aabb& aabb ) const;

		/** Tests intersection between this capsule and the given sphere
		 */
		//bool intersects( const sphere& s ) const;

		/** Tests intersection between this capsule and the given Oriented Bounding Box
		 */
		bool intersects( const OrientedBox& obb ) const;

		/** Tests intersection between this capsule and the given one
		 */
		bool intersects( const Capsule& cap ) const;


		/** The start point of this capsule.
		 */
		Ogre::Vector3 start;
		/** The end point of this capsule.
		 */
		Ogre::Vector3 end;
		/** The radius of this capsule.
		 */
		Ogre::Real radius;			
	};
}


#endif
