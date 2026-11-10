#pragma once

class SystemStats {
public:
    void Update(float deltaTime);
    
    float GetCPU() const { return cpu; }
    float GetGPU() const { return gpu; }

private:
    float cpu = 0.0f;
    float gpu = 0.0f;
    float updateTimer = 0.0f;

    float FetchCPULoad();
    float FetchGPULoad();
};