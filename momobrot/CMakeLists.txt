set(target_name "momobrot")

set(window_files
    "src/window/BaseWindow.h"
    "src/window/MainWindow.h"
    "src/window/MainWindow.cpp")

set(main_files
    "momobrot.manifest"
    "src/main.cpp")

set(src_files
    ${window_files}
    ${main_files})

add_executable(${target_name} ${src_files})

source_group("src" FILES ${main_files})
source_group("src\\window" FILES ${window_files})

set_target_properties(${target_name} PROPERTIES FOLDER "Twicemarks")
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin )
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/bin )
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/bin )
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_HOME_DIRECTORY}/bin )
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_HOME_DIRECTORY}/bin )
set_target_properties(${target_name} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin )