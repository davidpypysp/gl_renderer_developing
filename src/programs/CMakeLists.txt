add_library(gl_base_lib ${VENDORS_SOURCES})
target_link_libraries(gl_base_lib assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)

macro(add_gl_program target_name target_src)
	add_executable(${target_name} ${target_src})
	target_link_libraries (${target_name} LINK_PUBLIC gl_base_lib)
	set_target_properties(${target_name} PROPERTIES
    	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
endmacro()

add_subdirectory(basic)
add_subdirectory(advanced_lighting)