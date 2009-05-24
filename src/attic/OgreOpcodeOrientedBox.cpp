/// ////////////////////////////////////////////////////////////////////////////
///  @file OgreOpcodeOrientedBox.cpp
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

#include "OgreOpcodeOrientedBox.h"

using namespace Ogre;
namespace OgreOpcode
{
	//------------------------------------------------------------------------
	//bool OrientedBox::intersects( const Details::bbox3& box ) const
	//{ 
	//	// Optimize this: return intersects( OrientedBox(box) );

	//	//translation, in parent frame (note: A = this, B = obb)		   
	//	Vector3 v = box.getCenter() - center;		   
	//	Vector3 boxExtents = box.getExtents();

	//	//translation, in A's frame
	//	Vector3 T( v.dotProduct( rot.GetColumn(0)),
	//		v.dotProduct( rot.GetColumn(1)),
	//		v.dotProduct( rot.GetColumn(2)) );

	//	//B's basis with respect to A's local frame
	//	Real R[3][3];
	//	Real FR[3][3];
	//	Real ra, rb, t;
	//	long i, k;
	//	//calculate rotation matrix from "obb" to "this" - palso recomputes the fabs matrix
	//	for( i=0 ; i<3 ; i++ )
	//	{
	//		for( k=0 ; k<3 ; k++ )
	//		{
	//			R[i][k] = rot.GetColumn(k)[i];
	//			// fabs and shift borrowed from RAPID
	//			FR[i][k] = 1e-6f + Math::Abs(R[i][k]);
	//		}
	//	}

	//	// Separating axis theorem: test of all 15 potential separating axes
	//	// These axes are always parallel to each OBB edges or its normal plane
	//	const Vector3 &a = extents,
	//		&b = boxExtents;

	//	// First stage: each obb's axis!
	//	//A's basis vectors
	//	for( i=0 ; i<3 ; i++ )
	//	{
	//		ra = a[i];
	//		rb = b.x*FR[i][0] + b.y*FR[i][1] + b.z*FR[i][2];
	//		t = Math::Abs( T[i] );

	//		if( t > ra + rb ) return false;
	//	}

	//	//B's basis vectors
	//	for( k=0 ; k<3 ; k++ )
	//	{
	//		ra = a.x*FR[0][k] + a.y*FR[1][k] + a.z*FR[2][k];
	//		rb = b[k];
	//		t  = Math::Abs( T[0]*R[0][k] + T[1]*R[1][k] + T[2]*R[2][k] );

	//		if( t > ra + rb ) return false;
	//	}

	//	// Second stage: 9 cross products
	//	//L = A0 x B0
	//	ra = a[1]*FR[2][0] + a[2]*FR[1][0];
	//	rb = b[1]*FR[0][2] + b[2]*FR[0][1];
	//	t  = Math::Abs( T[2]*R[1][0] -  T[1]*R[2][0] );
	//	if( t > ra + rb ) return false;

	//	//L = A0 x B1
	//	ra = a[1]*FR[2][1] + a[2]*FR[1][1];
	//	rb = b[0]*FR[0][2] + b[2]*FR[0][0];
	//	t = Math::Abs( T[2]*R[1][1] - T[1]*R[2][1] );
	//	if( t > ra + rb ) return false;

	//	//L = A0 x B2
	//	ra = a[1]*FR[2][2] + a[2]*FR[1][2];
	//	rb = b[0]*FR[0][1] + b[1]*FR[0][0];
	//	t = Math::Abs( T[2]*R[1][2] - T[1]*R[2][2] );
	//	if( t > ra + rb ) return false;

	//	//L = A1 x B0
	//	ra = a[0]*FR[2][0] + a[2]*FR[0][0];
	//	rb = b[1]*FR[1][2] + b[2]*FR[1][1];
	//	t = Math::Abs( T[0]*R[2][0] - T[2]*R[0][0] );
	//	if( t > ra + rb ) return false;

	//	//L = A1 x B1
	//	ra = a[0]*FR[2][1] + a[2]*FR[0][1];
	//	rb = b[0]*FR[1][2] + b[2]*FR[1][0];
	//	t = Math::Abs( T[0]*R[2][1] - T[2]*R[0][1] );
	//	if( t > ra + rb ) return false;

	//	//L = A1 x B2
	//	ra = a[0]*FR[2][2] + a[2]*FR[0][2];
	//	rb = b[0]*FR[1][1] + b[1]*FR[1][0];
	//	t = Math::Abs( T[0]*R[2][2] - T[2]*R[0][2] );
	//	if( t > ra + rb ) return false;

	//	//L = A2 x B0
	//	ra = a[0]*FR[1][0] + a[1]*FR[0][0];
	//	rb = b[1]*FR[2][2] + b[2]*FR[2][1];
	//	t =  Math::Abs( T[1]*R[0][0] - T[0]*R[1][0] );
	//	if( t > ra + rb ) return false;

	//	//L = A2 x B1
	//	ra = a[0]*FR[1][1] + a[1]*FR[0][1];
	//	rb = b[0]*FR[2][2] + b[2]*FR[2][0];
	//	t = Math::Abs( T[1]*R[0][1] - T[0]*R[1][1] );
	//	if( t > ra + rb ) return false;

	//	//L = A2 x B2
	//	ra = a[0]*FR[1][2] + a[1]*FR[0][2];
	//	rb = b[0]*FR[2][1] + b[1]*FR[2][0];
	//	t = Math::Abs( T[1]*R[0][2] - T[0]*R[1][2] );
	//	if( t > ra + rb )	return false;


	//	// Phew! No separating axis found, no overlap!
	//	return true;
	//}
	//------------------------------------------------------------------------
	bool OrientedBox::intersects( const OrientedBox& obb ) const
	{           
		//translation, in parent frame (note: A = this, B = obb)
		Vector3 v = obb.center - center;		   
		//translation, in A's frame
		Vector3 T( v.dotProduct( rot.GetColumn(0)),
			v.dotProduct( rot.GetColumn(1)),
			v.dotProduct( rot.GetColumn(2)) );

		//B's basis with respect to A's local frame
		Real R[3][3];
		Real FR[3][3];
		Real ra, rb, t;
		long i, k;
		//calculate rotation matrix from "obb" to "this" - palso recomputes the fabs matrix
		for( i=0 ; i<3 ; i++ )
		{
			for( k=0 ; k<3 ; k++ )
			{
				R[i][k] = rot.GetColumn(i).dotProduct(obb.rot.GetColumn(k) );
				// fabs and shift borrowed from RAPID
				FR[i][k] = 1e-6f + Math::Abs(R[i][k]);
			}
		}

		// Separating axis theorem: test of all 15 potential separating axes
		// These axes are always parallel to each OBB edges or its normal plane
		const Vector3 &a = extents,
			&b = obb.extents;

		// First stage: each obb's axis!
		//A's basis vectors
		for( i=0 ; i<3 ; i++ )
		{
			ra = a[i];
			rb = b.x*FR[i][0] + b.y*FR[i][1] + b.z*FR[i][2];
			t = Math::Abs( T[i] );

			if( t > ra + rb ) return false;
		}

		//B's basis vectors
		for( k=0 ; k<3 ; k++ )
		{
			ra = a.x*FR[0][k] + a.y*FR[1][k] + a.z*FR[2][k];
			rb = b[k];
			t  = Math::Abs( T[0]*R[0][k] + T[1]*R[1][k] + T[2]*R[2][k] );

			if( t > ra + rb ) return false;
		}

		// Second stage: 9 cross products
		//L = A0 x B0
		ra = a[1]*FR[2][0] + a[2]*FR[1][0];
		rb = b[1]*FR[0][2] + b[2]*FR[0][1];
		t  = Math::Abs( T[2]*R[1][0] -  T[1]*R[2][0] );
		if( t > ra + rb ) return false;

		//L = A0 x B1
		ra = a[1]*FR[2][1] + a[2]*FR[1][1];
		rb = b[0]*FR[0][2] + b[2]*FR[0][0];
		t = Math::Abs( T[2]*R[1][1] - T[1]*R[2][1] );
		if( t > ra + rb ) return false;

		//L = A0 x B2
		ra = a[1]*FR[2][2] + a[2]*FR[1][2];
		rb = b[0]*FR[0][1] + b[1]*FR[0][0];
		t = Math::Abs( T[2]*R[1][2] - T[1]*R[2][2] );
		if( t > ra + rb ) return false;

		//L = A1 x B0
		ra = a[0]*FR[2][0] + a[2]*FR[0][0];
		rb = b[1]*FR[1][2] + b[2]*FR[1][1];
		t = Math::Abs( T[0]*R[2][0] - T[2]*R[0][0] );
		if( t > ra + rb ) return false;

		//L = A1 x B1
		ra = a[0]*FR[2][1] + a[2]*FR[0][1];
		rb = b[0]*FR[1][2] + b[2]*FR[1][0];
		t = Math::Abs( T[0]*R[2][1] - T[2]*R[0][1] );
		if( t > ra + rb ) return false;

		//L = A1 x B2
		ra = a[0]*FR[2][2] + a[2]*FR[0][2];
		rb = b[0]*FR[1][1] + b[1]*FR[1][0];
		t = Math::Abs( T[0]*R[2][2] - T[2]*R[0][2] );
		if( t > ra + rb ) return false;

		//L = A2 x B0
		ra = a[0]*FR[1][0] + a[1]*FR[0][0];
		rb = b[1]*FR[2][2] + b[2]*FR[2][1];
		t =  Math::Abs( T[1]*R[0][0] - T[0]*R[1][0] );
		if( t > ra + rb ) return false;

		//L = A2 x B1
		ra = a[0]*FR[1][1] + a[1]*FR[0][1];
		rb = b[0]*FR[2][2] + b[2]*FR[2][0];
		t = Math::Abs( T[1]*R[0][1] - T[0]*R[1][1] );
		if( t > ra + rb ) return false;

		//L = A2 x B2
		ra = a[0]*FR[1][2] + a[1]*FR[0][2];
		rb = b[0]*FR[2][1] + b[1]*FR[2][0];
		t = Math::Abs( T[1]*R[0][2] - T[0]*R[1][2] );
		if( t > ra + rb )	return false;


		// Phew! No separating axis found, no overlap!
		return true;
	}
	//------------------------------------------------------------------------
}

