set(MODULE_LIBRARIES "")
file(GLOB MODULE_FILES
    "${PROJECT_DIRECTORY}/${MODULE_NAME}/*.c"
    "${PROJECT_DIRECTORY}/${MODULE_NAME}/*.h"
    "${PROJECT_DIRECTORY}/${MODULE_NAME}/*.cpp"
    "${PROJECT_DIRECTORY}/${MODULE_NAME}/*.hpp"
)

set(MODULE_BINARY "${MODULE_NAME}")

add_executable(${MODULE_BINARY} ${MODULE_FILES})
target_include_directories(${MODULE_BINARY} PUBLIC "${PROJECT_DIRECTORY}")
target_include_directories(${MODULE_BINARY} PUBLIC "${PROJECT_DIRECTORY}/${MODULE_NAME}")
target_link_libraries(${MODULE_BINARY} ${MODULE_LIBRARIES})
install(
    TARGETS ${MODULE_BINARY}
    RUNTIME DESTINATION "${MODULE_IDIR}"
)
