workspace "Monstera"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Monstera/vendor/GLFW/include"
IncludeDir["Glad"] = "Monstera/vendor/Glad/include"
IncludeDir["ImGui"] = "Monstera/vendor/imgui"


include "Monstera/vendor/GLFW"
include "Monstera/vendor/Glad"
include "Monstera/vendor/imgui"

project "Monstera"
	location "Monstera"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "mdpch.h"
	pchsource "Monstera/src/mdpch.cpp"

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
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MD_PLATFORM_WINDOWS",
			"MD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "MD_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	--	staticruntime "off"
	--	runtime "Debug"

	filter "configurations:Release"
		defines "MD_RELEASE"
		buildoptions "/MD"
		optimize "On"
	--	staticruntime "off"
	--	runtime "Release"

	filter "configurations:Dist"
		defines "MD_DIST"
		buildoptions "/MD"
		optimize "On"
	--	staticruntime "off"
	--	runtime "Release"

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
		"Monstera/vendor/spdlog/include",
		"Monstera/src"
	}

	links
	{
		"Monstera"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MD_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MD_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	--	staticruntime "off"
	--	runtime "Debug"

	filter "configurations:Release"
		defines "MD_RELEASE"
		buildoptions "/MD"
		optimize "On"
	--	staticruntime "off"
	--	runtime "Release"

	filter "configurations:Dist"
		defines "MD_DIST"
		buildoptions "/MD"
		optimize "On"
	--	staticruntime "off"
	--	runtime "Release"