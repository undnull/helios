/*
 * types.hh
 * Created: 2021-01-16, 15:28:51.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <config.hh>

#include <functional>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <mutex>
#include <sstream>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using float4x4_t = glm::mat<4, 4, float, glm::packed_highp>;

using float2_t = glm::vec<2, float, glm::packed_highp>;
using float3_t = glm::vec<3, float, glm::packed_highp>;
using float4_t = glm::vec<4, float, glm::packed_highp>;

namespace std
{
constexpr const size_t PRIME1 = 73856093;
constexpr const size_t PRIME2 = 19349663;
constexpr const size_t PRIME3 = 83492791;
constexpr const size_t PRIME4 = 10916527;

template<>
struct hash<float2_t> {
    inline size_t operator()(const float2_t &v) const
    {
        glm::vec<2, size_t, glm::packed_highp> iv(v);
        return (iv.x * PRIME1) ^ (iv.y * PRIME2);
    }
};

template<>
struct hash<float3_t> {
    inline size_t operator()(const float3_t &v) const
    {
        glm::vec<3, size_t, glm::packed_highp> iv(v);
        return (iv.x * PRIME1) ^ (iv.y * PRIME2) * (iv.z * PRIME3);
    }
};

template<>
struct hash<float4_t> {
    inline size_t operator()(const float4_t &v) const
    {
        glm::vec<4, size_t, glm::packed_highp> iv(v);
        return (iv.x * PRIME1) ^ (iv.y * PRIME2) ^ (iv.z * PRIME3) ^ (iv.w * PRIME4);
    }
};
} // namespace std
