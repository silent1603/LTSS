@echo off

if exist build\ (
  echo Build Folder exist
) else (
  echo Error: Directory /path/to/dir does not exists.
  echo Create: Directory /path/to/dir does not exists.
  mkdir build
)

cd build
cmake ..