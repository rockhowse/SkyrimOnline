#pragma once

#define RegisterPODType(name, size) _RegisterPODType(#name, size)
#define RegisterPODTypeFlags(name, size, flag) _RegisterPODType(#name, size, flag)
#define RegisterMethod(name, methodName, method) _RegisterMethod(#name, methodName, method)
#define RegisterReferenceClass(name) _RegisterReferenceClass(#name)
#define RegisterProperty(name, var, offset) _RegisterProperty(#name, var, offset)
#define RegisterClassType(name) _RegisterClassType(#name)
#define RegisterInheritance(Base, Derived) _RegisterInheritance<Base, Derived>(#Base, #Derived)

namespace Skyrim
{
	namespace Game
	{
		class ScriptEngine
		{
		public:

			template <class A, class B>
			static B* refCast(A* a)
			{
				if( !a ) 
					return 0;

				B* b = reinterpret_cast<B*>(a);
				return b;
			}

			ScriptEngine();
			~ScriptEngine();

			void ReloadScripts();
			void Run();

			void RegisterForm(string& name);
			void RegisterWorld();



			template <typename T>
			void _RegisterMethod(const string& className, const string& methodName, T method)
			{
				engine->RegisterObjectMethod(className.c_str(), methodName.c_str(), method, asCALL_THISCALL);
			}

			template <typename T>
			void RegisterGlobal(const string& decl, T obj)
			{
				engine->RegisterGlobalProperty(decl.c_str(), obj);
			}



			void _RegisterPODType(const std::string& name, size_t size, int flag = asOBJ_APP_CLASS_CDAK)
			{
				engine->RegisterObjectType(name.c_str(), size, asOBJ_VALUE | asOBJ_POD | flag);
			}



			void _RegisterProperty(const std::string& typeName, const string& var, int offset)
			{
				engine->RegisterObjectProperty(typeName.c_str(), var.c_str(), offset);
			}



			void _RegisterClassType(const std::string& name)
			{
				engine->RegisterObjectType(name.c_str(), 0, asOBJ_REF);
			}



			template <class Base, class Derived>
			void _RegisterInheritance(const std::string& base, const std::string& derived)
			{
				engine->RegisterObjectBehaviour(base.c_str(), asBEHAVE_REF_CAST, (derived + std::string("@ f()")).c_str(), asFUNCTION((refCast<Base,Derived>)), asCALL_CDECL_OBJLAST);
				engine->RegisterObjectBehaviour(derived.c_str(), asBEHAVE_IMPLICIT_REF_CAST, (base + std::string("@ f()")).c_str(), asFUNCTION((refCast<Derived,Base>)), asCALL_CDECL_OBJLAST);
			}



			void _RegisterReferenceClass(const std::string& name)
			{
				engine->RegisterObjectType(name.c_str(), 0, asOBJ_REF | asOBJ_NOCOUNT);
			}

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
			void SetArguments(T arg, Args... args)
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
				int r = context->SetArgObject(N, &arg);
				if(r <  0)
					_trace
			}

			template <typename T>
			void SetArg(T* arg, int N)
			{
				int r = context->SetArgObject(N, arg);
				if(r <  0)
					_trace
			}

			template <>
			void SetArg<uint16_t>(uint16_t arg, int N)
			{
				int r = context->SetArgWord(N, arg);
				if(r <  0)
					_trace
			}

			template <>
			void SetArg<uint32_t>(uint32_t arg, int N)
			{
				int r = context->SetArgDWord(N, arg);
				if(r <  0)
					_trace
			}

			template <>
			void SetArg<uint64_t>(uint64_t arg, int N)
			{
				int r = context->SetArgQWord(N, arg);
				if(r <  0)
					_trace
			}

			template <>
			void SetArg<float>(float arg, int N)
			{
				int r = context->SetArgFloat(N, arg);
				if(r <  0)
					_trace
			}

			template <>
			void SetArg<double>(double arg, int N)
			{
				int r = context->SetArgDouble(N, arg);
				if(r <  0)
					_trace
			}

			void ParseScript(const boost::filesystem::path& pPath);

			asIScriptEngine* engine;
			asIScriptContext* context;
			asIScriptModule* currentModule;

			std::map<std::string, std::vector<asIScriptModule*> > mBindings;
		};
	}
}