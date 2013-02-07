#pragma once

namespace Skyrim
{
	namespace Game
	{
		class ScriptEngine
		{
		public:

			ScriptEngine();
			~ScriptEngine();

			void ReloadScripts();
			void Run();
			void RegisterForm(string& name);

		private:

			void ParseScript(const boost::filesystem::path& pPath);

			asIScriptEngine* engine;
			asIScriptContext* context;
		};
	}
}