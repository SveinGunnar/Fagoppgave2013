@echo off
rem AAW, s181087
set CC=     g++
set CFLAGS= -g -Wno-write-strings -Iinc -Llib
set CMODS=  main.cpp config.cpp log.cpp opengl.cpp openglext.cpp input.cpp vector.cpp matrix.cpp camera.cpp shader.cpp shaderman.cpp texture.cpp textureman.cpp sprite.cpp background.cpp renderman.cpp bitmap.cpp generator.cpp grid.cpp blocks.cpp mesh.cpp noise/simplex1234.c soundman.cpp sound.cpp music.cpp gameman.cpp entity.cpp physics.cpp player.cpp unit.cpp
set LFLAGS= -lwinmm -lbass -lglfw -lopengl32
set LOUT=   -o game

%CC% %CFLAGS% %CMODS% %LFLAGS% %LOUT%
