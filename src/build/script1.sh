#!/bin/sh

cd build
$1 ../core/viewer.pro
make

mv viewer ../
