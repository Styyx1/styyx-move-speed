#pragma once
#include <st-fui.h>

#include "REX/REX/Singleton.h"
namespace SPEED
{
namespace MENU
{

inline const char* DLL_NAME = "styyx-move-speed";

void RegisterMenu();

// call GetSingleton() after registering tool to have the translations available
// TODO: think of better way to do that than this
struct MenuDefines : REX::Singleton<MenuDefines>
{
    std::string m_ModName    = "$SPEEDNAME"_T;
    std::string m_RoadSpeed  = "$ROADSPEEDSETTING"_T;
    std::string m_MudSpeed   = "$MUDSPEEDSETTING"_T;
    std::string m_SnowSpeed  = "$SNOWSPEEDSETTING"_T;
    std::string m_GrassSpeed = "$GRASSSPEEDSETTING"_T;

    std::string m_RoadSpeedHelp  = "$HELP_ROAD"_T;
    std::string m_MudSpeedHelp   = "$HELP_MUD"_T;
    std::string m_SnowSpeedHelp  = "$HELP_SNOW"_T;
    std::string m_GrassSpeedHelp = "$HELP_GRASS"_T;
};

struct Speedy : FUCK::ITool
{
    const char* PluginName() const override { return DLL_NAME; }
    const char* Name() const override { return REX::Singleton<MenuDefines>::GetSingleton()->m_ModName.c_str(); }
    const char* Group() const override { return "Styyx Mods"; }
    void Draw() override;
    void OnOpen() override;
    void OnClose() override;

  private:
    void RestoreDefaults();
    void LoadFromConfig();
    void DrawSystem();
    void DrawSpeedySpeed();
    float _speedRoad{};
    float _speedMud{};
    float _speedSnow{};
    float _speedGrass{};
};
inline Speedy g_speedyTool;

} // namespace MENU

} // namespace SPEED