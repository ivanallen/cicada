set(CXX_FLAGS
    -g
    -O0
)

add_executable(timer main.cc)
target_link_libraries(timer cicada_core)

install(TARGETS timer
    RUNTIME DESTINATION bin
)
