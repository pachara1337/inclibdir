// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2013 NVIDIA Corporation. All rights reserved.
#ifndef PVD_IMMEDIATE_RENDERER_H
#define PVD_IMMEDIATE_RENDERER_H
#include "physxvisualdebuggersdk/PvdObjectModelBaseTypes.h"
#include "physxprofilesdk/PxProfileEventBufferClientManager.h"
#include "foundation/PxVec3.h"
#include "foundation/PxTransform.h"

namespace physx { namespace debugger { namespace renderer {
	
	struct PvdPoint
	{
		PxVec3		pos;
		PvdColor	color;
		PvdPoint(const PxVec3& pos, const PvdColor& color)
			: pos(pos), color(color) {}
		PvdPoint(){}
	};
	
	struct PvdLine
	{
		PvdLine(const PxVec3& pos0, const PxVec3& pos1, const PvdColor& color)
			: pos0(pos0), color0(color), pos1(pos1), color1(color) {}
		PvdLine(){}

		PxVec3		pos0;
		PvdColor	color0;
		PxVec3		pos1;
		PvdColor	color1;
	};

	
	struct PvdTriangle
	{
		PvdTriangle(const PxVec3& pos0, const PxVec3& pos1, const PxVec3& pos2, const PvdColor& color)
			: pos0(pos0), color0(color), pos1(pos1), color1(color), pos2(pos2), color2(color) {}
		PvdTriangle(){}
		PxVec3		pos0;
		PvdColor	color0;
		PxVec3		pos1;
		PvdColor	color1;
		PxVec3		pos2;
		PvdColor	color2;
	};

	struct PvdTransform
	{
		PxTransform transform;
		PvdColor xAxisColor;
		PvdColor yAxisColor;
		PvdColor zAxisColor;
		PvdTransform( const PxTransform& _transform, PxU32 x, PxU32 y, PxU32 z )
			: transform( _transform )
			, xAxisColor( x )
			, yAxisColor( y )
			, zAxisColor( z )
		{
		}
	};

	class PvdImmediateRenderer : public PxProfileEventBufferClientManager
	{
	protected:
		virtual ~PvdImmediateRenderer(){}
	public:
		virtual void addRef() = 0;
		virtual void release() = 0;

		//Instance to associate the further rendering with.
		virtual void setInstanceId( const void* instanceId ) = 0;
		//Draw these points associated with this instance
		virtual void drawPoints( const PvdPoint* points, PxU32 count ) = 0;
		//Draw these lines associated with this instance
		virtual void drawLines( const PvdLine* lines, PxU32 count ) = 0;
		//Draw these triangles associated with this instance
		virtual void drawTriangles( const PvdTriangle* triangles, PxU32 count ) = 0;

		//Constraint visualization routines
		virtual void visualizeJointFrames( const PxTransform& parent, const PxTransform& child ) = 0;
		virtual void visualizeLinearLimit( const PxTransform& t0, const PxTransform& t1, PxF32 value, bool active ) = 0;
		virtual void visualizeAngularLimit( const PxTransform& t0, PxF32 lower, PxF32 upper, bool active) = 0;
		virtual void visualizeLimitCone( const PxTransform& t, PxF32 ySwing, PxF32 zSwing, bool active) = 0;
		virtual void visualizeDoubleCone( const PxTransform& t, PxF32 angle, bool active) = 0;

		//Clear the immedate buffer.
		virtual void flushRenderEvents() = 0;

		static PvdImmediateRenderer& create( PxAllocatorCallback& alloc, PxU32 bufferSize = 0x2000 );
	};

}}}

#endif