#include <string>
#include <vector>

struct TracerData {
    int rows;
    int cols;
    int cursor[2];
    std::vector<std::vector<CellData>> cellData;
    std::string fileName;
    time_t lastModified;
};

struct CellData {
    // identifier and value
    unsigned char iv[2][5];
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