llvm_map_components_to_libnames(llvm_libs bitwriter core ipo irreader instcombine instrumentation target linker analysis scalaropts support )
file (GLOB SOURCES
        *.cpp
        )
add_executable(svf-ex ${SOURCES})
# briefly revised to add lib, if failed please compile with -v para and request on issues
# cmake add " -DZ3_DIR  " path
target_link_libraries(svf-ex ${llvm_libs} Svf Cudd z3)
set_target_properties( svf-ex PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
