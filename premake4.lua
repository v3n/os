solution "os"
  configurations  { "Debug", "Release" }

  -- Visual Studio default project
  -- startproject "ostests"

  configuration "Debug*" 
    defines       { "DEBUG" }
    flags         { "Symbols" }
    targetsuffix  "_d"
    objdir        "build/obj_debug"
    targetdir     "bin/debug"

  configuration "Release*"
    defines       { }
    flags         { "Optimize" }
    objdir        "build/obj_release"
    targetdir     "bin/release"

  -- The google test static lib
  project "gtest"
     kind        "StaticLib"     
     language    "C++"
     flags       { "StaticRuntime" } 
     files       { "lib/googletest/src/**.cc" }
     excludes    { "lib/googletest/src/gtest-all.cc", "lib/googletest/src/gtest_main.cc" }
     includedirs { "lib/googletest/include", "lib/googletest" }

     configuration "Debug"
        flags    { "Symbols" }
  
     configuration "Release"
        flags    { "Optimize" } 

  project "ostests"
    kind          "ConsoleApp"
    language      "C++"
    files         { "src/**.cpp", "test/**.cpp" }
    excludes      { "src/driver.cpp" }
    includedirs   { "include/", "lib/googletest/include" }
    links         { "gtest" }
    flags         { "ExtraWarnings" }
    defines       { "__FOR_TESTS=1" }

    configuration "gmake"
      buildoptions { "-std=c++11" }
      linkoptions { "-stdlib=libc++" }

  project "os"
    kind          "ConsoleApp"
    language      "C++"
    files         { "src/**.cpp" }
    includedirs   { "include/" }
    flags         { "ExtraWarnings" }

    configuration "gmake"
      buildoptions { "-std=c++11" }
      linkoptions { "-stdlib=libc++" }
