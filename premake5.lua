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
IncludeDir["glm"] = "MEK_Engine/vendor/glm"

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
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mekpch.h"
	pchsource "%{prj.name}/src/mekpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
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
		systemversion "latest"

		defines
		{
			"MEK_PLATFORM_WINDOWS",
			"MEK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "MEK_DEBUG"
		runtime "Debug"
		symbols "On"


	filter "configurations:Release"
		defines "MEK_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MEK_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"


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
		"MEK_Engine/src",
		"MEK_Engine/vendor",
		"%{IncludeDir.glm}"
	}

	links {
		"MEK_Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MEK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MEK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MEK_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MEK_DIST"
		runtime "Release"
		optimize "On"

