solution "OS"
  configurations { "Debug", "Release", "Test" }

  project "OS"
    kind "ConsoleApp"
    language "C++"
    files { "src/**.cpp" }
    includedirs { "include/" }
    flags { "ExtraWarnings" }

    configuration "gmake"
      buildoptions { "-std=c++11", "-stdlib=libc++" }
      linkoptions { "-stdlib=libc++" }

    configurations { "Debug*" }
      defines { "DEBUG" }
      flags { "Symbols" }

    configurations { "Release*" }
      defines { }
      flags { "Optimize" }
