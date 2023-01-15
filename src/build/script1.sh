#!/bin/sh

cd build
$1 ../core/*.pro
make

mv viewer ../
