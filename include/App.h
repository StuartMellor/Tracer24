class App {
   public:
    App(const int& status) : m_status(status){};
    ~App();
    int run();

   private:
    int m_status;
};