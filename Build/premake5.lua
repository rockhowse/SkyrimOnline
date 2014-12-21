function file_check(file_name)
  local file_found=io.open(file_name, "r")      

  if file_found==nil then
    return false
  end
  return true
end


solution "Skyrim Online"
 
    ------------------------------------------------------------------
    -- setup common settings
    ------------------------------------------------------------------
	defines 
	{ 
		"BOOST_ALL_NO_LIB", 
		"_CRT_SECURE_NO_WARNINGS",
	}
	configurations 
	{ 
		"PriDeb", 
		"PriRel", 
		"PubRel" 
	}

	vectorextensions "SSE2"
	floatingpoint "Fast"
    
    includedirs 
    { 
        "../include/", 
        "../include/scriptdragon",
        "../code/",         
        "../code/boost/", 
        "../code/mhook/", 
        "../code/boost/thread/",
        "../code/boost/filesystem/",
        "../code/boost/system/",
        "../code/log",
        "../code/network/include",
	}
	
    location "projects"
	platforms { "x32" }
	
	configuration { "vs*"}
		buildoptions 
		{ 
			"/wd4512",
			"/wd4996",
			"/wd4018"
		}
        defines
        {
            "WIN32"
        }
	
    configuration "PriDeb"
        defines { "DEBUG" }
        flags { "Symbols" }
        targetsuffix "_d"
 
    configuration "PriRel"
        defines { "NDEBUG" }
        optimize "On"
		targetsuffix "_r"
		
	configuration "PubRel"
        defines { "NDEBUG", "PUBLIC_BUILD" }
        optimize "On"
 
	------------------------------------------------------------------
    -- logic projects
    ------------------------------------------------------------------
	group "Server"
		project "Game"
			kind "ConsoleApp"
			language "C++"
			targetdir "bin"
			includedirs 
            { 
                "../code/game/include/", 
                "../code/messages/server/"
            }
			files 
            { 
                "../code/game/include/**.h", 
                "../code/game/src/**.cpp",
                "../code/messages/server/**.cpp",
                "../code/messages/server/**.h",
            }
            libdirs 
            {
                "../lib" 
            }
            
            links 
            { 
                "boost_filesystem", 
                "boost_system", 
                "boost_thread", 
                "boost_chrono",
                "Network",
                "ws2_32",
                "winmm"
            }
              
	group "Client"
		project "d3d9hook"
            targetname "d3d9"
			kind "SharedLib"
			language "C++"
			targetdir "bin"
			
			includedirs 
            { 
				"$(DXSDK_DIR)/Include/",
                "../code/d3d9/include/"
            }
			
			files 
            { 
                "../code/d3d9/include/**.h", 
                "../code/d3d9/src/**.cpp",
				"../code/d3d9/src/**.def"
            }
			
			libdirs 
            {
                "$(DXSDK_DIR)/Lib/x86"
            }
			
            links 
            { 
                "ws2_32",
                "winmm",
                "d3d9",
                "d3dx9"
            }
			
		project "SkyrimEngine"
            targetname "SkyrimEngine"
			kind "SharedLib"
			language "C++"
			targetdir "bin"
			
            defines
            {
                "SKYRIM_EXPORTS"
            }
            
			includedirs 
            { 
				"$(DXSDK_DIR)/Include/",
                "../code/skyrimengine/include/skyrim", 
            }
			
			files 
            { 
                "../code/skyrimengine/include/**.h", 
                "../code/skyrimengine/src/**.cpp",
				"../code/skyrimengine/src/**.def"
            }
			
            libdirs 
            {
				"$(DXSDK_DIR)/Lib/x86",
                "lib" 
            }
            
            links 
            { 
                "boost_filesystem", 
                "boost_system", 
                "boost_thread", 
                "boost_chrono",
                "Network",
                "disasm",
                "mhook",
                "ws2_32",
                "winmm",
            }

		project "OblivionEngine"
            targetname "OblivionEngine"
			kind "SharedLib"
			language "C++"
			targetdir "bin"
			
            defines
            {
                "OBSE_EXPORTS",
                "OBLIVION=1",
                "OBLIVION_VERSION=0x010201A0",
                "OBSE_CORE",
            }
            
			includedirs 
            { 
				"$(DXSDK_DIR)/Include/",
                "../code/oblivionengine/include/oblivion", 
                "../code/oblivionengine/obse", 
                "../code/oblivionengine/obse_common", 
                "../code/oblivionengine/common",
                "../code/oblivionengine/"
            }
			
			files 
            { 
                "../code/oblivionengine/include/**.h", 
                "../code/oblivionengine/src/**.cpp",
                "../code/oblivionengine/src/**.def",
                "../code/oblivionengine/obse/**.cpp",
                "../code/oblivionengine/obse_common/**.cpp",
                "../code/oblivionengine/common/**.cpp",
                "../code/oblivionengine/obse/**.h",
                "../code/oblivionengine/obse_common/**.h",
                "../code/oblivionengine/common/**.h",
				"../code/oblivionengine/src/**.def"
            }
			
            libdirs 
            {
				"$(DXSDK_DIR)/Lib/x86",
                "lib" 
            }
            
            links 
            { 
                "boost_filesystem", 
                "boost_system", 
                "boost_thread", 
                "boost_chrono",
                "Network",
                "disasm",
                "mhook",
                "ws2_32",
                "winmm",
            }
            
            forceincludes
            {
                "IPrefix.h",
                "obse_common/obse_prefix.h"
            }
			
		project "Logic"
            targetname "Logic"
			kind "SharedLib"
			language "C++"
			targetdir "bin"
			
			includedirs 
            { 
				"$(DXSDK_DIR)/Include/",
                "../code/logic/include/",
				"../include/MyGUI",
                "../code/oblivionengine/include/", 
                "../code/skyrimengine/include/", 
                "../code/messages/client/"
            }
			
			files 
            { 
                "../code/logic/include/**.h", 
                "../code/logic/src/**.cpp",
				"../code/logic/src/**.def",
                "../code/messages/client/**.cpp",
                "../code/messages/client/**.h",
            }
			
            libdirs 
            {
				"$(DXSDK_DIR)/Lib/x86",
                "lib"
            }
            
            links 
            { 
                "boost_filesystem",
				"boost_system",
				"boost_thread",
				"boost_chrono",
				"cryptopp",
				"Network",
				"disasm",
				"mhook",
				"ws2_32",
				"winmm",
				"d3d9.lib",
                "d3dx9.lib",
				"MyGUI.DirectXPlatform.lib",
				"MyGUIEngine.lib",
                "OblivionEngine",
                "SkyrimEngine"
            }
		
		project "version"
            targetname "version"
			kind "SharedLib"
			language "C++"
			targetdir "bin"
			
			includedirs 
            { 
                "../code/version/include/"
            }
			
			files 
            { 
                "../code/version/include/**.h",
				"../code/version/src/**.cpp",
            }
                
 	group "Common"
		project "Network"
			kind "StaticLib"
			language "C++"
			targetdir "bin"
			includedirs 
            { 
                "../code/network/include/", 
            }
			files 
            { 
                "../code/network/include/**.h", 
                "../code/network/include/enet/**.h", 
                "../code/network/src/**.cpp",
                "../code/network/src/enet/**.c",
            }
            libdirs 
            {
                "../lib" 
            }
            
            links 
            { 
                "boost_filesystem", 
                "boost_system", 
                "boost_thread", 
                "boost_chrono",
                "cryptopp"
            }
        
        project "disasm"
			kind "StaticLib"
			language "C"
			targetdir "lib"
			targetname "disasm"
            includedirs { "../code/disasm/" }
			files { "../code/disasm/*.c" }    
            
        project "mhook"
			kind "StaticLib"
			language "C++"
			targetdir "lib"
			targetname "mhook"
            includedirs { "../code/disasm/" }
			files { "../code/mhook/*.cpp" }    
            
        project "boost_filesystem"
			kind "StaticLib"
			language "C++"
			targetdir "lib"
			targetname "boost_filesystem"
			defines { "BOOST_FILESYSTEM_STATIC_LINK=1" }
			files { "../code/filesystem/*.cpp" }

		project "boost_system"
			kind "StaticLib"
			language "C++"
			targetdir "lib"
			targetname "boost_system"
			files { "../code/system/*.cpp", "../code/system/*.hpp" }
			
		project "boost_chrono"
			kind "StaticLib"
			language "C++"
			targetdir "lib"
			targetname "boost_chrono"
			files { "../code/chrono/*.cpp" }
			
		project "boost_thread"
			kind "StaticLib"
			language "C++"
			targetdir "lib"
			targetname "boost_thread"
			defines { "BOOST_THREAD_BUILD_LIB=1" }
			configuration { "vs*"}
				files { "../code/thread/*.cpp", "../code/thread/win32/*.cpp", "../code/thread/*.hpp" }
			configuration {"xcode*" }
				files { "../code/thread/*.cpp", "../code/thread/pthread/*.cpp", "../code/thread/*.hpp" }
			configuration {"gmake"}
				files { "../code/thread/*.cpp", "../code/thread/pthread/*.cpp", "../code/thread/*.hpp" }
