#pragma once

#include "RE/M/MaterialIDs.h"
#include "RE/T/TESGlobal.h"
#include "RE/T/TESObjectREFR.h"
namespace SPEED
{
struct SpeedHelper
{

    static float GetTerrainModifier(RE::TESObjectREFR* a_ref);
    static bool InOnWayStatic(RE::TESObjectREFR* a_ref);

  private:
    static bool CheckIsStaticRoad(RE::TESObjectREFR* a_ref);
    static bool CheckIsLandRoad(RE::TESObjectREFR* a_ref);
    static void ResetAndSetGlobals(const RE::MATERIAL_ID a_id);
    static bool IsGlobalActive(RE::TESGlobal* a_glob);
};
} // namespace SPEED