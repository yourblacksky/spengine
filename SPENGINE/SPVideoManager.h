//////////////////////////////////////////////////////////////////////////
/// @file		SPVideoManager.h the header file of SPVideoManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPComponent.h"
#include "SPVideo.h"
#include "SPStringMap.h"
#include "SPSingleton.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////
	/// @brief SPVideoManager class to hold and manage videos.
	///
	//////////////////////////////////////////////////////////////////
	class SPVideoManager : 
		public SPComponent,
		public SPSingleton<SPVideoManager>
	{
		SPWStringMap<SPVideoPtr> videos;

	public:
		SPVideoManager(void);
		~SPVideoManager(void);

		SPVideoPtr GetVideo(SPString name);
		bool CreateVideo(SPString name);
		bool ReleaseVideo(SPString name);

		bool Update(float timeDelta);
		bool Unload();
		bool Reload();

		virtual bool LoadFromString(SPString stringStream);
		virtual SPString SaveAsString();
	};

}

