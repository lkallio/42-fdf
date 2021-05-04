# 42-fdf -- A Heightmap Visualizer
> *My only hope is that one day we will be able to visualize simple wireframe heightmaps.* - Alan Turing

![title](https://media.giphy.com/media/aayRtWTPmH293aNHsz/giphy.gif)

## Install

1. brew install libx11 ; brew install libxext
2. git clone [this repo]
3. make

![t2](https://i.imgur.com/uy1MeA2.png)

## Use

- run ./fdf to see usage
- testmaps are in the file tests

## What it is

- accepts any files describing heights as numeric values -- the x, z positions will be taken from the position of those numbers
- displays a heightmap according to the file
- accepts many arguments to change the display mode (e.g. --color=0xff0000 will make the wireframe red, adding --gradient will make it go from red to cyan)
