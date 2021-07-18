add_executable(basic main.cc)
target_link_libraries(basic cicada_core)

install(TARGETS basic 
    RUNTIME DESTINATION bin
)
