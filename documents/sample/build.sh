#!/bin/bash
cd ./bin/Release
g++ -c ../../../../client/source/*.cpp
g++ -c ../../*.cpp -I../../../../client/source/
rm JsonHttpCommunicator.o
rm HttpCommunicator.o
rm Trainer.o
g++ -o sample *.o
./sample >$(date +"%Y_%m_%d_%H_%M_%S").txt
