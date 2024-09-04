#include "../lib/sandpile.h"
#include "../lib/argparser.h"
#include "../lib/queue.h"

#include <iostream>

int main(int argc, char** argv) {
    Sandpile sandpile = Sandpile(ParserArguments(argc, argv));

    sandpile.ReadTSV();
    sandpile.SandSpillage();

    return EXIT_SUCCESS;
}