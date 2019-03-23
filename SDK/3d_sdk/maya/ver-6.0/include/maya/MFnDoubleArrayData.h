
#ifndef _MFnDoubleArrayData
#define _MFnDoubleArrayData
//
//-
// ==========================================================================
// Copyright (C) Alias Systems Corp., and/or its licensors ("Alias").  
// All rights reserved.  These coded instructions, statements, computer  
// programs, and/or related material (collectively, the "Material")
// contain unpublished information proprietary to Alias, which is
// protected by Canadian and US federal copyright law and by international
// treaties. This Material may not be disclosed to third parties, or be copied
// or duplicated, in whole or in part, without the prior written consent of
// Alias.  ALIAS HEREBY DISCLAIMS ALL WARRANTIES RELATING TO THE MATERIAL,
// INCLUDING, WITHOUT LIMITATION, ANY AND ALL EXPRESS OR IMPLIED WARRANTIES OF
// NON-INFRINGEMENT, MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
// IN NO EVENT SHALL ALIAS BE LIABLE FOR ANY DAMAGES WHATSOEVER, WHETHER DIRECT,
// INDIRECT, SPECIAL, OR PUNITIVE, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, OR IN EQUITY, ARISING OUT OF OR RELATED TO THE
// ACCESS TO, USE OF, OR RELIANCE UPON THE MATERIAL.
// ==========================================================================
//+
//
// CLASS:    MFnDoubleArrayData
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnDoubleArrayData)
//
// MFnDoubleArrayData allows the creation and manipulation of MDoubleArray data
// objects for use in the dependency graph.  
//
// If a user written dependency node either accepts or produces MDoubleArrays,
// then this class is used to extract or create the data that comes from or
// goes to other dependency graph nodes.  The MDataHandle::type method will
// return kDoubleArray when data of this type is present.  To access it, the
// MDataHandle::data method is used to get an MObject for the data and this 
// should then be used to initialize an instance of MFnDoubleArrayData.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnData.h>

// *****************************************************************************

// DECLARATIONS

class MDoubleArray;

// *****************************************************************************

// CLASS DECLARATION (MFnDoubleArrayData)

/// double array function set for dependency node data
/**
  Create and manipulate MDoubleArray dependency node data.
*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MFnDoubleArrayData : public MFnData 
{

	declareMFn(MFnDoubleArrayData, MFnData);

public:
	///
	unsigned		length( MStatus* ReturnStatus = NULL ) const;
	///
	double          operator[]( unsigned index ) const;
	///
	double&	        operator[]( unsigned index );
	///
	MStatus			copyTo( MDoubleArray& ) const;
	///
	MStatus			set( const MDoubleArray& newArray );
	///
	MDoubleArray	array( MStatus*ReturnStatus=NULL );
	///
	MObject			create( MStatus*ReturnStatus=NULL );
	///
	MObject			create( const MDoubleArray& in, MStatus*ReturnStatus=NULL );

protected:
// No protected members

private:
// No private members

};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MFnDoubleArrayData */
