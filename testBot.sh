#! /bin/bash

rm -fr ../testing_ai

mkdir ../testing_ai
cp *.cc ../testing_ai
cp *.h ../testing_ai
cp Makefile ../testing_ai

cd ../testing_ai

make clean
make

java -jar ../Google-AI-Challenge/tools/PlayGame.jar ../Google-AI-Challenge/maps/map8.txt 1000 200 log.txt "java -jar ../Google-AI-Challenge/example_bots/BullyBot.jar" "./MyBot" | java -jar ../Google-AI-Challenge/tools/ShowGame.jar



