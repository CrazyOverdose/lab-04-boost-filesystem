#!/bin/bash

set -e

cmake -H. -B_builds
cmake --build _builds
./_builds/filesMain