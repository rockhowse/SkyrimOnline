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
    flags 
	{ 
		"NoRTTI"
	}

	vectorextensions "SSE2"
	floatingpoint "Fast"
    
    includedirs 
    { 
        "../include/", 
        "../include/scriptdragon",
        "../code/",         
        "../code/boost/", 
        "../code/boost/thread/",
        "../code/boost/filesystem/",
        "../code/boost/system/",
        "../code/cryptopp/include/",
        "../code/log",
        "../code/network/include"
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
            }
			files 
            { 
                "../code/game/include/**.h", 
                "../code/game/src/**.cpp",
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
                "cryptopp",
                "Network"
            }
              
	group "Client"
		project "Module"
            targetname "Version"
			kind "SharedLib"
			language "C++"
			targetdir "bin"
			includedirs 
            { 
                "../code/module/include/", 
            }
			files 
            { 
                "../code/module/include/**.h", 
                "../code/module/src/**.cpp",
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
                "cryptopp",
                "Network"
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
                "../code/network/src/**.cpp",
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

dofile "cryptopp.lua"

