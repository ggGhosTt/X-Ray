
#ifndef _MGeometryRequirements
#define _MGeometryRequirements
//
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All 
// rights reserved.
// 
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors,  which is protected by U.S. and Canadian federal copyright law 
// and by international treaties.
// 
// The Data may not be disclosed or distributed to third parties or be 
// copied or duplicated, in whole or in part, without the prior written 
// consent of Autodesk.
// 
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the following 
// disclaimer, must be included in all copies of the Software, in whole 
// or in part, and all derivative works of the Software, unless such copies 
// or derivative works are solely in the form of machine-executable object 
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, 
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO 
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST 
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR 
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS 
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES. 
// ==========================================================================
//+
//
// CLASS:    MGeometryRequirements
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MGeometryRequirements)
//
// The MGeometryRequirements class describes the set of geometry data 
// elements required by an geometry user. For example, a material can
// specify that is needs position, normal and UV set "a" to render a
// surface.
//
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MObject.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MUintArray.h>
#include <maya/MTypes.h>

class MGeometryManager;

// *****************************************************************************

// CLASS DECLARATION (MGeometryRequirements)

/// Image manipulation
/**
This class provides methods for reading file images stored on disk.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYARENDER_EXPORT MGeometryRequirements  
{
public:
	///
					MGeometryRequirements();
	///
					void addPosition();
	///
					void addComponentId();
	///
					void addNormal();
	///
					void addTexCoord( const MString& uvSetName);
	///
					void addTangent( const MString& uvSetName);
	///
					void addBinormal( const MString& uvSetName);
	///
					void addColor( const MString& colorSetName);

protected:
	MUintArray		mAttributes;
	MStringArray	mAttributeNames;

private:
	void			addItem( unsigned int, const MString &setName );
	bool			getRequirements( void * ) const;

	friend class MGeometryManager;
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MGeometryRequirements */
