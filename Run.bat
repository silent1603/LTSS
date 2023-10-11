@echo off

if exist bin\image.ppm (
    Del bin\image.ppm
)
echo. bin\image.ppm

.\bin\RayTracing.exe >> .\bin\image.ppm