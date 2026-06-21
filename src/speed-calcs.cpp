#include "speed-calcs.h"

#include <configs/config.h>

#include "formloader.h"


float SPEED::SpeedHelper::GetTerrainModifier(RE::TESObjectREFR* a_ref)
{

    if (!a_ref)
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

    if (!a_ref->IsHumanoid())
    {
        return 1;
    }


    if (InOnWayStatic(a_ref))
    {
        return SPEED::CONFIG::speed_mult_road.GetValue();
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

    ResetAndSetGlobals(type);

    switch (type)
    {
        case RE::MATERIAL_ID::kSnow:
            return SPEED::CONFIG::speed_mult_snow.GetValue();
        case RE::MATERIAL_ID::kMud:
            return SPEED::CONFIG::speed_mult_mud.GetValue();
        case RE::MATERIAL_ID::kGrass:
            return SPEED::CONFIG::speed_mult_grass.GetValue();
        default:
            return 1;
    }
}
bool SPEED::SpeedHelper::InOnWayStatic(RE::TESObjectREFR* a_ref)
{
    auto ret                          = CheckIsStaticRoad(a_ref) || CheckIsLandRoad(a_ref);
    FormLoader::m_onRoadGlobal->value = ret ? 1 : 0;
    return ret;
}

bool SPEED::SpeedHelper::CheckIsStaticRoad(RE::TESObjectREFR* a_ref)
{

    if (!a_ref)
    {
        return false;
    }

    if (!a_ref->IsPlayerRef())
    {
        return false;
    }

    auto actor = a_ref->As<RE::Actor>();
    if (!actor)
    {
        return false;
    }

    auto cont = actor->GetCharController();
    if (!cont)
    {
        return false;
    }


    auto bod = cont->supportBody;

    if (!bod)
    {
        return false;
    }

    RE::TESObjectREFR* dat = bod->GetUserData();
    if (!dat)
    {
        return false;
    }
    auto base = dat->GetObjectReference();

    if (!base)
    {
        return false;
    }

    RE::TESObjectSTAT* destr = base->As<RE::TESObjectSTAT>();

    if (!destr)
    {
        return false;
    }

    if (FormLoader::m_allRoads.contains(destr))
    {
        return true;
    }
    return false;
}
bool SPEED::SpeedHelper::CheckIsLandRoad(RE::TESObjectREFR* a_ref)
{

    if (!a_ref)
    {
        return false;
    }

    if (!a_ref->IsPlayerRef())
    {
        return false;
    }

    auto tes = RE::TES::GetSingleton();
    if (!tes)
    {
        return false;
    }
    auto landscapeTexture = tes->GetLandTexture(a_ref->GetPosition());
    if (!landscapeTexture)
    {
        return false;
    }

    if (FormLoader::m_allLandscapes.contains(landscapeTexture))
    {
        return true;
    }


    return false;
}
void SPEED::SpeedHelper::ResetAndSetGlobals(const RE::MATERIAL_ID a_id)
{

    switch (a_id)
    {
        case RE::MATERIAL_ID::kSnow:
            if (!IsGlobalActive(FormLoader::m_onSnowGlobal))
            {
                FormLoader::m_onSnowGlobal->value = 1;
            }
            if (IsGlobalActive(FormLoader::m_onMudGlobal))
            {
                FormLoader::m_onMudGlobal->value = 0;
            }
            if (IsGlobalActive(FormLoader::m_onRoadGlobal))
            {
                FormLoader::m_onRoadGlobal->value = 0;
            }
            break;
        case RE::MATERIAL_ID::kMud:
            if (!IsGlobalActive(FormLoader::m_onMudGlobal))
            {
                FormLoader::m_onMudGlobal->value = 1;
            }
            if (IsGlobalActive(FormLoader::m_onSnowGlobal))
            {
                FormLoader::m_onSnowGlobal->value = 0;
            }
            if (IsGlobalActive(FormLoader::m_onRoadGlobal))
            {
                FormLoader::m_onRoadGlobal->value = 0;
            }
            break;
        case RE::MATERIAL_ID::kGrass:
            if (IsGlobalActive(FormLoader::m_onSnowGlobal))
            {
                FormLoader::m_onSnowGlobal->value = 0;
            }
            if (IsGlobalActive(FormLoader::m_onMudGlobal))
            {
                FormLoader::m_onMudGlobal->value = 0;
            }
            if (IsGlobalActive(FormLoader::m_onRoadGlobal))
            {
                FormLoader::m_onRoadGlobal->value = 0;
            }
            break;
        default:
            if (IsGlobalActive(FormLoader::m_onSnowGlobal))
            {
                FormLoader::m_onSnowGlobal->value = 0;
            }
            if (IsGlobalActive(FormLoader::m_onMudGlobal))
            {
                FormLoader::m_onMudGlobal->value = 0;
            }
            if (IsGlobalActive(FormLoader::m_onRoadGlobal))
            {
                FormLoader::m_onRoadGlobal->value = 0;
            }

            return;
    }
}
bool SPEED::SpeedHelper::IsGlobalActive(RE::TESGlobal* a_glob)
{

    return a_glob && a_glob->value > 0;
}
