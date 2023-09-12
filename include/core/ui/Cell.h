namespace Tracer {
namespace ui {
class Cell {
   public:
    void render();
    void select();

   private:
    bool m_isFocused = false;
    bool isActive = false;
};
}  // namespace ui
}  // namespace Tracer