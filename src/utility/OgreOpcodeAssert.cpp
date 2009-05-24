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

#include "utility/OgreOpcodeAssert.h"

#include <cstdio>
#include <cstdarg>

namespace OgreOpcode
{
	namespace utility
	{
		namespace Assert
		{
			struct AssertHandler
			{
				AssertHandler()
					: handler(&AssertHandler::DefaultHandler)
				{
				}

				static bool DefaultHandler(const char* condition, const char* msg, const char* file, const int line)
				{
					std::printf("%s(%d): Assert Failure: ", file, line);
					
					if (condition != NULL)
						std::printf("'%s' ", condition);

					if (msg != NULL)
						std::printf("%s", msg);

					std::printf("\n");

					return true;
				}

				Handler handler;
			};

			AssertHandler& GetAssertHandlerInstance()
			{
				static AssertHandler s_handler;
				return s_handler;
			}


			Handler GetHandler()
			{
				return GetAssertHandlerInstance().handler;
			}

			void SetHandler(Handler newHandler)
			{
				GetAssertHandlerInstance().handler = newHandler;
			}

			bool Report(const char* condition, const char* msg, const char* file, const int line)
			{
				return GetAssertHandlerInstance().handler(condition, msg, file, line);
			}

			bool ReportFormatted(const char* condition, const char* file, const int line, const char* msg, ...)
			{
				if (msg != NULL)
				{
					char messageBuffer[1024];
					{
						va_list args;
						va_start(args, msg);
						vsnprintf(messageBuffer, 1024, msg, args);
						va_end(args);
					}

					return Report(condition, messageBuffer, file, line);
				}

				return Report(condition, NULL, file, line);
			}
		} // namespace Assert
	} // namespace utility
} // namespace OgreOpcode
