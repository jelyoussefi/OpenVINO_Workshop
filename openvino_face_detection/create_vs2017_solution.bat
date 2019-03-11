@echo off

:: Copyright (c) 2018 Intel Corporation
::
:: Licensed under the Apache License, Version 2.0 (the "License");
:: you may not use this file except in compliance with the License.
:: You may obtain a copy of the License at
::
::      http://www.apache.org/licenses/LICENSE-2.0
::
:: Unless required by applicable law or agreed to in writing, software
:: distributed under the License is distributed on an "AS IS" BASIS,
:: WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
:: See the License for the specific language governing permissions and
:: limitations under the License.


@setlocal
set "ROOT_DIR=%~dp0"
set "BUILD_DIR=%ROOT_DIR%\build"
if exist "%BUILD_DIR%" rd /s /q "%BUILD_DIR%"
 
if exist "C:\Intel\computer_vision_sdk\bin\setupvars.bat" call "C:\Intel\computer_vision_sdk\bin\setupvars.bat"

echo Creating Visual Studio 2017 (x64) files... && ^
cd "%ROOT_DIR%" && cmake -E make_directory "%BUILD_DIR%" && cd "%BUILD_DIR%" && cmake -G "Visual Studio 15 2017 Win64" "%ROOT_DIR%"


echo Done.
pause