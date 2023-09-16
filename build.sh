#!/bin/bash

cc color_slider.c -o color_slider $(pkg-config --cflags --libs "gtk4") -ggdb -O2
