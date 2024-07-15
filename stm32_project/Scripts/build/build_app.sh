DIRNAME="$(dirname "$(readlink -f "$0")")"

if [ $2 == "build" ]; then

    # $1 - Makefile dir
    # $2 - Makefile func
    # $3 - Makefile arg
    # $4 - Output dir
    # $5 - Outfile name
    # $6 - Cmakelist
    # $7 - artifact_path
    # $8 - sensor define

    make -C $1 $2 $3 output_path=$4 outfile=$5 cmakelist=$6 sns_def=-D$8
    mkdir -p $7
    cp -f $1/$4/*.bin $1/$4/*.hex $7

elif [ $2 == "clean" ]; then

    # $1 - Project dir
    # $2 - func
    # $3 - boot output
    # $4 - app output
    # $5 - artifacts

    rm -rf $3 
    rm -rf $4
    rm -rf $5

elif [ $2 == "flash" ]; then
    make --makefile=$1/Makefile $2 $3 artifact_dir=$4 outfile=$5 openocd=$6 programmer_cfg=$7 target_cfg=$8

elif [ $2 == "erase" ]; then
    make --makefile=$1/Makefile $2 openocd=$3 first_sector=$4 second_sector=$5 programmer_cfg=$6 target_cfg=$7

elif [ $2 == "lock" ]; then
    make --makefile=$1/Makefile $2 openocd=$3 openocd_cfg=$4 programmer_cfg=$5 target_cfg=$6

elif [ $2 == "unlock" ]; then
    make --makefile=$1/Makefile $2 openocd=$3 openocd_cfg=$4 programmer_cfg=$5 target_cfg=$6

elif [ $2 == "reset" ]; then
    make --makefile=$1/Makefile $2 openocd=$3 programmer_cfg=$4 target_cfg=$5

fi
