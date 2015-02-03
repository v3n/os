solution "OS"
  configurations { "Debug", "Release", "Test" }

  project "OS"
    kind "ConsoleApp"
    language "C++"
    files { "src/**.cpp" }
    includedirs { "include/" }
    flags { "ExtraWarnings" }

    configurations { "Debug*" }
      defines { "DEBUG" }
      flags { "Symbols" }

    configurations { "Release*" }
      defines { }
      flags { "Optimize" }