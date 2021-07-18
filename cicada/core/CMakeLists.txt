file(GLOB CORE_SRCS "*.cc")
file(GLOB CORE_HEADERS "*.h")

add_library(cicada_core ${CORE_SRCS})

install(FILES ${CORE_HEADERS} DESTINATION include/cicada/core)

install(TARGETS cicada_core
    ARCHIVE DESTINATION lib
)
