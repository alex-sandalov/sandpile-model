#include "sandpile.h"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>

Coord::Coord(int16_t x, int16_t y) : x(x), y(y) {}

MatrixAmountOfSand::MatrixAmountOfSand(int64_t size_field)  {
    field = new uint8_t[size_field];
    for (int i = 0; i < size_field; i++) {
        field[i] = static_cast<uint8_t>(0);
    }
}

MatrixAmountOfSand::MatrixAmountOfSand() {} 

uint8_t& MatrixAmountOfSand::operator[](size_t index) {
    return field[index];
}

void MatrixAmountOfSand::SetAmount(size_t coord, int index) {
    field[coord] = static_cast<uint8_t>(index);
}

MatrixAmountOfSand::~MatrixAmountOfSand() {
    delete [] field;
}

Sandpile::Sandpile(Arguments args) 
    : arguments(args) {
    max_sandbox = 0;
}

void Sandpile::CheckMaximumCord(int16_t x_coord, int16_t y_coord) {
    max_x_coord = std::max(max_x_coord, x_coord);
    max_y_coord = std::max(max_y_coord, y_coord);
    min_x_coord = std::min(min_x_coord, x_coord);
    min_y_coord = std::min(min_y_coord, y_coord);
}

void Sandpile::ReadTSV() {
    std::ifstream file(Sandpile::arguments.input_file);
    if (!file.is_open()) {
        std::cerr << "file not found\n";
        return;
    }
    std::string s;
    int16_t x_coord;
    int16_t y_coord;
    uint64_t sandbox;
    while (file >> x_coord >> y_coord >> sandbox) {
        queue_sand.push(Pixel(x_coord, y_coord, sandbox));
        max_sandbox = std::max(max_sandbox, sandbox);
        CheckMaximumCord(x_coord, y_coord);
    }
}

void Draw(uint64_t field[], uint64_t x, uint64_t y) {
    int cnt = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            std::cout << field[cnt] << " "; 
            cnt++;
        }
        std::cout << std::endl;
    }
}

bool Sandpile::Stabilization() {
    bool is_stab = true;
    uint64_t cnt = 0;
    Coord edit_coordinate[] = {Coord(-1, 0), Coord(1, 0), Coord(0, -1), Coord(0, 1)};
    for (int i = 0; i < size * size; i++) {
        if (field[i] > 3) {
            for (auto size_coord : edit_coordinate) {
                field[i]--;
                uint64_t a_coord = i + size_coord.x + size * size_coord.y;
                field[a_coord]++;
            }
            is_stab = false;
        }
    }
    return is_stab;
}

void Sandpile::SandSpillage() {
    size = std::sqrt(max_sandbox) + abs(std::max(max_x_coord - min_x_coord, max_y_coord - min_y_coord)) * 4;
    size += size % 2;
    field = new uint64_t[(size) * (size)];
    std::memset(field, 0, size * size);
    int64_t size_queue = queue_sand.size();
    Coord edit_coordinate[] = {Coord(-1, 0), Coord(1, 0), Coord(0, -1), Coord(0, 1)};
    uint64_t count_iter = 0;
    uint64_t center = size * (size / 2) + size / 2;
    while (!queue_sand.is_empty()) {
        Pixel sand = queue_sand.pop();
        size_t coord = size * sand.x_coord  + sand.y_coord + center;
        size_queue--;
        if (!field[coord]) {
            field[coord] = sand.sandbox;
        }
        if (field[coord] < 3) {
            continue;    
        }
        for (auto size_coord : edit_coordinate) {
            field[coord]--;
            size_t a_coord = size * (sand.x_coord + size_coord.x) + (sand.y_coord + size_coord.y) + center;
            field[a_coord]++;
        }
    }
    bool is_stabil = false;
    int64_t iter = 0;
    while (!Stabilization()) {
        if (arguments.freq && !(iter % arguments.freq)) {
            Sandpile::CreateArrayBmp(iter);
        }
        iter++;
    }
    Sandpile::CreateArrayBmp(count_iter);
}

void Sandpile::CreateArrayBmp(uint64_t iter) {
    MatrixAmountOfSand img = MatrixAmountOfSand(size * size);
    uint64_t coord = 0;
    uint64_t size_img = size;
    for (uint64_t i = 0; i < size; i++) {
        for (uint64_t j = 0; j < size; j++) {
            img.SetAmount(coord, std::min(static_cast<uint64_t>(4), field[coord]));
            coord++;
        }
    }

    std::string file_path = arguments.directory_path + std::to_string(iter) + "sand.bmp";
    Sandpile::CreateBMP(file_path, &img, size_img);
}

void Sandpile::CreateBMP(std::string file_path, MatrixAmountOfSand* img, int64_t size_img) {
    uint64_t width = size_img;
    uint64_t height = size_img;
    static const int16_t fileHeaderSize = 14;
    static const int16_t informationHeaderSize = 40;
    static const int16_t paletteSize = 16;
    
    uint32_t palette[paletteSize] = {
      0x00FFFFFF,
      0x0000FF00,
      0x00FFFF00,
      0x00FF00FF,
      0x00000000
    };

    width = size_img;
    height = size_img;
    std::ofstream file(file_path, std::ios::out | std::ios::binary);

    uint8_t fileHeader[fileHeaderSize];

    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
   
    fileHeader[2] = sizeof(fileHeader);
    fileHeader[3] = sizeof(fileHeader) >> 8;
    fileHeader[4] = sizeof(fileHeader) >> 16;
    fileHeader[5] = sizeof(fileHeader) >> 24;
    
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    
    fileHeader[8] = 0;
    fileHeader[9] = 0;
   
    fileHeader[10] = size;
    fileHeader[11] = size >> 8;
    fileHeader[12] = size >> 16;
    fileHeader[13] = size >> 24;
    
    uint8_t informationHeader[informationHeaderSize];

    informationHeader[0] = sizeof(informationHeader);
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;
    
    informationHeader[4] = width;
    informationHeader[5] = width >> 8;
    informationHeader[6] = width >> 16;
    informationHeader[7] = width >> 24;
   
    informationHeader[8] = height;
    informationHeader[9] = height >> 8;
    informationHeader[10] = height >> 16;
    informationHeader[11] = height >> 24;
    
    informationHeader[12] = 1;
    informationHeader[13] = 0;
   
    informationHeader[14] = 4;

    for (int i = 15; i <= 31; i++) {
        informationHeader[i] = 0;
    }
    
    informationHeader[32] = 16;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;
    
    informationHeader[36] = 16;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    int32_t row = width / 2 + width % 2;
    int32_t padding = (4 - (row % 4)) % 4;
    int32_t total = (row + padding) * height;
    int32_t size = sizeof(palette) + sizeof(fileHeader) + sizeof(informationHeader);

    file.write(reinterpret_cast<char*>(fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<char*>(informationHeader), sizeof(informationHeader));
    file.write(reinterpret_cast<char*>(&palette), sizeof(palette));
    
    uint8_t field[total];
    int16_t cnt = 0;
    int16_t cnt1 = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < row; x++) {
            field[cnt1] = static_cast<uint8_t>((img->field[cnt] << 4) | img->field[cnt + 1]);
            cnt1++;
            cnt += 2;
        }
        for (int k = 0; k < padding; k++) {
            field[cnt1] = static_cast<uint8_t>(0);
            cnt1++;
        }
    }
    file.write(reinterpret_cast<char*>(field), total);
}

Sandpile::~Sandpile() {
    delete [] field;
}