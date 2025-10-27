SOURCE_FILES="file.cpp filesystem.cpp main.cpp"
EXECUTABLE_NAME="program"
COMPILER="g++"

echo "Compiling and linking..."
$COMPILER -o $EXECUTABLE_NAME $SOURCE_FILES

if [ $? -eq 0 ]; then
    echo "Build successful! Executable created: $EXECUTABLE_NAME"
    echo "Running $EXECUTABLE_NAME..."
    echo "-----------------------------------------"
    ./$EXECUTABLE_NAME "$@"
    echo "-----------------------------------------"
else
    echo "Build failed. Please check the compilation errors above."
fi
