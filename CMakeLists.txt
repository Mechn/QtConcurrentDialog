# CMake 最低版本要求
cmake_minimum_required(VERSION 3.5)

# 项目名称
project(QtConcurrentDialog)

# 查找Qt5所需的组件，这里假设使用了核心、GUI和Widgets模块
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)

# 设置C++标准为 C++11或更高（根据你的需求）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置安装目录
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

# 将源文件添加到项目中
set(SOURCES
    src/main.cpp
    src/QThreadTask.cpp
    src/AsyncTaskExecutor.cpp
)

# 将头文件所在目录添加到包含路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_BUILD_PATH}
)

# 将.ui文件转换为头文件和源文件（需要Qt5_WRAP_UI）
set(UI_FILES 
    form/QThreadTask.ui
    )
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

# 将.qrc资源文件添加到项目中（需要Qt5_ADD_RESOURCES）
set(QRC_FILES 
    res/QThreadTask.qrc 
    )
qt5_add_resources(RCS_SOURCES ${QRC_FILES} )

# 将含Q_OBJECT宏的类执行MOC
set(MOC_HEADERS 
    src/QThreadTask.h
    src/AsyncTaskExecutor.h
)
qt5_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

# 添加可执行文件
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${UI_HEADERS}
    ${RCS_SOURCES}
    ${MOC_SOURCES}
)

# 链接Qt5库
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Concurrent
)

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION bin) #可以使用“CMAKE_INSTALL_PREFIX”改变安装路径
