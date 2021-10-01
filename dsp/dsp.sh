#!/bin/bash

if [ -z "$1" ]; then
  echo no param
  exit
fi

cd ../microcosmos-v2.5/src/

rm -r dsp

echo "../../dsp/${1}/dsp"

ln -s "../../dsp/${1}/dsp" dsp
