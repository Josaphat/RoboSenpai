LIST (APPEND MODULES_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/PennyArcade.cpp)
SET (MODULES_SOURCE ${MODULES_SOURCE} PARENT_SCOPE)

LIST (APPEND MODULES_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/PennyArcade.h)
SET (MODULES_HEADERS ${MODULES_HEADERS} PARENT_SCOPE)

# I can't get this source_group command to actually work.
SOURCE_GROUP("modules\\pennyarcade" FILES ${CMAKE_CURRENT_SOURCE_DIR}/PennyArcade.h ${CMAKE_CURRENT_SOURCE_DIR}/PennyArcade.cpp)
