
#pragma once

#include "REX/REX/TOML.h"

namespace SPEED::CONFIG
{

inline REX::TOML::F64 speed_mult_road{"General", "fSpeedMultRoad", 1.5};
inline REX::TOML::F64 speed_mult_snow{"General", "fSpeedMultSnow", 0.5};
inline REX::TOML::F64 speed_mult_mud{"General", "fSpeedMultMud", 0.3};
inline REX::TOML::F64 speed_mult_grass{"General", "fSpeedMultGrass", 0.9};
inline REX::TOML::Bool enable_debug_logs{"Debugging", "bEnableDebugLogs", true};

void UpdateSetting(bool a_save = false);
} // namespace SPEED::CONFIG
