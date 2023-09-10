class Clock {
   public:
    Clock(const int& steps, const int& cols, const float& tempo)
        : m_steps(steps), m_cols(cols), m_tempo(tempo){};
    int start();
    void changeTempo(float tempo);
    int stop();
    int reset();
    void performStep();

    void clockLoop();

   private:
    float m_tempo;
    float m_tempoMs;
    int m_steps;
    int m_currentStep;
    int m_loopCount;
    int m_cols;
};