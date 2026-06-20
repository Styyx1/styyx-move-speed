#include "formloader.h"

#include <filesystem>
#include <glaze/glaze.hpp>
#include <optional>
#include <st-forms.h>


namespace SPEED
{

void FormLoader::LoadForms()
{

    auto dh            = RE::TESDataHandler::GetSingleton();
    m_allRoadsFromList = dh->LookupForm<RE::BGSListForm>(ALL_ROADS_ID, MOD_NAME);
    m_onRoadGlobal     = dh->LookupForm<RE::TESGlobal>(ON_ROAD_GLOBAL, MOD_NAME);
    m_onMudGlobal      = dh->LookupForm<RE::TESGlobal>(ON_MUD_GLOBAL, MOD_NAME);
    m_onSnowGlobal     = dh->LookupForm<RE::TESGlobal>(ON_SNOW_GLOBAL, MOD_NAME);

    if (!MiscUtil::IsModLoaded(MOD_NAME))
    {
        SKSE::stl::report_and_fail(std::format("{} is not active, make sure to activate it", MOD_NAME));
    }

    if (m_allRoadsFromList)
    {
        CombineFormlists();
    }

    JsonLoader::LoadPatchesJSONFolder();
}
void FormLoader::CombineFormlists()
{

    std::vector<RE::TESObjectSTAT*> temp;
    m_allRoadsFromList->ForEachForm(
        [&](RE::TESForm* a_formInList)
        {
            if (a_formInList)
            {
                if (auto stat = a_formInList->As<RE::TESObjectSTAT>(); stat)
                {
                    m_allRoads.insert(stat);
                    logs::info("added {} to vector", stat->GetFormID());
                    return RE::BSContainer::ForEachResult::kContinue;
                }
            }
            return RE::BSContainer::ForEachResult::kContinue;
        });
}

void JsonLoader::LoadPatchesJSONFolder()
{

    const std::filesystem::path folder(JSON_PATH);
    auto folder_str = folder.string();
    if (!std::filesystem::exists(folder) || !std::filesystem::is_directory(folder))
    {
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(folder))
    {
        bool is_json = entry.path().extension() == ".json";

        if (!entry.is_regular_file() || !is_json)
        {
            continue;
        }
        const auto config = LoadJsonFile(entry.path());
        if (!config)
        {
            continue;
        }

        logs::info("Reading [{}]", entry.path().filename().string());
        ParseLandscapes(*config);
        ParseRoadStatics(*config);
    }
}
std::optional<RoadRecords> JsonLoader::LoadJsonFile(const std::filesystem::path& a_path)
{

    std::string buffer{};
    RoadRecords loaded_roads{};

    const auto ec =
        glz::read_file_json<glz::opts{.error_on_unknown_keys = false}>(loaded_roads, a_path.string(), buffer);
    if (!ec)
    {
        return loaded_roads;
    }
    return std::nullopt;
}
void JsonLoader::ParseLandscapes(const RoadRecords& a_roadLandscapes)
{

    for (const auto& landscape : a_roadLandscapes.Landscapes)
    {
        if (auto landForm = FormUtil::GetFormFromString(landscape))
        {
            auto land = landForm->As<RE::TESLandTexture>();
            if (land)
            {
                AddToRoadSet(land);
            }
        }
    }
}
void JsonLoader::ParseRoadStatics(const RoadRecords& a_roadStats)
{

    for (const auto& roadStr : a_roadStats.RoadStats)
    {
        if (auto statForm = FormUtil::GetFormFromString(roadStr))
        {
            auto stat = statForm->As<RE::TESObjectSTAT>();
            if (stat)
            {
                AddToSet(stat);
            }
        }
    }
}


void JsonLoader::AddToSet(RE::TESObjectSTAT* a_stat)
{

    if (!a_stat)
    {
        return;
    }
    FormLoader::m_allRoads.insert(a_stat);
    logs::info("added {} from json", editorID::get_editorID(a_stat));
}
void JsonLoader::AddToRoadSet(RE::TESLandTexture* a_landscape)
{

    if (!a_landscape)
    {
        return;
    }
    FormLoader::m_allLandscapes.insert(a_landscape);
    logs::info("added {} from json", editorID::get_editorID(a_landscape));
};
} // namespace SPEED