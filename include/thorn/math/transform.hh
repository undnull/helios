/*
 * transform.hh
 * Created: 2021-03-07, 22:54:23.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <thorn/types.hh>
#include <glm/gtc/matrix_transform.hpp>

namespace thorn::math
{
/**
 * @brief Object transform.
 * 
 */
class Transform {
public:
    /**
     * @brief Constructor
     * 
     */
    Transform();

    /**
     * @brief Sets the object origin.
     * 
     * @param origin Origin in pixels.
     */
    void setOrigin(const float2_t &origin);

    /**
     * @brief Sets the object position.
     * 
     * @param position Position in pixels.
     */
    void setPosition(const float2_t &position);

    /**
     * @brief Sets the object rotation.
     * 
     * @param rotation Rotation in degrees.
     */
    void setRotation(float rotation);

    /**
     * @brief Sets the object scale.
     * 
     * @param scale_v Scale.
     */
    void setScale(float scale_v);

    /**
     * @brief Moves the object.
     * 
     * @param velocity Delta.
     */
    void move(const float2_t &velocity);

    /**
     * @brief Rotates the object.
     * 
     * @param angle Delta.
     */
    void rotate(float angle);

    /**
     * @brief Scales the object.
     * 
     * @param f Scale factor.
     */
    void scale(float f);

    /**
     * @brief Gets the object origin.
     * 
     * @return Origin in pixels.
     */
    const float2_t &getOrigin() const;

    /**
     * @brief Gets the object position.
     * 
     * @return Position in pixels.
     */
    const float2_t &getPosition() const;

    /**
     * @brief Gets the object rotation.
     * 
     * @return Rotation in degrees.
     */
    float getRotation() const;

    /**
     * @brief Gets the object Scale.
     * 
     * @return Scale factor.
     */
    float getScale() const;

    /**
     * @brief Generates a model matrix of the object.
     * 
     * @return Model matrix.
     */
    const float4x4_t &getMatrix();

private:
    float2_t origin;
    float2_t position;
    float rotation;
    float scale_v;

    bool needs_update;
    float4x4_t matrix;
};

inline Transform::Transform()
{
    origin = float2_t(0.0f, 0.0f);
    position = float2_t(0.0f, 0.0f);
    rotation = 0.0f;
    scale_v = 1.0f;
    needs_update = true;
}

inline void Transform::setOrigin(const float2_t &origin)
{
    this->origin = origin;
    needs_update = true;
}

inline void Transform::setPosition(const float2_t &position)
{
    this->position = position;
    needs_update = true;
}

inline void Transform::setRotation(float rotation)
{
    this->rotation = rotation;
    needs_update = true;
}

inline void Transform::setScale(float scale_v)
{
    this->scale_v = scale_v;
    needs_update = true;
}

inline void Transform::move(const float2_t &velocity)
{
    position += velocity;
    needs_update = true;
}

inline void Transform::rotate(float angle)
{
    rotation += angle;
    needs_update = true;
}

inline void Transform::scale(float f)
{
    scale_v *= f;
    needs_update = true;
}

inline const float2_t &Transform::getOrigin() const
{
    return origin;
}

inline const float2_t &Transform::getPosition() const
{
    return position;
}

inline float Transform::getRotation() const
{
    return rotation;
}

inline float Transform::getScale() const
{
    return scale_v;
}

inline const float4x4_t &Transform::getMatrix()
{
    if(needs_update) {
        matrix = float4x4_t(1.0f);
        matrix = glm::translate(matrix, float3_t(position, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(rotation), float3_t(0.0f, 0.0f, 1.0f));
        matrix = glm::scale(matrix, float3_t(scale_v, scale_v, 1.0f));
        matrix = glm::translate(matrix, float3_t(-origin, 0.0f));
    }

    return matrix;
}
} // namespace thorn::math
