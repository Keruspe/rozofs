include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories(${CMAKE_BINARY_DIR}/src) # for config.h

add_executable(test_list
    ../src/list.h
    test_list.c
)

add_executable(test_htable
    ../src/xmalloc.h
    ../src/xmalloc.c
    ../src/htable.h
    ../src/htable.c
    test_htable.c
)

add_executable(test_dist
    ../src/xmalloc.h
    ../src/xmalloc.c
    ../src/dist.h
    test_dist.c
)

add_executable(test_transform
    ../src/xmalloc.h
    ../src/xmalloc.c
    ../src/transform.h
    ../src/transform.c
    test_transform.c
)
target_link_libraries(test_transform -lm)

add_executable(rpc_throughput
    ../src/rpcclt.h
    ../src/rpcclt.c
    rpc_throughput.h
    rpc_throughputxdr.c
    rpc_throughputclt.c
    rpc_throughput_client.c
)

add_executable(rpc_throughput_server
    rpc_throughput.h
    rpc_throughputxdr.c
    rpc_throughput_server.c
    rpc_throughputsvc.c
)

add_executable(transform_throughput
    ../src/xmalloc.h
    ../src/xmalloc.c
    ../src/transform.h
    ../src/transform.c
    transform_throughput.c
)
target_link_libraries(transform_throughput -lm)

add_executable(transform_file
    ../src/xmalloc.h
    ../src/xmalloc.c
    ../src/transform.h
    ../src/transform.c
    transform_file.c
)
target_link_libraries(transform_file -lm)

add_executable(test_volume
    ../src/xmalloc.h
    ../src/xmalloc.c
    ../src/rozofs.h
    ../src/rozofs.c
    ../src/rpcclt.h
    ../src/rpcclt.c
    ../src/sproto.h
    ../src/sprotoxdr.c
    ../src/sprotoclt.c
    ../src/storageclt.c
    ../src/volume.h
    ../src/volume.c
    test_volume.c
)
target_link_libraries(test_volume ${PTHREAD_LIBRARY})

add_executable(test_storage
    ../src/xmalloc.h
    ../src/xmalloc.c
    ../src/rozofs.h
    ../src/rozofs.c
    ../src/htable.h
    ../src/htable.c
    ../src/storage.h
    ../src/storage.c
    test_storage.c
)
target_link_libraries(test_storage ${UUID_LIBRARY})

add_executable(test_sconfig
    ../src/xmalloc.h
    ../src/xmalloc.c
    ../src/sconfig.h
    ../src/sconfig.c
    test_sconfig.c
)
target_link_libraries(test_sconfig ${CONFIG_LIBRARY})

add_executable(test_econfig
    ../src/xmalloc.h
    ../src/xmalloc.c
    ../src/econfig.h
    ../src/econfig.c
    test_econfig.c
)
target_link_libraries(test_econfig ${CONFIG_LIBRARY})
