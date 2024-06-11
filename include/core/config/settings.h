namespace Tracer {
namespace config {
class Settings {
   public:
    Settings();
    Settings(const int& tracks, const int& steps) : m_nTracks(tracks), m_steps(steps){};
    int getTracks() const { return m_nTracks; }
    int getSteps() const { return m_steps; }
    int getSubTracks() const { return m_subTracks; }

    void saveSettings();
    void loadSettings();

   private:
    int m_nTracks = 4;
    int m_steps = 128;
    int m_subTracks = 3;
};
}  // namespace config
}  // namespace Tracer