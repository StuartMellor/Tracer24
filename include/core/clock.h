class Clock {
   public:
    Clock();
    void performStep();

   private:
    float m_tempo;
    int m_steps;
    int m_currentStep;
};