#include "obse/PluginAPI.h"
#include "obse/CommandTable.h"

#if OBLIVION
#include "obse/GameAPI.h"

#define ENABLE_EXTRACT_ARGS_MACROS 1	// #define this as 0 if you prefer not to use this

#if ENABLE_EXTRACT_ARGS_MACROS

OBSEScriptInterface * g_scriptInterface = NULL;	// make sure you assign to this
#define ExtractArgsEx(...) g_scriptInterface->ExtractArgsEx(__VA_ARGS__)
#define ExtractFormatStringArgs(...) g_scriptInterface->ExtractFormatStringArgs(__VA_ARGS__)

#endif

#else
#include "obse_editor/EditorAPI.h"
#endif

#include "obse/ParamInfos.h"
#include "obse/Script.h"
#include "obse/GameObjects.h"
#include <string>
#include <sstream>
#include <fstream>


PluginHandle				g_pluginHandle = kPluginHandle_Invalid;
OBSESerializationInterface	* g_serialization = NULL;
OBSEArrayVarInterface		* g_arrayIntfc = NULL;
OBSEScriptInterface			* g_scriptIntfc = NULL;
OBSECommandTableInterface* g_cmdIntfc = NULL;

/***************************
* Serialization routines
***************************/

std::string	g_strData;
std::ofstream g_log("out.log", std::ios::trunc);

static void ResetData(void)
{
	g_strData.clear();
}

static void ExamplePlugin_SaveCallback(void * reserved)
{
}

static void ExamplePlugin_LoadCallback(void * reserved)
{
}

static void ExamplePlugin_PreloadCallback(void * reserved)
{
}

static void ExamplePlugin_NewGameCallback(void * reserved)
{
	ResetData();
}

bool Cmd_TextAxis_Execute(COMMAND_ARGS)
{
	std::ostringstream os;
	*result = 4.0f;
	for(int i = 0; i < 16; ++i)
	{
		os << "{" << ((char*)arg1)[i] << ":" << (int)((char*)arg1)[i] << "} ; ";
	}
	g_log << os.str() << std::endl;

	return true;
}

static ParamInfo kParams_TextAxis[2] =
{
	{	"axis",		kParamType_Axis,	0	},
	{	"string",	kParamType_String,	0	},
};

DEFINE_COMMAND_PLUGIN(TextAxis, "Test", 0, 2, kParams_TextAxis)

/*************************
	Messaging API example
*************************/

OBSEMessagingInterface* g_msg;

void MessageHandler(OBSEMessagingInterface::Message* msg)
{
	switch (msg->type)
	{
	case OBSEMessagingInterface::kMessage_ExitGame:
		break;
	case OBSEMessagingInterface::kMessage_ExitToMainMenu:
		break;
	case OBSEMessagingInterface::kMessage_PostLoad:
		break;
	case OBSEMessagingInterface::kMessage_LoadGame:
	case OBSEMessagingInterface::kMessage_SaveGame:
		break;
	case OBSEMessagingInterface::kMessage_Precompile: 
		{
			ScriptBuffer* buffer = (ScriptBuffer*)msg->data;		
			break;
		}
	case OBSEMessagingInterface::kMessage_PreLoadGame:
		break;
	case OBSEMessagingInterface::kMessage_ExitGame_Console:
		break;
	default:
		break;
	}
}

extern "C" {

bool OBSEPlugin_Query(const OBSEInterface * obse, PluginInfo * info)
{
	// fill out the info structure
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "Oblivion.Online";
	info->version = 1;

	// version checks
	if(!obse->isEditor)
	{
		if(obse->obseVersion < OBSE_VERSION_INTEGER)
		{
			return false;
		}

		if(obse->oblivionVersion != OBLIVION_VERSION)
		{
			return false;
		}

		g_serialization = (OBSESerializationInterface *)obse->QueryInterface(kInterface_Serialization);
		if(!g_serialization)
		{
			return false;
		}

		if(g_serialization->version < OBSESerializationInterface::kVersion)
		{
			return false;
		}

		g_arrayIntfc = (OBSEArrayVarInterface*)obse->QueryInterface(kInterface_ArrayVar);
		if (!g_arrayIntfc)
		{
			return false;
		}

		g_scriptIntfc = (OBSEScriptInterface*)obse->QueryInterface(kInterface_Script);		
	}
	else
	{
		// no version checks needed for editor
	}

	// version checks pass

	return true;
}

bool CallFunction(const char* longName, void * thisObj, std::vector<unsigned char>& parameterStack, int stackSize, double * result)
{
	if(g_cmdIntfc)
	{
		auto cmd = g_cmdIntfc->GetByName(longName);

		if(cmd)
		{
			UInt32 opcodeOffset = 4;

			unsigned char scriptBuff[sizeof(Script)];
			Script* fScript = (Script*)scriptBuff;
			ScriptEventList eList;
			void* sstate = GetGlobalScriptStateObj();
			fScript->Constructor();
			fScript->MarkAsTemporary();
			eList.m_eventList = nullptr;
			eList.m_script = fScript;
			eList.m_vars = nullptr;
			eList.m_unk1 = 0;

			union ShortToChar
			{
				unsigned short s;
				unsigned char c[2];
			};

			ShortToChar tmp;
			tmp.s = cmd->opcode;

			std::vector<unsigned char> params;
			params.push_back(tmp.c[0]);
			params.push_back(tmp.c[1]);

			tmp.s = parameterStack.size();
			params.push_back(tmp.c[0]);
			params.push_back(tmp.c[1]);

			params.insert(params.end(), parameterStack.begin(), parameterStack.end());

			bool ret = cmd->execute(cmd->params, params.data(), (TESObjectREFR*)thisObj, 0, fScript, &eList, result, &opcodeOffset);

			fScript->StaticDestructor();

			return ret;
		}
		else
		{
			MessageBoxA(0, "Command not found...", "", 0);
		}
	}
	return false;
}


bool OBSEPlugin_Load(const OBSEInterface * obse)
{
	g_pluginHandle = obse->GetPluginHandle();

	// register commands
	obse->SetOpcodeBase(0x7541);
	obse->RegisterCommand(&kCommandInfo_TextAxis);
	
	// set up serialization callbacks when running in the runtime
	if(!obse->isEditor)
	{
		g_serialization->SetSaveCallback(g_pluginHandle,    ExamplePlugin_SaveCallback);
		g_serialization->SetLoadCallback(g_pluginHandle,    ExamplePlugin_LoadCallback);
		g_serialization->SetNewGameCallback(g_pluginHandle, ExamplePlugin_NewGameCallback);

		// register to use string var interface
		// this allows plugin commands to support '%z' format specifier in format string arguments
		OBSEStringVarInterface* g_Str = (OBSEStringVarInterface*)obse->QueryInterface(kInterface_StringVar);
		g_Str->Register(g_Str);

		// get an OBSEScriptInterface to use for argument extraction
		g_scriptInterface = (OBSEScriptInterface*)obse->QueryInterface(kInterface_Script);
	}

	// register to receive messages from OBSE
	OBSEMessagingInterface* msgIntfc = (OBSEMessagingInterface*)obse->QueryInterface(kInterface_Messaging);
	msgIntfc->RegisterListener(g_pluginHandle, "OBSE", MessageHandler);
	g_msg = msgIntfc;

	// get command table, if needed
	g_cmdIntfc = (OBSECommandTableInterface*)obse->QueryInterface(kInterface_CommandTable);

	return true;
}

};
