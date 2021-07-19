file(GLOB BASE_SRCS "*.cc")
file(GLOB BASE_HEADERS "*.h")

add_library(cicada_base ${BASE_SRCS})
#add_dependencies(cicada_base glog)
target_link_libraries(cicada_base glog)

install(FILES ${BASE_HEADERS} DESTINATION include/cicada/base)

install(TARGETS cicada_base
    ARCHIVE DESTINATION lib
)
