cmake_minimum_required(VERSION 3.0)

project(DesignPatterns)

# Enable C++14 on GCC and Clang
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-std=c++14 -Wall")
endif()

# Folders
set(CREATIONAL_FOLDER   "${PROJECT_SOURCE_DIR}/Creational")
set(STRUCTURAL_FOLDER   "${PROJECT_SOURCE_DIR}/Structural")
set(BEHAVIORAL_FOLDER   "${PROJECT_SOURCE_DIR}/Behavioral")
set(OPTIMIZATION_FOLDER "${PROJECT_SOURCE_DIR}/Optimization")

# Creational Patterns
add_executable(Builder "${CREATIONAL_FOLDER}/Builder.cpp")
add_executable(Factory "${CREATIONAL_FOLDER}/Factory.cpp")
add_executable(Prototype "${CREATIONAL_FOLDER}/Prototype.cpp")
add_executable(Singleton "${CREATIONAL_FOLDER}/Singleton.cpp")

set_target_properties(Builder Factory Prototype Singleton
                      PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin/Creational")

# Structural Patterns

# Behavioral Patterns

# Optimization Patterns
add_executable(ObjectPool "${OPTIMIZATION_FOLDER}/ObjectPool.cpp"
                          "${OPTIMIZATION_FOLDER}/PoolAllocator.cpp")

set_target_properties(ObjectPool
                      PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin/Optimization")
