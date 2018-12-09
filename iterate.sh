#!bin/bash/

#to generate files to backup find . -name "*.sh"  -o -name "*.cc" -o -name "*.cpp" -o -name "*.hpp" -o -name "*.h" -o -name "makefile" -o -name "Makefile" >> filename.txt
#tobackup stuff run iterate.sh filename.txt 

while read -r line ; do
    echo "Processing $line"
    pathfull=$line
    path=$(dirname $pathfull)
    file=$(basename $pathfull)
    echo $path
    echo $file
    newpath=/home/hep/ss4314/BackupCodeCMTuser$path
    mkdir -p /home/hep/ss4314/BackupCodeCMTuser$path; cp /home/hep/ss4314/cmtuser/$path/$file $newpath;
done < "$1"

