# Install script for directory: D:/Desktop/Workspace/comp-477-project/lib/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/comp477project")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Desktop/Workspace/comp-477-project/lib/assimp/lib/Debug/assimp-vc142-mtd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Desktop/Workspace/comp-477-project/lib/assimp/lib/Release/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Desktop/Workspace/comp-477-project/lib/assimp/lib/MinSizeRel/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Desktop/Workspace/comp-477-project/lib/assimp/lib/RelWithDebInfo/assimp-vc142-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/anim.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/aabb.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/ai_assert.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/camera.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/color4.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/color4.inl"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/config.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/ColladaMetaData.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/commonMetaData.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/defs.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Defines.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/cfileio.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/light.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/material.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/material.inl"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/matrix3x3.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/matrix3x3.inl"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/matrix4x4.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/matrix4x4.inl"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/mesh.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/pbrmaterial.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/postprocess.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/quaternion.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/quaternion.inl"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/scene.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/metadata.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/texture.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/types.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/vector2.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/vector2.inl"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/vector3.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/vector3.inl"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/version.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/cimport.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/importerdesc.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Importer.hpp"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/DefaultLogger.hpp"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/ProgressHandler.hpp"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/IOStream.hpp"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/IOSystem.hpp"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Logger.hpp"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/LogStream.hpp"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/NullLogger.hpp"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/cexport.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Exporter.hpp"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/DefaultIOStream.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/DefaultIOSystem.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/SceneCombiner.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/fast_atof.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/qnan.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/BaseImporter.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Hash.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/ParsingUtils.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/StreamReader.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/StreamWriter.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/StringComparison.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/StringUtils.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/SGSpatialSort.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/GenericProperty.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/SpatialSort.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/SmallVector.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/SmoothingGroups.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/SmoothingGroups.inl"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/StandardShapes.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/RemoveComments.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Subdivision.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Vertex.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/LineSplitter.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/TinyFormatter.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Profiler.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/LogAux.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Bitmap.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/XMLTools.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/IOStreamBuffer.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/CreateAnimMesh.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/XmlParser.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/BlobIOSystem.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/MathFunctions.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Exceptional.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Compiler/poppack1.h"
    "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/Debug/assimp-vc142-mtd.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Desktop/Workspace/comp-477-project/lib/assimp/code/RelWithDebInfo/assimp-vc142-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

