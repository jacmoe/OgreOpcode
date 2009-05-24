/*
* Copyright (c) 2008, Power of Two Games LLC
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of Power of Two Games LLC nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY POWER OF TWO GAMES LLC ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL POWER OF TWO GAMES LLC BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __OgreOpcodeAssert_h__
#define __OgreOpcodeAssert_h__

#define OGREOPCODE_ASSERTS_ENABLED

namespace OgreOpcode
{
	namespace utility
	{
		namespace Assert
		{
			typedef bool (*Handler)(const char* condition, const char* msg, const char* file, int line);

			Handler GetHandler();
			void SetHandler(Handler newHandler);
			
			bool Report(const char* condition, const char* msg, const char* file, int line);
			bool ReportFormatted(const char* condition, const char* file, int line, const char* msg, ...);
		} // namespace Assert
	} // namespace utility
} // namespace OgreOpcode

#define OGREOPCODE_HALT() do { __debugbreak(); } while(0)
#define OGREOPCODE_UNUSED(x) do { (void)sizeof(x); } while(0)

#ifdef OGREOPCODE_ASSERTS_ENABLED
	#define OGREOPCODE_ASSERT(cond) \
	do { if ((!(cond)) && OgreOpcode::utility::Assert::Report(#cond, 0, __FILE__, __LINE__)) \
			OGREOPCODE_HALT(); } while(0)

	#define OGREOPCODE_ASSERT_MSG(cond, msg, ...) \
		do { if ((!(cond)) && OgreOpcode::utility::Assert::ReportFormatted(#cond, __FILE__, __LINE__, (msg), __VA_ARGS__)) \
			OGREOPCODE_HALT(); } while(0)

	#define OGREOPCODE_ASSERT_FAIL(msg, ...) \
		do { if (OgreOpcode::utility::Assert::ReportFormatted(NULL, __FILE__, __LINE__, (msg), __VA_ARGS__)) \
			OGREOPCODE_HALT(); } while(0)
#else
	#define OGREOPCODE_ASSERT(condition) \
		do { OGREOPCODE_UNUSED(condition); } while(0)
	#define OGREOPCODE_ASSERT_MSG(condition, msg, ...) \
		do { OGREOPCODE_UNUSED(condition); OGREOPCODE_UNUSED(msg); } while(0)
	#define OGREOPCODE_ASSERT_FAIL(msg, ...) \
		do { OGREOPCODE_UNUSED(msg); } while(0)
#endif

#define OGREOPCODE_STATIC_ASSERT(x) \
	typedef char OgreOpcodeStaticAssert[(x) ? 1 : -1];

#endif // __OgreOpcodeAssert_h__

