#ifndef ASCRIPTMANAGER_H
#define ASCRIPTMANAGER_H

#include <vector>
#include <string>
#include <functional>
#include <angelscript.h>
#include "AScript/scriptstdstring/scriptstdstring.h"
#include "AScript/scriptbuilder/scriptbuilder.h"

using namespace std;

namespace hg
{
	class HexagonGame;

	class AScriptManager
	{
		private:
			asIScriptEngine* engine;
			HexagonGame* hgPtr;
			CScriptBuilder builder;

		public:
			AScriptManager(HexagonGame* mHgPtr);
			~AScriptManager();

			void executeFile(string mFileName);
			void registerFunc(void(*mFunc)());
	};
}

#endif // ASCRIPTMANAGER_H

