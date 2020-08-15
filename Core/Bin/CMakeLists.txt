
Set (COMMONLIBS
        ${PROJECT_NAME}-${LIBRARIES_TARGET_PREFIX}Common
)

Add_Executable        (ImportTool   ImportTool.cpp)
Target_Link_Libraries (ImportTool   ${COMMONLIBS})

Add_Executable        (ScoreViewer  ScoreViewer.cpp)
Target_Link_Libraries (ScoreViewer  ${COMMONLIBS})

