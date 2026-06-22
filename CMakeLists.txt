cmake_minimum_required(VERSION 3.15)
project(Sunyong_Compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LLVM 14 환경 강제 고정 맵핑 
set(LLVM_DIR "/usr/local/opt/llvm@14/lib/cmake/llvm" CACHE PATH "Force LLVM 14" FORCE)
list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/llvm@14")

find_package(LLVM REQUIRED CONFIG)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})

# 컴파일러 타겟 소스 격리 매핑
add_executable(sunyong_compiler sunyong_compiler.cpp)

# ★ 수정: LLVM_TARGETS_TO_BUILD 변수를 사용하여 설치된 모든 하드웨어 백엔드를 안전하게 전개
llvm_map_components_to_libnames(llvm_libs 
    ${LLVM_TARGETS_TO_BUILD}
    core 
    support 
    passes 
    executionengine 
    analysis
)

target_link_libraries(sunyong_compiler PRIVATE ${llvm_libs})