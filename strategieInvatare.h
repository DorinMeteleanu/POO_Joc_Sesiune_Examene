#pragma once
#include <iostream>

class StrategieInvatare {
public:
    virtual void aplicaStrategie(int ore, int& energie, int& stres, int& bonus) = 0;
    virtual int getCooldownValue() const = 0;
    virtual ~StrategieInvatare();
};

class StrategieHardcore : public StrategieInvatare {
public:
    void aplicaStrategie(int ore, int& energie, int& stres, int& bonus) override;
    int getCooldownValue() const;
};

class StrategieRelaxata : public StrategieInvatare {
public:
    void aplicaStrategie(int ore, int& energie, int& stres, int& bonus) override;
    int getCooldownValue() const;
};

class StrategieNormala : public StrategieInvatare {
public:
    void aplicaStrategie(int ore, int& energie, int& stres, int& bonus) override;
    int getCooldownValue() const;
};