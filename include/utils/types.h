#ifndef TRACER_TYPES
#define TRACER_TYPES

#include <string>
#include <vector>

namespace Tracer {

struct CursorPos {
    int col;
    int row;
    int sub;
};

struct CellData {
    // identifier and value
    unsigned char iv[2][5];
};

struct GridState {
    int selectedRow = -1;
    int selectedCol = -1;
};

struct TracerData {
    int rows;
    int cols;
    int cursor[2];
    std::vector<std::vector<CellData>> cellData;
    std::string fileName;
    time_t lastModified;
};

enum TracerStatusCode {
    OK,
    EXIT,
    SAVING,
};

struct Action {
    int type;
    int row;
    int col;
    int value;
    int identifier;
    int direction;
    int steps;
    int tempo;
    int cursor[2];
    std::string fileName;
    time_t lastModified;
};
}  // namespace Tracer

#endif  // !TRACER_TYPES