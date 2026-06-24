#pragma once

#include "RE/A/Actor.h"
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
    static void ResetAndSetGlobals(const RE::MATERIAL_ID a_id);
    static bool IsGlobalActive(RE::TESGlobal* a_glob);
    static void DeactivateGlobal(RE::TESGlobal* a_glob);
    static void ActivateGlobal(RE::TESGlobal* a_glob);
    static void HandleSnowGLOB();
    static void HandleMudGLOB();
    static void HandleRoadGLOB();
    static void HandleGrassGLOB();
    static void HandleSandGLOB();
    static void HandleWaterGLOB();
    static void DeactivateAllGLOB();
    static RE::TESObjectREFR* GetObjectUnderFeet(const RE::Actor* a_actor);
    static bool IsOnPreferredPath(RE::Actor* a_actor);
};
} // namespace SPEED