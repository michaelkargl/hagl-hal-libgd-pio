#!/bin/sh

script_path="$0"
script_dir="$(dirname $script_path)"


cd "$script_dir"
git submodule foreach --recursive 'git submodule init && git submodule update'
platformio run --target upload --environment native
cd -
