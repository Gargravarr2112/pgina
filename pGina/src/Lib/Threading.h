/*
	Copyright (c) 2011, pGina Team
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
		* Redistributions of source code must retain the above copyright
		  notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright
		  notice, this list of conditions and the following disclaimer in the
		  documentation and/or other materials provided with the distribution.
		* Neither the name of the pGina Team nor the names of its contributors
		  may be used to endorse or promote products derived from this software without
		  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include <Windows.h>

namespace pGina
{
	namespace Threading
	{
		class Mutex
		{
		public:
			Mutex();

			bool Lock();
			bool Unlock();

		private:
			HANDLE m_mutexHandle;
		};

		class ScopedLock
		{
		public:
			ScopedLock(Mutex& m) :
				m_mutex(m) { m_mutex.Lock(); }
			~ScopedLock() { m_mutex.Unlock(); }

		private:
			Mutex& m_mutex;
		};

		class Thread
		{
		public:
			void Start();
			void Stop();

		protected:
			Thread();
			virtual ~Thread();
			virtual DWORD ThreadMain() = 0;
			bool Running();
			void Running(bool v);

		protected:
			Mutex m_mutex;

		private:
			static DWORD WINAPI _internal_threadmain(LPVOID arg);
			HANDLE m_threadHandle;
			bool m_running;
		};
	}
}