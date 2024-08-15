cmake_minimum_required(VERSION 3.30)

# 本CMakeLists.txt的project名称
# 会自动创建两个变量，PROJECT_SOURCE_DIR和PROJECT_NAME
# ${PROJECT_SOURCE_DIR}：本CMakeLists.txt所在的文件夹路径
# ${PROJECT_NAME}：本CMakeLists.txt的project名称
PROJECT(randTake)

aux_source_directory(${PROJECT_SOURCE_DIR} RANDTAKE_FILES)

include_directories(
    ${PROJECT_SOURCE_DIR}
)

add_library(${PROJECT_NAME} STATIC ${RANDTAKE_FILES})
