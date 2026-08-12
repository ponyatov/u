find_package(SDL2 REQUIRED)

# include(FindPackageHandleStandardArgs)
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(SDL2 REQUIRED sdl2>=2.0)

if(SDL2_FOUND)
  message("-- Found SDL2: ${SDL2_LIBRARIES} (found version \"${SDL2_VERSION}\")")
  add_compile_definitions(SDL SDL2_FOUND)

#   add_library(SDL2::SDL2 INTERFACE IMPORTED)    

  target_include_directories(SDL2::SDL2 INTERFACE ${SDL2_INCLUDE_DIRS})
  target_compile_options(SDL2::SDL2 INTERFACE ${SDL2_CFLAGS_OTHER})
  target_link_libraries(SDL2::SDL2 INTERFACE ${SDL2_LIBRARIES})
  list(APPEND L SDL2::SDL2)
endif()
