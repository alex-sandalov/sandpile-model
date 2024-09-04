#pragma once

#include <cstddef>
#include <iostream>
#include <string>

static const char* kShortArgumentInput = "-i";
static const char *kLongArgumentInputEq = "--input=";
static const char *kShortArgumentOutput = "-o";
static const char *kLongArgumentOuputEq = "--output=";
static const char *kShortArgumentMaxIter = "-m";
static const char *kLongArgumentMaxIterEq = "--max-iter=";
static const char *kShortArgumentFreq = "-f";
static const char *kLongArgumentFreqEq = "--freq=";

struct Arguments {
    const char* input_file = "test.tsv";
    const char* directory_path = "img/";
    size_t max_iter = 0;
    size_t freq = 0;
};

Arguments ParserArguments(int argc, char** argv);