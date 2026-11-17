#pragma once

namespace Audio {
    void Init();
    void Close();
    void UpdateVolumes(float uiVol, float arenaVol, float popVol);
    
    void PlayClick();
    void PlayPop();
}