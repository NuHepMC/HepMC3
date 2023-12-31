set(CMAKE_MODULE_PATH    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules    ${CMAKE_MODULE_PATH})
foreach( fl  IN ITEMS "-pedantic" "-Wpedantic" )
  string(REPLACE "${fl}" ""  CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  string(REPLACE "${fl}" ""  CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endforeach()
find_package(Graphviz)
find_package(ROOT REQUIRED COMPONENTS Core RIO Tree Gui Graf Hist Gpad )
if(Graphviz_FOUND AND ROOT_FOUND)
  message(STATUS "HepMC3 ViewerExample: GrpahViz and ROOT found. GUI Browser example enabled. ${ROOT_LIBRARIES}  ${Graphviz_GRAPH_LIBRARY}  ${Graphviz_CGRAPH_LIBRARY} ${Graphviz_GVC_LIBRARY} ${Graphviz_INCLUDE_DIRS}")
  include_directories(${PROJECT_SOURCE_DIR}/rootIO/include ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}  ${ROOT_INCLUDE_DIRS} ${Graphviz_INCLUDE_DIRS} ./)
  ROOT_GENERATE_DICTIONARY(HepMC3ViewerFrameDict include/HepMC3ViewerFrame.h LINKDEF include/LinkDef.h OPTIONS -inlineInputHeader)
  ADD_EXECUTABLE(HepMC3Viewer.exe  src/main.cc  src/HepMC3ViewerFrame.cc HepMC3ViewerFrameDict.cxx  )
  set_target_properties(HepMC3Viewer.exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_BINDIR})
  target_compile_definitions(HepMC3Viewer.exe PRIVATE ${Graphviz_DEFINES} )
  include_directories( include  )

  SET(linklibraties   ${Graphviz_CGRAPH_LIBRARY}  ${Graphviz_GVC_LIBRARY}  HepMC3::HepMC3 HepMC3::rootIO )
  if (Graphviz_GRAPH_LIBRARY)
    list(APPEND linklibraties  ${Graphviz_GRAPH_LIBRARY}  )
  endif()
  TARGET_LINK_LIBRARIES(HepMC3Viewer.exe   ${linklibraties} ROOT::Core ROOT::RIO ROOT::Tree  ROOT::Gui ROOT::Graf ROOT::Hist ROOT::Gpad)
  if (USE_INSTALLED_HEPMC3)
    install(TARGETS HepMC3Viewer.exe DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${CMAKE_INSTALL_BINDIR} FILES_MATCHING PATTERN "*.pcm" PATTERN "*config"  PATTERN "CMakeFiles" EXCLUDE )
    install(DIRECTORY ${PROJECT_BINARY_DIR}/outputs/${CMAKE_INSTALL_BINDIR}/ DESTINATION ${CMAKE_INSTALL_BINDIR}
        FILES_MATCHING PATTERN "*env.sh*")
  endif()
elseif()
  message(STATUS "HepMC3 ViewerExample: GraphViz or ROOT package not found. GUI Browser example disabled.")
endif()
