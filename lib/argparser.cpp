#include "argparser.h"

#include <cstring>

Arguments ParserArguments(int argc, char** argv) {
    Arguments arguments;
    for (int i = 1; i < argc; i++) {
        if (i + 1 < argc && !std::strcmp(kShortArgumentInput, argv[i])) {
            arguments.input_file = argv[++i];
        } else if (i + 1 < argc && !std::strcmp(kShortArgumentOutput, argv[i])) {
            arguments.directory_path = argv[++i];
        } else if (i + 1 < argc && !std::strcmp(kShortArgumentMaxIter, argv[i])) {
            arguments.max_iter = std::atoi(argv[++i]);
        } else if (i + 1 < argc && !std::strcmp(kShortArgumentFreq, argv[i])) {
            arguments.freq = std::atoi(argv[++i]);
        } else if (!std::strncmp(kLongArgumentInputEq, argv[i], std::strlen(kLongArgumentInputEq))) {
            arguments.input_file = std::strlen(kLongArgumentInputEq) + argv[i];
        } else if (!std::strncmp(kLongArgumentOuputEq, argv[i], std::strlen(kLongArgumentOuputEq))) {
            arguments.directory_path = std::strlen(kLongArgumentOuputEq) + argv[i];
        } else if (!std::strncmp(kLongArgumentFreqEq, argv[i], std::strlen(kLongArgumentFreqEq))) {
            arguments.max_iter = std::atoi(std::strlen(kLongArgumentFreqEq) + argv[i]);
        } else if (!std::strncmp(kLongArgumentMaxIterEq, argv[i], std::strlen(kLongArgumentMaxIterEq))) {
            arguments.freq = std::atoi(std::strlen(kLongArgumentMaxIterEq) + argv[i]);
        } else {
            std::cerr << "Error args\n";
            exit(EXIT_FAILURE);
        }
    }
    return arguments;
}