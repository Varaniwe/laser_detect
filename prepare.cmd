@echo off
rmdir /S /Q build
@set script_dir=%~dp0

@set arch=i386
@set CMAKE_GENERATOR=Visual Studio 15 2017

@mkdir %script_dir%\build 2>nul 1>nul
@set build_dir=%script_dir%\build\%arch%
@mkdir %build_dir% 2>nul 1>nul
@pushd %build_dir%
shift
cmake -WSdev -G "%CMAKE_GENERATOR%" %* ..\..
@popd