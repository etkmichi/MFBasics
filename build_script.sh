#!/bin/bash
build_target=$1
job_count=$(nproc --all)
directory=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
echo $directory
cd $directory
if [ "$build_target" == "h" -o "$build_target" == "help" -o "$build_target" == "-h" -o "$build_target" == "--help" ]; then
    echo "r|R|release|Release - create release build target"
    echo "d|D|debug|Debug - create debug build target"
    echo "c|C|clean|Clean - clean debug and release builds"
    exit 0
fi
case $build_target in
"r"|"R"|"release")build_target="Release";;
"d"|"D"|"debug")build_target="Debug";;
"c"|"C"|"clean")build_target="Clean";;
esac

export MF_PROJECTS_DIR="$directory"
export MF_BASICS_DIR="$directory/MFBasics"
while [ "$build_target" != "Debug" -a "$build_target" != "Release" -a "$build_target" != "Clean" ]
do
    echo "No build target defined!"
    echo "1==Debug  2==Release  3==clean  4==exit"
    read -p "" input_v
    case $input_v in
        "1")build_target="Debug";;
        "2")build_target="Release";;
        "3")build_target="Clean";;
        "4")exit 0;;
        *)
            echo "Invalid input!"
            $build_target="";;
    esac
done
if [ "$build_target" == "Clean" ]; then
    cd $directory/MFBasics/Debug
    make clean
    cd $directory/MFBasics/Release
    make clean
else
    echo "build target set to $build_target"
    cd $directory/MFBasics/$build_target
    make all -j$job_count
fi