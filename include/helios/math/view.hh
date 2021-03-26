/*
 * view.hh
 * Created: 2021-03-08, 18:42:47.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <helios/types.hh>
#include <glm/gtc/matrix_transform.hpp>

namespace hx::math
{
class View {
public:
    View();

    void setSize(const float2_t &size);
    void setPosition(const float2_t &position);
    void setRotation(float rotation);
    void setZoomFactor(float zoom_v);

    void move(const float2_t &velocity);
    void rotate(float angle);
    void zoom(float f);

    const float2_t &getSize() const;
    const float2_t &getPosition() const;
    float getRotation() const;
    float getZoomFactor() const;

    const float4x4_t getMatrix() const;

private:
    float2_t size;
    float2_t position;
    float rotation;
    float zoom_v;
};

inline View::View()
{
    position = float2_t(0.0f, 0.0f);
    rotation = 0.0f;
    zoom_v = 1.0f;
}

inline void View::setSize(const float2_t &size)
{
    this->size = size;
}

inline void View::setPosition(const float2_t &position)
{
    this->position = position;
}

inline void View::setRotation(float rotation)
{
    this->rotation = glm::mod(rotation, 360.0f);
}

inline void View::setZoomFactor(float zoom_v)
{
    this->zoom_v = zoom_v;
}

inline void View::move(const float2_t &velocity)
{
    position += velocity;
}

inline void View::rotate(float angle)
{
    rotation += angle;
    rotation = glm::mod(rotation, 360.0f);
}

inline void View::zoom(float f)
{
    zoom_v *= f;
}

inline const float2_t &View::getSize() const
{
    return size;
}

inline const float2_t &View::getPosition() const
{
    return position;
}

inline float View::getRotation() const
{
    return rotation;
}

inline float View::getZoomFactor() const
{
    return zoom_v;
}

inline const float4x4_t View::getMatrix() const
{
    float4x4_t matrix = float4x4_t(1.0f);
    matrix = glm::translate(matrix, float3_t(size * 0.5f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation), float3_t(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, 1.0f / float3_t(zoom_v, zoom_v, 1.0f));
    matrix = glm::translate(matrix, float3_t(-size * 0.5f, 0.0f));
    matrix = glm::translate(matrix, float3_t(position, 0.0f));
    return matrix;
}
} // namespace hx::math
