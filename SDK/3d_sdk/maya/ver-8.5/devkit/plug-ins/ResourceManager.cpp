//-
// ==========================================================================
// Copyright (C) 2005 ATI Technologies Inc. All rights reserved.
//
// Copyright (C) 1995 - 2006 Autodesk, Inc. and/or its licensors.  All 
// rights reserved.
//
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors, which is protected by U.S. and Canadian federal copyright 
// law and by international treaties.
//
// The Data is provided for use exclusively by You. You have the right 
// to use, modify, and incorporate this Data into other products for 
// purposes authorized by the Autodesk software license agreement, 
// without fee.
//
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the 
// following disclaimer, must be included in all copies of the 
// Software, in whole or in part, and all derivative works of 
// the Software, unless such copies or derivative works are solely 
// in the form of machine-executable object code generated by a 
// source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
// PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE, OR 
// TRADE PRACTICE. IN NO EVENT WILL AUTODESK AND/OR ITS LICENSORS 
// BE LIABLE FOR ANY LOST REVENUES, DATA, OR PROFITS, OR SPECIAL, 
// DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK 
// AND/OR ITS LICENSORS HAS BEEN ADVISED OF THE POSSIBILITY 
// OR PROBABILITY OF SUCH DAMAGES.
//
// ==========================================================================
//+

#include "ResourceManager.h"


std::vector<GLuint> ResourceManager::sTextureList;
std::vector<GLuint> ResourceManager::sAsmProgramList;
std::vector<GLuint> ResourceManager::sProgramList;
std::vector<GLuint> ResourceManager::sShaderList;


//
//
//
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::recover() 
{
	if (sTextureList.size())
		glDeleteTextures( (GLsizei) sTextureList.size(), &(*sTextureList.begin()));

	if (sAsmProgramList.size())
		glDeleteProgramsARB( (GLsizei) sAsmProgramList.size(), &(*sAsmProgramList.begin()));


	for (std::vector<GLuint>::iterator it=sProgramList.begin(); it<sProgramList.end(); it++) {
		glDeleteObject( *it); 
	}
	{
		for (std::vector<GLuint>::iterator it=sShaderList.begin(); it<sShaderList.end(); it++) {
			glDeleteObject( *it); 
		}
	}

	sTextureList.clear();
	sAsmProgramList.clear();
	sProgramList.clear();
	sShaderList.clear();
	
	GL_CHECK;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::destroyTexture( GLuint tex) {
  sTextureList.push_back(tex);
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::destroyAsmProgram( GLuint prog) {
  sAsmProgramList.push_back(prog);
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::destroyProgram( GLuint prog) {
  sProgramList.push_back(prog);
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void ResourceManager::destroyShader( GLuint shad){
  sShaderList.push_back(shad);
}

