/// ////////////////////////////////////////////////////////////////////////////
/// @file OgreOpcodeExports.h
/// @brief Export macros and common stuff.
///
/// @author The OgreOpcode Team
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
#ifndef __OgreOpcodeExports_h__
#define __OgreOpcodeExports_h__

// Turn deprecation warnings off when using VC8
#if (_MSC_VER >= 1400)
#pragma warning (disable : 4996)
#pragma warning( disable: 4267 )  // conversion from 'size_t' to whatever
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 1
#endif
#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE 1
#endif
#endif //VC8


#if defined( WIN32 ) && !defined ( __MINGW32__ ) && !defined ( OGREOPCODE_STATIC )
#	if defined( OGREOPCODE_EXPORTS )
#		define _OgreOpcode_Export __declspec( dllexport )
#	else
#		define _OgreOpcode_Export __declspec( dllimport )
#	endif
#else
#	define _OgreOpcode_Export
#endif

#endif // __OgreOpcodeExports_h__
