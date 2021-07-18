file(GLOB CORE_SRCS "*.cc")
file(GLOB CORE_HEADERS "*.h")

add_subdirectory(tests)
add_subdirectory(poller)

add_library(cicada_core ${CORE_SRCS})
#target_link_libraries(cicada_core cicada_poller)

install(FILES ${CORE_HEADERS} DESTINATION include/cicada/core)

install(TARGETS cicada_core
    ARCHIVE DESTINATION lib
)
