#pragma once

#include "queue.h"
#include "argparser.h"

#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

struct Coord {
    int16_t x;
    int16_t y;

    Coord(int16_t x, int16_t y);
};

struct MatrixAmountOfSand {
    uint8_t* field;
    uint64_t size;

    MatrixAmountOfSand();   

    MatrixAmountOfSand(int64_t size_field);

    void SetAmount(size_t coord, int index);

    uint8_t& operator[](size_t index);

    ~MatrixAmountOfSand();
};

class Sandpile {
public:
    Sandpile(Arguments args);

    void CheckMaximumCord(int16_t x_coord, int16_t y_coord);

    bool Stabilization();

    void ReadTSV();

    void CreateArrayBmp(uint64_t iter);

    void CreateBMP(std::string path, MatrixAmountOfSand* img, int64_t size_img);

    void SandSpillage();

    ~Sandpile();

private:
    Arguments arguments;

    int16_t max_x_coord = 0;
    int16_t max_y_coord = 0;
    int16_t min_x_coord = 0;
    int16_t min_y_coord = 0;

    uint64_t max_sandbox;

    uint64_t size;

    uint64_t *field;

    Queue queue_sand;
};