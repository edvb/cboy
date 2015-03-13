#!/bin/sh

vim src/cboy.h src/main.c \
    -O2 src/map.c src/map.h src/item.c src/entity.c src/player.c src/data.c

