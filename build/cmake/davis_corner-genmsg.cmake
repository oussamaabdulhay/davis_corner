# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "davis_corner: 1 messages, 0 services")

set(MSG_I_FLAGS "-Idavis_corner:/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(davis_corner_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg" NAME_WE)
add_custom_target(_davis_corner_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "davis_corner" "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(davis_corner
  "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/davis_corner
)

### Generating Services

### Generating Module File
_generate_module_cpp(davis_corner
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/davis_corner
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(davis_corner_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(davis_corner_generate_messages davis_corner_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg" NAME_WE)
add_dependencies(davis_corner_generate_messages_cpp _davis_corner_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(davis_corner_gencpp)
add_dependencies(davis_corner_gencpp davis_corner_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS davis_corner_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(davis_corner
  "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/davis_corner
)

### Generating Services

### Generating Module File
_generate_module_eus(davis_corner
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/davis_corner
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(davis_corner_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(davis_corner_generate_messages davis_corner_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg" NAME_WE)
add_dependencies(davis_corner_generate_messages_eus _davis_corner_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(davis_corner_geneus)
add_dependencies(davis_corner_geneus davis_corner_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS davis_corner_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(davis_corner
  "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/davis_corner
)

### Generating Services

### Generating Module File
_generate_module_lisp(davis_corner
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/davis_corner
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(davis_corner_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(davis_corner_generate_messages davis_corner_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg" NAME_WE)
add_dependencies(davis_corner_generate_messages_lisp _davis_corner_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(davis_corner_genlisp)
add_dependencies(davis_corner_genlisp davis_corner_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS davis_corner_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(davis_corner
  "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/davis_corner
)

### Generating Services

### Generating Module File
_generate_module_nodejs(davis_corner
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/davis_corner
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(davis_corner_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(davis_corner_generate_messages davis_corner_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg" NAME_WE)
add_dependencies(davis_corner_generate_messages_nodejs _davis_corner_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(davis_corner_gennodejs)
add_dependencies(davis_corner_gennodejs davis_corner_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS davis_corner_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(davis_corner
  "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/davis_corner
)

### Generating Services

### Generating Module File
_generate_module_py(davis_corner
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/davis_corner
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(davis_corner_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(davis_corner_generate_messages davis_corner_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/ku-t2/catkin_ws_eventcamera/src/davis_corner/msg/Corners.msg" NAME_WE)
add_dependencies(davis_corner_generate_messages_py _davis_corner_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(davis_corner_genpy)
add_dependencies(davis_corner_genpy davis_corner_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS davis_corner_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/davis_corner)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/davis_corner
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(davis_corner_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/davis_corner)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/davis_corner
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(davis_corner_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/davis_corner)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/davis_corner
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(davis_corner_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/davis_corner)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/davis_corner
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(davis_corner_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/davis_corner)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/davis_corner\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/davis_corner
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(davis_corner_generate_messages_py std_msgs_generate_messages_py)
endif()
