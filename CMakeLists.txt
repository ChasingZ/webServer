cmake_minimum_required(VERSION 3.0)
project(chat)

set(CMAKE_CXX_STANDARD 11) # 设置C++标准为C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制要求编译器支持指定的C++标准，若不支持则构建失败

#配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

#配置最终的可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

#加载子目录
add_subdirectory(src)

