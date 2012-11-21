#include "AScriptManager.h"
#include "Utils/Utils.h"

namespace hg
{
	void messageCallback(const asSMessageInfo *msg, void *param) { log(msg->message); }
	void test(string mString) { log(mString); }

	AScriptManager::AScriptManager(HexagonGame* mHgPtr) : hgPtr{mHgPtr}
	{
		engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
		engine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_CDECL);
		RegisterStdString(engine);

		// Register the function that we want the scripts to call
		engine->RegisterGlobalFunction("void test(string mString)", asFUNCTION(test), asCALL_CDECL);		
	}

	AScriptManager::~AScriptManager() { engine->Release(); }

	void AScriptManager::executeFile(string mFileName)
	{
		int r{0};

		r = builder.StartNewModule(engine, "MyModule");
		if( r < 0 ) { log("Unrecoverable error while starting a new module.\n"); return; }

		r = builder.AddSectionFromFile(("AScripts/" + toStr(mFileName)).c_str());
		if( r < 0 ) { log("Please correct the errors in the script and try again.\n"); return; }

		r = builder.BuildModule();
		if( r < 0 ) { log("Please correct the errors in the script and try again.\n"); return; }

		// Find the function that is to be called.
		asIScriptModule *mod = engine->GetModule("MyModule");
		asIScriptFunction *func = mod->GetFunctionByDecl("void main()");
		if( func == 0 ) { log("The script must have the function 'void main()'. Please add it and try again.\n"); return; }

		// Create our context, prepare it, and then execute
		asIScriptContext *ctx = engine->CreateContext();
		ctx->Prepare(func);
		r = ctx->Execute();
		if( r != asEXECUTION_FINISHED ) if( r == asEXECUTION_EXCEPTION ) log(ctx->GetExceptionString());
	}

	void AScriptManager::registerFunc(void(*mFunc)())
	{
		engine->RegisterGlobalFunction("void run()", asFUNCTION(mFunc), asCALL_CDECL);
	}
}

