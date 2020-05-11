#pragma once

#include <Core.h>

namespace Volt
{
	template<typename T>
	class CInstance
	{
	public:
		static T& Get()
		{
			if (!pInstance) pInstance = new T;

			return *pInstance;
		}

		template<typename ... Args>
		static T& Get(Args&&... args)
		{
			if (!pInstance) pInstance = new T(std::forward<Args>(args)...);

			return *pInstance;
		}

		static void Delete()
		{
			if (pInstance) delete pInstance;
		}

	private:
		static inline T* pInstance = nullptr;
	};
}