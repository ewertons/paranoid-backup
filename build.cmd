if NOT EXIST cmake (
    mkdir cmake
)

cd cmake
del /s /q *
rmdir /s /q *

cmake ..
msbuild pbkp.sln

cd ..