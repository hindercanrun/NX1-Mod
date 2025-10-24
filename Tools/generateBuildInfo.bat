@echo off

set OUTPUT_DIR=D:\ns\nx\1\plugins\NX1Gaming\Tools\

for /f %%i in ('git rev-list --count HEAD') do set COUNT=%%i

echo #pragma once > "%OUTPUT_DIR%\buildInfo.h"
echo const int GIT_COMMIT = %COUNT%; >> "%OUTPUT_DIR%\buildInfo.h"
