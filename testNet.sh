#! /bin/bash

rm -fr ../testing_ai_net

mkdir ../testing_ai_net
cp *.cc ../testing_ai_net
cp *.h ../testing_ai_net
cp Makefile ../testing_ai_net
cp *.c ../testing_ai_net

cd ../testing_ai_net

make clean
make


gcc -o tcp tcp.c

./tcp 213.3.30.106 9999 cagedmantis -p meowmeow ./MyBot >>game_log.log


