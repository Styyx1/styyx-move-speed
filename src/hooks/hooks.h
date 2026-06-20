#pragma once

namespace SPEED
{
void InstallHooks();

struct MoveSpeedScaleHook
{
    static float Call(RE::TESObjectREFR* a_ref);
    static inline REL::Relocation<decltype(Call)> func;
};

} // namespace SPEED
