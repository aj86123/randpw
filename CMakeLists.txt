cmake_minimum_required(VERSION 3.30)

# 本CMakeLists.txt的project名称
# 会自动创建两个变量，PROJECT_SOURCE_DIR和PROJECT_NAME
# ${PROJECT_SOURCE_DIR}：本CMakeLists.txt所在的文件夹路径
# ${PROJECT_NAME}：本CMakeLists.txt的project名称
PROJECT(randpw)

# Enable C++11
set(CMAKE_CXX_STANDARD 17)


# 如果想要生成的可执行文件拥有符号表，可以gdb调试，就直接加上这句
add_definitions("-Wall -g")

# 设置变量，下面的代码都可以用到
set(RANDTAKE_DIR ${PROJECT_SOURCE_DIR}/randTake)

# 编译子文件夹的CMakeLists.txt
add_subdirectory(randTake)

# 规定.h头文件路径
include_directories(
    ${RANDTAKE_DIR}
)

# 生成可执行文件
add_executable(${PROJECT_NAME} randpw.cpp)

# 链接操作
target_link_libraries(${PROJECT_NAME} randTake)
