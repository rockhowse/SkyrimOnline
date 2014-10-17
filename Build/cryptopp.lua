group "Common"
	project "cryptopp"
		kind "StaticLib"
		language "C++"
		targetdir "lib"
		targetname "cryptopp"

        includedirs
        {
            "../code/cryptopp/src/"
        }
		files 
		{ 
			"../code/cryptopp/src/*.cpp",
			"../code/cryptopp/include/*.h" 
		}
		defines 
		{ 
		}
	project "*"
group ""