set(target_name "dububench")

set(image_files
    "src/Image/Texture2D.cpp"
    "src/Image/Texture2D.h"
    "src/Image/Bitmap.cpp"
    "src/Image/Bitmap.h"
    "src/Image/Pixel.h")

set(render_files
    "src/Render/RenderPipeline.cpp"
    "src/Render/RenderPipeline.h")

set(renderer_files
    "src/Render/Renderer/RendererSphereTracer.cpp"
    "src/Render/Renderer/RendererSphereTracer.h")

set(postprocessor_files
    "src/Render/PostProcessor/PostProcessorChromaticAberration.cpp"
    "src/Render/PostProcessor/PostProcessorChromaticAberration.h"
    "src/Render/PostProcessor/PostProcessorFishEye.cpp"
    "src/Render/PostProcessor/PostProcessorFishEye.h"
    "src/Render/PostProcessor/PostProcessorRGBFlip.cpp"
    "src/Render/PostProcessor/PostProcessorRGBFlip.h")

set(sdf_files
    "src/Render/SDF/RenderCommands.h")

set(utils_files
    "src/Utils/SDF.h"
    "src/Utils/Shadermath.h"
    "src/Utils/Utils.h"
    "src/Utils/Vec.h"
    "src/Utils/Vmath.h")

set(main_files
    "src/main.cpp")

set(src_files
    ${image_files}
    ${render_files}
    ${renderer_files}
    ${postprocessor_files}
    ${sdf_files}
    ${utils_files}
    ${main_files})

add_executable(${target_name} ${src_files})

source_group("src" FILES ${main_files})
source_group("src\\Image" FILES ${image_files})
source_group("src\\Render" FILES ${render_files})
source_group("src\\Render\\Renderer" FILES ${renderer_files})
source_group("src\\Render\\PostProcessor" FILES ${postprocessor_files})
source_group("src\\Render\\SDF" FILES ${sdf_files})
source_group("src\\Utils" FILES ${utils_files})

set_target_properties(${target_name} PROPERTIES FOLDER "Twicemarks")
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin )
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/bin )
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/bin )
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_HOME_DIRECTORY}/bin )
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_HOME_DIRECTORY}/bin )
set_target_properties(${target_name} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin )