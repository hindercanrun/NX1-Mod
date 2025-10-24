@echo off

for /f %%i in ('git rev-list --count HEAD') do set COUNT=%%i
echo #pragma once > buildInfo.h
echo const int GIT_COMMIT = %COUNT%; >> buildInfo.h