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
        "../Include/", 
        "../Include/scriptdragon",
        "../Code/",         
        "../Code/boost/", 
        "../Code/mhook/", 
        "../Code/boost/thread/",
        "../Code/boost/filesystem/",
        "../Code/boost/system/",
        "../Code/log",
        "../Code/network/include",
	}
    
    if os.is("windows") then
    links
    {
        "ws2_32",
        "winmm"
    }
    end
	
    location "projects"
    if os.is("windows") then
        platforms { "x32" }
    else
        platforms { "x64" }
    end
	
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
        
    configuration {"gmake"}
		linkoptions( "-lm -lpthread -pthread -g" ) 
		buildoptions {"-g --std=c++11 -fpermissive" } 
	
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
			targetdir "bin/server"
			includedirs 
            { 
                "../Code/game/include/", 
                "../Code/messages/server/"
            }
			files 
            { 
                "../Code/game/include/**.h", 
                "../Code/game/src/**.cpp",
                "../Code/messages/server/**.cpp",
                "../Code/messages/server/**.h",
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
            }
    if os.is("windows") then
        group "Client"		
            project "SkyrimOnline"
                targetname "SkyrimOnline"
                kind "SharedLib"
                language "C++"
                targetdir "bin"
                
                defines
                {
                    "SKYRIM_EXPORTS",
                    "RUNTIME",
                    "RUNTIME_VERSION=0x09200000"
                }
                
                includedirs 
                { 
                    "../Code/skyrimonline/include/",
                    "../include/MyGUI",
                    "../Code/messages/client/",
                    "$(DXSDK_DIR)/Include/",
                    "../Code/skyrimonline/include", 
                    "../Code/skyrimonline/",
                    "../Code/skyrimonline/skse",                 
                }
                
                files 
                { 
                    "../Code/skyrimonline/include/**.h", 
                    "../Code/skyrimonline/src/**.cpp",
                    "../Code/skyrimonline/src/**.def",
                    "../Code/skyrimonline/common/**.h", 
                    "../Code/skyrimonline/common/**.cpp",
                    "../Code/skyrimonline/skse/**.h", 
                    "../Code/skyrimonline/skse/**.cpp",
                    "../Code/messages/client/**.cpp",
                    "../Code/messages/client/**.h",
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
                    "d3d9.lib",
                    "d3dx9.lib",
                    "MyGUI.DirectXPlatform.lib",
                    "MyGUIEngine.lib",
                }
                
                forceincludes
                {
                    "common/IPrefix.h"
                }
                
    end          
 	group "Common"
		project "Network"
			kind "StaticLib"
			language "C++"
			targetdir "bin"
			includedirs 
            { 
                "../Code/network/include/", 
            }
			files 
            { 
                "../Code/network/include/**.h", 
                "../Code/network/include/enet/**.h", 
                "../Code/network/src/**.cpp",
                "../Code/network/src/**.c",
            }
            defines
            {
                "HAS_SOCKLEN_T"
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
            }
    if os.is("windows") then    
        project "disasm"
			kind "StaticLib"
			language "C"
			targetdir "lib"
			targetname "disasm"
            includedirs { "../Code/disasm/" }
			files { "../Code/disasm/*.c" }    
            
        project "mhook"
			kind "StaticLib"
			language "C++"
			targetdir "lib"
			targetname "mhook"
            includedirs { "../Code/disasm/" }
			files { "../Code/mhook/*.cpp" }    
    end        
        project "boost_filesystem"
			kind "StaticLib"
			language "C++"
			targetdir "lib"
			targetname "boost_filesystem"
			defines { "BOOST_FILESYSTEM_STATIC_LINK=1" }
			files { "../Code/filesystem/*.cpp" }

		project "boost_system"
			kind "StaticLib"
			language "C++"
			targetdir "lib"
			targetname "boost_system"
			files { "../Code/system/*.cpp", "../Code/system/*.hpp" }
			
		project "boost_chrono"
			kind "StaticLib"
			language "C++"
			targetdir "lib"
			targetname "boost_chrono"
			files { "../Code/chrono/*.cpp" }
			
		project "boost_thread"
			kind "StaticLib"
			language "C++"
			targetdir "lib"
			targetname "boost_thread"
			defines { "BOOST_THREAD_BUILD_LIB=1" }
			configuration { "vs*"}
				files { "../Code/thread/*.cpp", "../Code/thread/win32/*.cpp", "../Code/thread/*.hpp" }
			configuration {"xCode*" }
				files { "../Code/thread/*.cpp", "../Code/thread/pthread/*.cpp", "../Code/thread/*.hpp" }
			configuration {"gmake"}
				files { "../Code/thread/*.cpp", "../Code/thread/pthread/*.cpp", "../Code/thread/*.hpp" }
