#pragma once

/*
code taken from: https://github.com/usernameak/Skyrim_Horseback_Mod/blob/master/Horseback.cpp

License:

Copyright (c) 2023 usernameak

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

namespace SPEED::Roads
{
static float TESObjectREFR_GetRelevantWaterHeight(RE::TESObjectREFR* self)
{
    using func_t = decltype(&TESObjectREFR_GetRelevantWaterHeight);
    REL::Relocation<func_t> func{RELOCATION_ID(19411, 19839)};
    return func(self);
}

struct BSNavmeshInfo;

struct BSNavmeshLocationInfo
{
    uint32_t field_0;
    uint32_t field_4;
    uint32_t field_8;
    uint32_t field_C;
    BSNavmeshInfo* m_navmeshInfo;
    uint64_t field_18;
    uint64_t field_20;
    uint32_t m_triangleIndex;
    uint32_t field_2C;
};

static_assert(sizeof(BSNavmeshLocationInfo) == 0x30);

struct BSNavmeshInfo
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    RE::BSNavmesh* m_navmesh;
};

static void Pathing_GetCharacterLocation(RE::Pathing* self, BSNavmeshLocationInfo* info, RE::TESObjectREFR* refr)
{
    using func_t = decltype(&Pathing_GetCharacterLocation);
    REL::Relocation<func_t> func{RELOCATION_ID(29819, 30635)};
    func(self, info, refr);
}

struct FindTriangleForLocationWaterFilter
{
    void* vftable;
    int field_8;
    int field_C;
    float m_waterHeight;
};

static FindTriangleForLocationWaterFilter* FindTriangleForLocationWaterFilter_ctor(
    FindTriangleForLocationWaterFilter* self, float waterHeight)
{
    using func_t = decltype(&FindTriangleForLocationWaterFilter_ctor);
    REL::Relocation<func_t> func{RELOCATION_ID(88005, 90392)};
    return func(self, waterHeight);
}

static bool BSNavmeshLocationInfo_FindTriangleForLocation(BSNavmeshLocationInfo* self,
                                                          FindTriangleForLocationWaterFilter* filter)
{
    using func_t = decltype(&BSNavmeshLocationInfo_FindTriangleForLocation);
    REL::Relocation<func_t> func{RELOCATION_ID(87983, 90367)};
    return func(self, filter);
}
} // namespace SPEED::Roads
