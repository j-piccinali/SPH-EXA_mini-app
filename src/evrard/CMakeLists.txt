
add_executable(evrard evrard.cpp)
target_include_directories(evrard PRIVATE ${PROJECT_SOURCE_DIR}/domain/include)
target_include_directories(evrard PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(evrard PRIVATE ${MPI_CXX_INCLUDE_PATH})
target_compile_definitions(evrard PRIVATE USE_MPI GRAVITY)
target_link_libraries(evrard ${MPI_CXX_LIBRARIES})
target_link_libraries(evrard OpenMP::OpenMP_CXX)

if(CMAKE_CUDA_COMPILER)
    add_executable(evrard-cuda $<TARGET_OBJECTS:gather_obj> $<TARGET_OBJECTS:cuda_find_neighbors_obj> $<TARGET_OBJECTS:cuda_sph> evrard.cpp)
    target_include_directories(evrard-cuda PRIVATE  ${PROJECT_SOURCE_DIR}/domain/include)
    target_include_directories(evrard-cuda PRIVATE ${PROJECT_SOURCE_DIR}/include)
    target_include_directories(evrard-cuda PRIVATE ${MPI_CXX_INCLUDE_PATH})
    target_compile_definitions(evrard-cuda PRIVATE GRAVITY USE_MPI USE_CUDA)
    set_target_properties(evrard-cuda PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
    target_link_libraries(evrard-cuda ${MPI_CXX_LIBRARIES})
    target_link_libraries(evrard-cuda OpenMP::OpenMP_CXX)
    install(TARGETS evrard-cuda RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

install(TARGETS evrard RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
