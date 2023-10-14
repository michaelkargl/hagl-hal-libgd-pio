#!/bin/sh

git submodule foreach --recursive 'git submodule init && git submodule update'

platformio run --target upload --environment native
