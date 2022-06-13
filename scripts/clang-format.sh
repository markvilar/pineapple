#!/usr/bin/bash

find ./bin -iname *.hpp -o -iname *.cpp \
    | xargs clang-format -style=file -i -fallback-style=none

find ./examples -iname *.hpp -o -iname *.cpp \
    | xargs clang-format -style=file -i -fallback-style=none

find ./pineapple -iname *.hpp -o -iname *.cpp \
    | xargs clang-format -style=file -i -fallback-style=none

exit 0
