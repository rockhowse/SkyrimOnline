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

			template <typename... Args>
			void FireEvent(const string& formName, const string& function, Args... args)
			{
				std::vector<asIScriptModule*>& vec = mBindings[formName];
				for(auto itor : vec)
				{
					Call(itor, function, args...);
				}
			}

			template <typename... Args>
			void Call(const string& module, const string& function, Args... args)
			{
				asIScriptModule* mod = engine->GetModule(module.c_str(), asGM_ONLY_IF_EXISTS);
				Call(mod, function, args...);
			}

			template <typename... Args>
			void Call(asIScriptModule* module, const string& function, Args... args)
			{
				currentModule = module;
				if(currentModule)
				{
					asIScriptFunction* func = currentModule->GetFunctionByDecl(function.c_str());
					if(func)
					{
						context->Prepare(func);
						SetArguments<0>(args...);
						context->Execute();
						context->Unprepare();
						currentModule = nullptr;
					}
				}
			}

		private:

			template <int N, class T, typename... Args>
			void SetArguments(T& arg, Args... args)
			{
				SetArg(arg, N);

				SetArguments<N + 1>(args...);
			}

			template<int N>
			void SetArguments()
			{
			}

			template <typename T>
			void SetArg(T arg, int N)
			{
				context->SetArgObject(N, &arg);
			}

			template <>
			void SetArg<uint16_t>(uint16_t arg, int N)
			{
				context->SetArgWord(N, arg);
			}

			template <>
			void SetArg<uint32_t>(uint32_t arg, int N)
			{
				context->SetArgDWord(N, arg);
			}

			template <>
			void SetArg<uint64_t>(uint64_t arg, int N)
			{
				context->SetArgQWord(N, arg);
			}

			template <>
			void SetArg<float>(float arg, int N)
			{
				context->SetArgFloat(N, arg);
			}

			template <>
			void SetArg<double>(double arg, int N)
			{
				context->SetArgDouble(N, arg);
			}

			void ParseScript(const boost::filesystem::path& pPath);

			asIScriptEngine* engine;
			asIScriptContext* context;
			asIScriptModule* currentModule;

			std::map<std::string, std::vector<asIScriptModule*> > mBindings;
		};
	}
}