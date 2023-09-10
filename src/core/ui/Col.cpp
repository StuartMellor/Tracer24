#include "Cell.h"

class Col {
   public:
    Col(const* int rows) : m_rows(rows){};
    void render();

   private:
    int m_rows;
    bool isFocused = false;
};