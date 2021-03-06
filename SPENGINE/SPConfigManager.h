//////////////////////////////////////////////////////////////////////////
/// @file		SPConfigManager.h the header file of SPConfigManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-12
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPConfig.h"
#include "SPSingleton.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief ConfigManager class to hold game config.
	//////////////////////////////////////////////////////////////////////
	class SPConfigManager : public SPSingleton<SPConfigManager>
	{
		string configFile;		///< File path;
		SPConfig currentConfig; ///< Current config.

	public:
		SPConfigManager(void);
		~SPConfigManager(void);

		bool LoadConfig(string path);
		bool SetConfig(SPConfig &config);
		SPConfig GetCurrentConfig();
	};
}


