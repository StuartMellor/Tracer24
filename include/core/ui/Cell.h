#include "imgui"

class Cell {
   public:
    void render() {
        // Render an outlined box with three text fields
        ImGui::BeginGroup();
        ImGui::Text("Cell");
        ImGui::InputText("##cell", NULL, 0);
        ImGui::EndGroup();
    }

    void select() {
        m_isFocused = true;
    }

   private:
    bool m_isFocused = false;
    bool isActive = false;
}