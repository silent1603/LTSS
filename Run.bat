@echo off

if exist bin\image.ppm (
  rm -f bin\image.ppm
  echo. bin\image.ppm
) else (
  echo. bin\image.ppm
)

.\bin\RayTracing.exe >> .\bin\image.ppm