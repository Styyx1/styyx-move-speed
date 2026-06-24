#include "menu-defines.h"

#include <configs/config.h>

#include "API/FUCK_API.h"
#include "REX/REX/Singleton.h"
#include "st-fui.h"


namespace SPEED
{
void MENU::RegisterMenu()
{

    if (FUCK::Connect(DLL_NAME))
    {
        FUCK::RegisterTool(&g_speedyTool);
    }
}


void MENU::Speedy::Draw()
{

    if (FUCK::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen))
    {
        DrawSpeedySpeed();
    }
    if (FUCK::CollapsingHeader("System", ImGuiTreeNodeFlags_DefaultOpen))
    {
        DrawSystem();
    }
}
void MENU::Speedy::OnOpen()
{
    LoadFromConfig();
}
void MENU::Speedy::OnClose()
{
    CONFIG::UpdateSetting(true);
}
void MENU::Speedy::RestoreDefaults()
{
    _speedRoad   = 1.3;
    _speedMud    = 0.8;
    _speedSnow   = 0.7;
    _speedGrass  = 0.9;
    _speedSand   = 0.9;
    _enableNPC   = false;
    _enableWater = true;

    CONFIG::speed_mult_road.SetValue(_speedRoad);
    CONFIG::speed_mult_grass.SetValue(_speedGrass);
    CONFIG::speed_mult_mud.SetValue(_speedMud);
    CONFIG::speed_mult_snow.SetValue(_speedSnow);
    CONFIG::speed_mult_sand.SetValue(_speedSand);
    CONFIG::enable_roads_for_npcs.SetValue(_enableNPC);
    CONFIG::slow_in_water.SetValue(_enableWater);

    CONFIG::UpdateSetting(true);
}
void MENU::Speedy::LoadFromConfig()
{
    _speedGrass  = CONFIG::speed_mult_grass.GetValue();
    _speedMud    = CONFIG::speed_mult_mud.GetValue();
    _speedRoad   = CONFIG::speed_mult_road.GetValue();
    _speedSnow   = CONFIG::speed_mult_snow.GetValue();
    _speedSand   = CONFIG::speed_mult_sand.GetValue();
    _enableNPC   = CONFIG::enable_roads_for_npcs.GetValue();
    _enableWater = CONFIG::slow_in_water.GetValue();
}


void MENU::Speedy::DrawSystem()
{

    if (FUCK::Button("Reset"))
    {
        RestoreDefaults();
    }
}
void MENU::Speedy::DrawSpeedySpeed()
{

    auto md = REX::Singleton<MenuDefines>::GetSingleton();
    FUCK::Indent();

    FUCKUtil::Checkbox(md->m_enableNPCRoads.c_str(), _enableNPC, CONFIG::enable_roads_for_npcs,
                       md->m_enableNPCHelp.c_str());
    FUCKUtil::Checkbox(md->m_enableWaterSlow.c_str(), _enableWater, CONFIG::slow_in_water,
                       md->m_enableWaterHelp.c_str());

    FUCKUtil::SliderFloat(md->m_RoadSpeed.c_str(), _speedRoad, CONFIG::speed_mult_road, 0.1, 5.0,
                          md->m_RoadSpeedHelp.c_str());
    FUCKUtil::SliderFloat(md->m_SnowSpeed.c_str(), _speedSnow, CONFIG::speed_mult_snow, 0.1, 5.0,
                          md->m_SnowSpeedHelp.c_str());
    FUCKUtil::SliderFloat(md->m_MudSpeed.c_str(), _speedMud, CONFIG::speed_mult_mud, 0.1, 5.0,
                          md->m_MudSpeedHelp.c_str());
    FUCKUtil::SliderFloat(md->m_GrassSpeed.c_str(), _speedGrass, CONFIG::speed_mult_grass, 0.1, 5.0,
                          md->m_GrassSpeedHelp.c_str());

    FUCKUtil::SliderFloat(md->m_SandSpeed.c_str(), _speedSand, CONFIG::speed_mult_sand, 0.1, 5.0,
                          md->m_SandSpeedHelp.c_str());

    FUCK::Unindent();
}


} // namespace SPEED