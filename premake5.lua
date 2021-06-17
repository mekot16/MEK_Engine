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

project "MEK_Engine"
	location "MEK_Engine"
	kind "SharedLib"
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
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
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

