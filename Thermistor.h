#include <Arduino.h>

class Thermistor
{
private:

    size_t m_AI;
    double m_T0, m_RT0, m_B, m_VCC, m_R;
public:
    Thermistor(size_t AI, double T0, double RT0, double B, double VCC, double R);
    double GetTempInK();
    double GetTempInC();
    double GetTempInF();
    ~Thermistor();
};

Thermistor::Thermistor(size_t AI, double T0, double RT0, double B, double VCC, double R) :
m_AI(AI),
m_T0(T0),
m_RT0(RT0),
m_B(B),
m_VCC(VCC),
m_R(R)
{
}

double Thermistor::GetTempInK()
{
    double VRT = analogRead(m_AI);
    VRT = (5.00 / 1023.00) * VRT;
    double VR = m_VCC - VRT;
    double RT = VRT / (VR / m_R);
    double ln = log(RT / m_RT0);

    return (1 / ((ln / m_B) + (1 / m_T0)));
}

double Thermistor::GetTempInC()
{
    return GetTempInK() - 273.15;
}

double Thermistor::GetTempInF()
{
    return (GetTempInK() - 273.15) * 1.8 + 32;
}

Thermistor::~Thermistor()
{
}