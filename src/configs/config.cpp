#include "config.h"

void SPEED::CONFIG::UpdateSetting(bool a_save)
{
    const auto toml = REX::Singleton<REX::TOML::SettingStore>::GetSingleton();
    toml->Init("Data/SKSE/Plugins/speed.toml", "Data/SKSE/Plugins/speed_custom.toml");

    if (!a_save)
    {
        toml->Load();
    }
    else
    {
        toml->Save();
    }
}