#include "hooks.h"

#include "speed-calcs.h"
#include "st-hooks.h"

namespace SPEED
{

void InstallHooks()
{
    // move speed function (speed scales with height in vanilla)
    // SE ID found in blade and blunt
    HookUtils::WriteCall5<MoveSpeedScaleHook>(RELOCATION_ID(37013, 37943), OFFSET(0x1A, 0x51));
    logs::info("Hooks installed.");
}

float MoveSpeedScaleHook::Call(RE::TESObjectREFR* a_ref)
{
    float original = func(a_ref);

    float modifier = SpeedHelper::GetTerrainModifier(a_ref);
    return original * modifier;
}
} // namespace SPEED
