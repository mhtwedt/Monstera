workspace "Monstera"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Monstera-Editor"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"]  = "Monstera/vendor/GLFW/include"
IncludeDir["Glad"]  = "Monstera/vendor/Glad/include"
IncludeDir["ImGui"] = "Monstera/vendor/imgui"
IncludeDir["glm"] = "Monstera/vendor/glm"
IncludeDir["stb_image"] = "Monstera/vendor/stb_image"
IncludeDir["entt"] = "Monstera/vendor/entt/include"
IncludeDir["yaml_cpp"] = "Monstera/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "Monstera/vendor/ImGuizmo"
IncludeDir["FFmpeg"] = "Monstera/vendor/FFmpeg"


group "Dependencies"
	include "Monstera/vendor/GLFW"
	include "Monstera/vendor/Glad"
	include "Monstera/vendor/imgui"
	include "Monstera/vendor/yaml-cpp"
--	include "Monstera/vendor/glm"
group ""


project "Monstera"
	location "Monstera"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "mdpch.h"
	pchsource "Monstera/src/mdpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"YAML_CPP_STATIC_DEFINE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "files:Monstera/vendor/ImGuizmo/**.cpp"
		flags { "NoPCH" }
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "MD_DEBUG"
	--	buildoptions "/MDd" -- This functionality is replaced by the runtime command
		symbols "on"
	--	staticruntime "off"
		runtime "Debug"

	filter "configurations:Release"
		defines "MD_RELEASE"
	--	buildoptions "/MD" -- This functionality is replaced by the runtime command
		optimize "on"
	--	staticruntime "off"
		runtime "Release"

	filter "configurations:Dist"
		defines "MD_DIST"
	--	buildoptions "/MD" -- This functionality is replaced by the runtime command
		optimize "on"
	--	staticruntime "off"
		runtime "Release"

project "Monstera-Editor"
	location "Monstera-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

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
		"Monstera/src",
		"Monstera/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"Monstera"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "MD_DEBUG"
	--	buildoptions "/MDd" -- This functionality is replaced by the runtime command
		symbols "on"
	--	staticruntime "off"
		runtime "Debug"

	filter "configurations:Release"
		defines "MD_RELEASE"
	--	buildoptions "/MD" -- This functionality is replaced by the runtime command
		optimize "on"
	--	staticruntime "off"
		runtime "Release"

	filter "configurations:Dist"
		defines "MD_DIST"
	--	buildoptions "/MD" -- This functionality is replaced by the runtime command
		optimize "on"
	--	staticruntime "off"
		runtime "Release"

project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		staticruntime "on"
	
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
			"Monstera/src",
			"Monstera/vendor",
			"%{IncludeDir.glm}",
			"%{IncludeDir.entt}"
		}
	
		links
		{
			"Monstera"
		}
	
		filter "system:windows"
			staticruntime "On"
			systemversion "latest"
	
		filter "configurations:Debug"
			defines "MD_DEBUG"
		--	buildoptions "/MDd" -- This functionality is replaced by the runtime command
			symbols "on"
		--	staticruntime "off"
			runtime "Debug"
	
		filter "configurations:Release"
			defines "MD_RELEASE"
		--	buildoptions "/MD" -- This functionality is replaced by the runtime command
			optimize "on"
		--	staticruntime "off"
			runtime "Release"
	
		filter "configurations:Dist"
			defines "MD_DIST"
		--	buildoptions "/MD" -- This functionality is replaced by the runtime command
			optimize "on"
		--	staticruntime "off"
			runtime "Release"

project "WIN"
		location "WIN"
		kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Monstera/vendor/spdlog/include",
		"Monstera/src",
		"Monstera/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}",
		"C:/opencv/build/include",
		"%{IncludeDir.FFmpeg}"
	}

	links
	{
		"Monstera"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "MD_DEBUG"
	--	buildoptions "/MDd" -- This functionality is replaced by the runtime command
		symbols "on"
	--	staticruntime "off"
		runtime "Debug"

	filter "configurations:Release"
		defines "MD_RELEASE"
	--	buildoptions "/MD" -- This functionality is replaced by the runtime command
		optimize "on"
	--	staticruntime "off"
		runtime "Release"

	filter "configurations:Dist"
		defines "MD_DIST"
	--	buildoptions "/MD" -- This functionality is replaced by the runtime command
		optimize "on"
	--	staticruntime "off"
		runtime "Release"

project "ImGuiTest"
location "ImGuiTest"
kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Monstera/vendor/spdlog/include",
		"Monstera/src",
		"Monstera/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}",
		"C:/opencv/build/include",
		"%{IncludeDir.FFmpeg}"
	}

	links
	{
		"Monstera"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "MD_DEBUG"
	--	buildoptions "/MDd" -- This functionality is replaced by the runtime command
		symbols "on"
	--	staticruntime "off"
		runtime "Debug"

	filter "configurations:Release"
		defines "MD_RELEASE"
	--	buildoptions "/MD" -- This functionality is replaced by the runtime command
		optimize "on"
	--	staticruntime "off"
		runtime "Release"

	filter "configurations:Dist"
		defines "MD_DIST"
	--	buildoptions "/MD" -- This functionality is replaced by the runtime command
		optimize "on"
	--	staticruntime "off"
		runtime "Release"