#pragma once

namespace SPEED
{

inline RE::FormID ALL_ROADS_ID   = 0x1;
inline RE::FormID ON_ROAD_GLOBAL = 0x2;
inline RE::FormID ON_SNOW_GLOBAL = 0x3;
inline RE::FormID ON_MUD_GLOBAL  = 0x4;
inline constexpr auto MOD_NAME   = "MovementOverhaul.esl";
inline constexpr auto JSON_PATH  = "Data/SKSE/Plugins/Roads";


struct FormLoader
{

    static inline RE::BGSListForm* m_allRoadsFromList;
    static inline RE::TESGlobal* m_onRoadGlobal;
    static inline RE::TESGlobal* m_onSnowGlobal;
    static inline RE::TESGlobal* m_onMudGlobal;

    static inline std::unordered_set<RE::TESObjectSTAT*> m_allRoads;
    static inline std::unordered_set<RE::TESLandTexture*> m_allLandscapes;

    static void LoadForms();
    static void CombineFormlists();
};

struct RoadRecords
{
    std::vector<std::string> Landscapes{};
    std::vector<std::string> RoadStats{};
};

struct JsonLoader
{

    static void LoadPatchesJSONFolder();

  private:
    static std::optional<RoadRecords> LoadJsonFile(const std::filesystem::path& a_path);
    static void ParseLandscapes(const RoadRecords& a_roadLandscapes);
    static void ParseRoadStatics(const RoadRecords& a_roadStats);
    static void LoadJson(std::filesystem::path& a_jsonPath);
    static void AddToSet(RE::TESObjectSTAT* a_stat);
    static void AddToRoadSet(RE::TESLandTexture* a_landscape);
};

} // namespace SPEED