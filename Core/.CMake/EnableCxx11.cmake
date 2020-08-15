
Include (CheckCXXCompilerFlag)

Check_CXX_Compiler_Flag("-std=gnu++14"  COMPILER_ACCEPTS_GNU14)
Check_CXX_Compiler_Flag("-std=gnu++11"  COMPILER_ACCEPTS_GNU11)
Check_CXX_Compiler_Flag("-std=c++11"    COMPILER_ACCEPTS_CXX11)
Check_CXX_Compiler_Flag("-std=c++0x"    COMPILER_ACCEPTS_CXX0X)

If ( COMPILER_ACCEPTS_GNU14 )
    Message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} Accepts -std=gnu++14")
    Set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -std=gnu++14")
ElseIf ( COMPILER_ACCEPTS_GNU11 )
    Message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} Accepts -std=gnu++11")
    Set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -std=gnu++11")
ElseIf ( COMPILER_ACCEPTS_CXX11 )
    Message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} Accepts -std=c++11")
    Set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -std=c++11")
ElseIf ( COMPILER_ACCEPTS_CXX0X )
    Message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} Accepts -std=c++0x")
    Set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -std=c++0x")
Else  ()
    Message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} : No Support c++11")
EndIf ()

