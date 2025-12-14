# 加载当前目录下所有的源文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(../redis REDIS_LIST)

#include_directories(${PROJECT_SOURCE_DIR}/thirdparty)  # 显式添加头文件路径
#include_directories(${PROJECT_SOURCE_DIR}/include/server)  # 显式添加头文件路径
#include_directories(${PROJECT_SOURCE_DIR}/include/server/db)

#link_directories(/usr/lib64/mysql)s

# 指定生成可执行文件
add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})

# 指定可执行文件链接时需要的库文件
target_link_libraries(ChatServer muduo_net muduo_base /usr/lib64/mysql/libmysqlclient.so hiredis pthread)