add_executable(basic main.cc)

install(TARGETS basic 
    RUNTIME DESTINATION bin  # 可执行文件安装路径
)
