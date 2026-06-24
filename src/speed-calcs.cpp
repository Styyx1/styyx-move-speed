#include "speed-calcs.h"

#include <configs/config.h>

#include "formloader.h"
#include "roads.h"

float SPEED::SpeedHelper::GetTerrainModifier(RE::TESObjectREFR* a_ref)
{

    if (!a_ref || !a_ref->Is3DLoaded() || a_ref->IsDead())
    {
        return 1;
    }
    auto cell = a_ref->GetParentCell();
    if (!cell)
    {
        return 1;
    }
    if (!cell->IsExteriorCell())
    {
        return 1;
    }

    if (InOnWayStatic(a_ref))
    {
        return SPEED::CONFIG::speed_mult_road.GetValue();
    }

    // after road check to have horses benefit from road modifiers
    if (!a_ref->IsHumanoid())
    {
        return 1;
    }

    auto tes = RE::TES::GetSingleton();
    if (!tes)
    {
        return 1;
    }
    auto landscapeTexture = tes->GetLandTexture(a_ref->GetPosition());
    if (!landscapeTexture)
    {
        return 1;
    }

    auto mato = landscapeTexture->materialType;
    if (!mato)
    {
        return 1;
    }


    auto type = mato->materialID;

    // important to do only on player
    if (a_ref->IsPlayerRef())
    {
        ResetAndSetGlobals(type);
    }

    auto sub =
        CONFIG::slow_in_water.GetValue() ? a_ref->GetSubmergeLevel(a_ref->GetPositionZ(), a_ref->GetParentCell()) : -1;


    if (sub > 0)
    {
        logs::info("submerged level is: {}", sub);
        auto actor = a_ref->As<RE::Actor>();

        if (actor && !actor->IsSwimming() && sub > 0.3)
        {
            return 1.1 - sub;
        }
    }


    switch (type)
    {
        case RE::MATERIAL_ID::kSnow:
            return SPEED::CONFIG::speed_mult_snow.GetValue();
        case RE::MATERIAL_ID::kMud:
            return SPEED::CONFIG::speed_mult_mud.GetValue();
        case RE::MATERIAL_ID::kGrass:
            return SPEED::CONFIG::speed_mult_grass.GetValue();
        case RE::MATERIAL_ID::kSand:
            return SPEED::CONFIG::speed_mult_sand.GetValue();
        default:
            return 1;
    }
}
bool SPEED::SpeedHelper::InOnWayStatic(RE::TESObjectREFR* a_ref)
{
    auto actor = a_ref->As<RE::Actor>();
    if (!actor)
    {
        return false;
    }
    if (actor->IsInCombat())
    {
        DeactivateAllGLOB();
        return false;
    }
    auto ret = IsOnPreferredPath(actor);
    if (a_ref->IsPlayerRef())
    {
        HandleRoadGLOB();
    }
    return ret;
}

void SPEED::SpeedHelper::ResetAndSetGlobals(const RE::MATERIAL_ID a_id)
{

    switch (a_id)
    {
        case RE::MATERIAL_ID::kSnow:
            HandleSnowGLOB();
            break;
        case RE::MATERIAL_ID::kMud:
            HandleMudGLOB();
            break;
        case RE::MATERIAL_ID::kGrass:
            HandleGrassGLOB();
            break;
        case RE::MATERIAL_ID::kSand:
            HandleSandGLOB();
            break;
        default:
            DeactivateAllGLOB();
            return;
    }
}
bool SPEED::SpeedHelper::IsGlobalActive(RE::TESGlobal* a_glob)
{

    return a_glob && a_glob->value > 0;
}
void SPEED::SpeedHelper::DeactivateGlobal(RE::TESGlobal* a_glob)
{

    if (IsGlobalActive(a_glob))
    {
        a_glob->value = 0;
    }
}
void SPEED::SpeedHelper::ActivateGlobal(RE::TESGlobal* a_glob)
{

    if (!IsGlobalActive(a_glob))
    {
        a_glob->value = 1;
    }
}
void SPEED::SpeedHelper::HandleSnowGLOB()
{
    ActivateGlobal(FormLoader::m_onSnowGlobal);
    DeactivateGlobal(FormLoader::m_inGrassGlobal);
    DeactivateGlobal(FormLoader::m_onRoadGlobal);
    DeactivateGlobal(FormLoader::m_inWaterGlobal);
    DeactivateGlobal(FormLoader::m_onSandGlobal);
    DeactivateGlobal(FormLoader::m_onMudGlobal);
}
void SPEED::SpeedHelper::HandleMudGLOB()
{
    ActivateGlobal(FormLoader::m_onMudGlobal);
    DeactivateGlobal(FormLoader::m_inGrassGlobal);
    DeactivateGlobal(FormLoader::m_onRoadGlobal);
    DeactivateGlobal(FormLoader::m_inWaterGlobal);
    DeactivateGlobal(FormLoader::m_onSandGlobal);
    DeactivateGlobal(FormLoader::m_onSnowGlobal);
}
void SPEED::SpeedHelper::HandleRoadGLOB()
{
    ActivateGlobal(FormLoader::m_onRoadGlobal);
    DeactivateGlobal(FormLoader::m_inGrassGlobal);
    DeactivateGlobal(FormLoader::m_onSnowGlobal);
    DeactivateGlobal(FormLoader::m_inWaterGlobal);
    DeactivateGlobal(FormLoader::m_onSandGlobal);
    DeactivateGlobal(FormLoader::m_onMudGlobal);
}
void SPEED::SpeedHelper::HandleGrassGLOB()
{
    ActivateGlobal(FormLoader::m_inGrassGlobal);
    DeactivateGlobal(FormLoader::m_onSnowGlobal);
    DeactivateGlobal(FormLoader::m_onRoadGlobal);
    DeactivateGlobal(FormLoader::m_inWaterGlobal);
    DeactivateGlobal(FormLoader::m_onSandGlobal);
    DeactivateGlobal(FormLoader::m_onMudGlobal);
}
void SPEED::SpeedHelper::HandleSandGLOB()
{
    ActivateGlobal(FormLoader::m_onSandGlobal);
    DeactivateGlobal(FormLoader::m_inGrassGlobal);
    DeactivateGlobal(FormLoader::m_onRoadGlobal);
    DeactivateGlobal(FormLoader::m_inWaterGlobal);
    DeactivateGlobal(FormLoader::m_onSnowGlobal);
    DeactivateGlobal(FormLoader::m_onMudGlobal);
}
void SPEED::SpeedHelper::HandleWaterGLOB()
{
    ActivateGlobal(FormLoader::m_inWaterGlobal);
    DeactivateGlobal(FormLoader::m_inGrassGlobal);
    DeactivateGlobal(FormLoader::m_onRoadGlobal);
    DeactivateGlobal(FormLoader::m_onSnowGlobal);
    DeactivateGlobal(FormLoader::m_onSandGlobal);
    DeactivateGlobal(FormLoader::m_onMudGlobal);
}
void SPEED::SpeedHelper::DeactivateAllGLOB()
{
    DeactivateGlobal(FormLoader::m_inWaterGlobal);
    DeactivateGlobal(FormLoader::m_inGrassGlobal);
    DeactivateGlobal(FormLoader::m_onRoadGlobal);
    DeactivateGlobal(FormLoader::m_onSnowGlobal);
    DeactivateGlobal(FormLoader::m_onSandGlobal);
    DeactivateGlobal(FormLoader::m_onMudGlobal);
}
RE::TESObjectREFR* SPEED::SpeedHelper::GetObjectUnderFeet(const RE::Actor* a_actor)
{

    if (!a_actor)
    {
        return nullptr;
    }

    const auto charController = a_actor->GetCharController();
    const auto supportBody    = charController ? charController->supportBody : nullptr;

    return supportBody ? supportBody->GetUserData() : nullptr;
}
bool SPEED::SpeedHelper::IsOnPreferredPath(RE::Actor* a_actor)
{

    auto ref = a_actor->AsReference();
    if (!ref || !ref->Is3DLoaded() || ref->IsDead())
    {
        return false;
    }
    float relWaterHeight = Roads::TESObjectREFR_GetRelevantWaterHeight(ref);
    auto pathing         = RE::Pathing::GetSingleton();

    Roads::BSNavmeshLocationInfo navmeshInfo{};
    Pathing_GetCharacterLocation(pathing, &navmeshInfo, ref);

    Roads::FindTriangleForLocationWaterFilter filter{};
    Roads::FindTriangleForLocationWaterFilter_ctor(&filter, relWaterHeight);

    if (BSNavmeshLocationInfo_FindTriangleForLocation(&navmeshInfo, &filter) && navmeshInfo.m_navmeshInfo &&
        navmeshInfo.m_triangleIndex < 0xFFFF)
    {
        if (auto* navmesh = navmeshInfo.m_navmeshInfo->m_navmesh)
        {
            bool isPreferred = navmesh->triangles[navmeshInfo.m_triangleIndex].triangleFlags.all(
                RE::BSNavmeshTriangle::TriangleFlag::kPreferred);
            if (isPreferred)
            {
                return true;
            }
        }
    }
    return false;
}
