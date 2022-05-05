workspace "Setup"
	architecture "x64"
	startproject "SetupProject_Lis"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (sol. directory)
IncludeDir = {}
IncludeDir["Lis"] = "SetupProject_Lis/vendor/lis_premake/include"

project "SetupProject_Lis"
	location "SetupProject_Lis"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/lis_premake/include/**.h",
		"%{prj.name}/vendor/lis_premake/src/**.h",
		"%{prj.name}/vendor/lis_premake/src/**.cpp",
	}
	
	-- Additional library directories
	libdirs { "SetupProject_Lis/vendor/lis_premake/lib" }
	
	-- OpenMP support
	buildoptions { "/openmp" }
	
	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.Lis}",
	}

	-- link the project glfw
	links 
	{
		"Lis",
	}
		
	-- Filter: Configurations only applied to specific platforms
	filter "system:windows"
		--cppdialect "C++17"
		--staticruntime "On"
		systemversion "latest"


