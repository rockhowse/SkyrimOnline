#include "stdafx.h"
#include "ScriptEngine.hpp"

using namespace boost::filesystem;

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		void MessageCallback(const asSMessageInfo *msg, void *param)
		{
			const char *type = "ERR ";
			if( msg->type == asMSGTYPE_WARNING ) 
				type = "WARN";
			else if( msg->type == asMSGTYPE_INFORMATION ) 
				type = "INFO";

			std::ostringstream os;
			os << msg->section << "(" << msg->row << ", " <<  msg->col << ") : " <<  type << " : " << msg->message;
			Framework::System::Log::Debug(os.str());
		}
		//--------------------------------------------------------------------------------
		void Print(std::string& pMessage)
		{
			Framework::System::Log::Debug(std::string("Script : ") + pMessage);
		}
		//--------------------------------------------------------------------------------

		//--------------------------------------------------------------------------------
		ScriptEngine::ScriptEngine()
		{
			engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

			engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

			RegisterStdString(engine);

			engine->RegisterGlobalFunction("void print(string &in)", asFUNCTION(Print), asCALL_CDECL);

			context = engine->CreateContext();

			RegisterReferenceClass(ScriptEngine);
			RegisterGlobal("ScriptEngine Script", this);

			RegisterMethod(ScriptEngine, "void RegisterForm(string& in)", RegisterForm);
			RegisterMethod(ScriptEngine, "void RegisterWorld()", RegisterWorld);
		
		}
		//--------------------------------------------------------------------------------
		ScriptEngine::~ScriptEngine()
		{
			context->Release();
			engine->Release();
		}
		//--------------------------------------------------------------------------------
		void ScriptEngine::ReloadScripts()
		{
			boost::filesystem::path slash("/");
			std::wstring preferredSlash = slash.make_preferred().native();

			path p(std::wstring(L".") + preferredSlash + std::wstring(L"Scripts"));
			if(exists(p))
			{
				std::vector<path> paths;
				std::copy(directory_iterator(p), directory_iterator(), std::back_inserter(paths));
				std::sort(paths.begin(), paths.end());

				for (auto it = paths.begin(); it != paths.end(); ++it)
				{

					if(!is_directory(*it) && it->has_extension() && it->extension().string() == std::string(".as"))
					{
						ParseScript(*it);
					}
				}
			}

			Framework::System::Log::Print("");
		}
		//--------------------------------------------------------------------------------
		void ScriptEngine::ParseScript(const path& pPath)
		{
			CScriptBuilder builder;
			
			string name = pPath.filename().string();
			name = name.substr(0, name.size() - 3);

			builder.StartNewModule(engine, name.c_str());
			int r = builder.AddSectionFromFile(pPath.string().c_str());
			if(r < 0)
			{
				Framework::System::Log::Error(std::string("Failed to build : ") + name); 
				return;
			}

			r = builder.BuildModule();
			if(r < 0)
			{
				Framework::System::Log::Error(std::string("Failed to build : ") + name); 
				return;
			}
			else
			{
				Framework::System::Log::Debug(std::string("Built script : ") + name);

				Call(name, "void RegisterSelf()");
			}
		}
		//--------------------------------------------------------------------------------
		void ScriptEngine::RegisterForm(string& name)
		{
			mBindings[name].push_back(currentModule);
		}
		//--------------------------------------------------------------------------------
		void ScriptEngine::RegisterWorld()
		{
			RegisterForm(string("[WORLD]"));
		}
		//--------------------------------------------------------------------------------
	}
}