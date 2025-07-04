option(WEB "Build WEB" OFF)
option(STAGING "Staging build" OFF)

add_custom_target(
    npm_install
    COMMAND npm install
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "Installing npm dependencies"
)

add_custom_target(
    npm_run_build
    COMMAND npm run build
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "Running npm run build"
)

add_custom_target(
    npm_run_staging
    COMMAND npm run staging
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "Running npm run staging"
)

add_custom_target(
    deploy_www
    COMMAND rm -rf ${CMAKE_CURRENT_LIST_DIR}/../rootfs/usr/share/supervisor/www/*
    COMMAND mkdir -p ${CMAKE_CURRENT_LIST_DIR}/../rootfs/usr/share/supervisor/www/
    COMMAND cp -r ${CMAKE_CURRENT_LIST_DIR}/dist/* ${CMAKE_CURRENT_LIST_DIR}/../rootfs/usr/share/supervisor/www/
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "Deploying web files"
)

if(STAGING)
    add_dependencies(npm_run_build npm_run_staging)
else()
    add_dependencies(npm_run_build npm_install)
endif()

add_dependencies(deploy_www npm_run_build)

if(WEB)
add_dependencies(${PROJECT_NAME} deploy_www)
endif()