file(GLOB POLLER_SRCS "*.cc")
file(GLOB POLLER_HEADERS "*.h")

add_library(cicada_poller ${POLLER_SRCS})

install(FILES ${POLLER_HEADERS} DESTINATION include/cicada/core/poller)

install(TARGETS cicada_poller
    ARCHIVE DESTINATION lib
)
