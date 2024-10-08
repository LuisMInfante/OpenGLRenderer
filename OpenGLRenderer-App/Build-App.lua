project "OpenGLRenderer-App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp", "Source/**.hpp", "Source/**.c" }

   includedirs
   {
      "Source",
      "Assets",
      "../Vendor/GLEW/include",
      "../Vendor/GLFW/include",
      "../Vendor/GLM",
      "../Vendor/STB",

	  -- Include Core
	  "../OpenGLRenderer-Core/Source",
      "../OpenGLRenderer-Core/Source/Public"
   }

   links
   {
      "OpenGLRenderer-Core",
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"