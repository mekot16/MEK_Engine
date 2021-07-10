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
IncludeDir["Glad"] = "MEK_Engine/vendor/Glad/include"
IncludeDir["imgui"] = "MEK_Engine/vendor/imgui"

-- This includes these premake files in this file and groups them into a Dependencies folder
group "Dependencies"
	include "MEK_Engine/vendor/GLFW"
	include "MEK_Engine/vendor/Glad"
	include "MEK_Engine/vendor/imgui"

group ""

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MEK_PLATFORM_WINDOWS",
			"MEK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MEK_DEBUG"
		buildoptions "/MDd"
		symbols "On"


	filter "configurations:Release"
		defines "MEK_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MEK_DIST"
		buildoptions "/MD"
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
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MEK_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MEK_DIST"
		buildoptions "/MD"
		optimize "On"

