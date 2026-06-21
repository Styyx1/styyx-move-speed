#include "configs/config.h"
#include "formloader.h"
#include "hooks/hooks.h"
#include "menu/menu-defines.h"

void Listener(SKSE::MessagingInterface::Message* a_msg)
{
    switch (a_msg->type)
    {
        case SKSE::MessagingInterface::kDataLoaded:
            SPEED::FormLoader::LoadForms();
            SPEED::MENU::RegisterMenu();
            break;
        default:
            break;
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    Init(skse);

    SPEED::CONFIG::UpdateSetting();
    SKSE::AllocTrampoline(14);
    SPEED::InstallHooks();
    SKSE::GetMessagingInterface()->RegisterListener(Listener);
    return true;
}