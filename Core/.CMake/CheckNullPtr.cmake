
Include (CheckCXXSourceCompiles)

check_cxx_source_compiles(
   "int main () {
        void * p = nullptr;
        return ( 0 );
    }"
    CMAKE_CHECK_CXX_NULLPTR_ENABLED
)
If ( CMAKE_CHECK_CXX_NULLPTR_ENABLED )
    set(CONFIG_CHECK_CXX_NULLPTR_ENABLED  1)
Else()
    set(CONFIG_CHECK_CXX_NULLPTR_ENABLED  0)
EndIf()

