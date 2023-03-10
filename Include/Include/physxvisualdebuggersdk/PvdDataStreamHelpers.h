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
#ifndef PVD_DATA_STREAM_HELPERS_H
#define PVD_DATA_STREAM_HELPERS_H
#include "physxvisualdebuggersdk/PvdObjectModelBaseTypes.h"
namespace physx { namespace debugger { namespace comm {
	class PvdPropertyDefinitionHelper
	{
	protected:
		virtual ~PvdPropertyDefinitionHelper(){}
	public:
		/**
			Push a name c such that it appends such as a.b.c.
		*/
		virtual void pushName( const char* inName, const char* inAppendStr = "." ) = 0;
		/**
			Push a name c such that it appends like a.b[c]
		*/
		virtual void pushBracketedName( const char* inName, const char* leftBracket = "[", const char* rightBracket = "]" ) = 0;
		/**
		 *	Pop the current name
		 */
		virtual void popName() = 0;

		virtual void clearNameStack() = 0;
		/**
		 *	Get the current name at the top of the name stack.  
		 *	Would return "a.b.c" or "a.b[c]" in the above examples.
		 */
		virtual const char* getTopName() = 0;

		virtual void addNamedValue( const char* name, PxU32 value ) = 0;
		virtual void clearNamedValues() = 0;
		virtual DataRef<NamedValue> getNamedValues() = 0;

		/**
		 *	Define a property using the top of the name stack and the passed-in semantic
		 */
		virtual void createProperty( const NamespacedName& clsName, const char* inSemantic, const NamespacedName& dtypeName, PropertyType::Enum propType = PropertyType::Scalar ) = 0;

		template<typename TClsType, typename TDataType>
		void createProperty( const char* inSemantic = "", PropertyType::Enum propType = PropertyType::Scalar )
		{
			createProperty( getPvdNamespacedNameForType<TClsType>(), inSemantic, getPvdNamespacedNameForType<TDataType>(), propType );
		}

		//The datatype used for instances needs to be pointer unless you actually have Pvd::InstanceId members on your value structs.
		virtual void addPropertyMessageArg( const NamespacedName& inDatatype, PxU32 inOffset, PxU32 inSize ) = 0;

		template<typename TDataType>
		void addPropertyMessageArg( PxU32 offset )
		{
			addPropertyMessageArg( getPvdNamespacedNameForType<TDataType>(), offset, static_cast<PxU32>( sizeof( TDataType ) ) );
		}
		virtual void addPropertyMessage( const NamespacedName& clsName, const NamespacedName& msgName, PxU32 inStructSizeInBytes ) = 0;
		template<typename TClsType, typename TMsgType>
		void addPropertyMessage()
		{
			addPropertyMessage( getPvdNamespacedNameForType<TClsType>(), getPvdNamespacedNameForType<TMsgType>(), static_cast<PxU32>( sizeof( TMsgType ) ) );
		}
		virtual void clearPropertyMessageArgs() = 0;

		void clearBufferedData() { clearNameStack(); clearPropertyMessageArgs(); clearNamedValues(); }
	};
}}}
#endif