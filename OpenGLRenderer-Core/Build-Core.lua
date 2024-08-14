project "OpenGLRenderer-Core"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp", "Source/**.hpp", "Source/**.c" }

   includedirs
   {
      "Source",
      "../Vendor/GLEW/include",
      "../Vendor/GLFW/include",
      "../Vendor/GLM"
   }
   
   libdirs
   {
      "../Vendor/GLEW/lib/Release/Win32",
      "../Vendor/GLFW/lib-vc2022"
   }

   links
   {
      "opengl32",
      "glew32s",
      "glfw3"
   }

   defines 
   {
       "GLEW_STATIC",
       "GLM_ENABLE_EXPERIMENTAL"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

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