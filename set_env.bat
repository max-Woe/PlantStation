@echo off
setlocal

set "PROJECT_DIR=%~dp0"
set "PLUGINS_PATH=%PROJECT_DIR%java\plugins"
set "NEW_PATH=%PATH%%PLUGINS_PATH
echo PROJECT_DIR: PROJECT_DIR%
echo
echo "PLUGINS_PATH: %PLUGINS_PATH%
echo
echo NewPath: %NEW_PATH%
echo PATH: %PATH%
