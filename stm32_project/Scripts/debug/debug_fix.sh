
# $1 - Programmer cfg
# $2 - Target cfg

openocd -f $1 -f $2  -c "init" -c "resume" -c "exit"