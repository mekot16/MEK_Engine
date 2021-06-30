workspace "MEK_Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories releative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "MEK_Engine/vendor/GLFW/include"

-- This includes the premake file in this submodule
include "MEK_Engine/vendor/GLFW"

project "MEK_Engine"
	location "MEK_Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mekpch.h"
	pchsource "%{prj.name}/src/mekpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MEK_PLATFORM_WINDOWS",
			"MEK_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MEK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MEK_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MEK_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"MEK_Engine/vendor/spdlog/include",
		"MEK_Engine/src"
	}

	links {
		"MEK_Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MEK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MEK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MEK_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MEK_DIST"
		optimize "On"

