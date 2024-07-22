workspace "OpenGLRenderer"
   architecture "x86"
   configurations { "Debug", "Release", "Dist" }
   startproject "OpenGLRenderer-App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "OpenGLRenderer-Core/Build-Core.lua"
group ""

include "OpenGLRenderer-App/Build-App.lua"