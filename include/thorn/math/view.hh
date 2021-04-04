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
#include <thorn/types.hh>
#include <glm/gtc/matrix_transform.hpp>

namespace thorn::math
{
/**
 * @brief Camera transformation.
 * 
 */
class View {
public:
    /**
     * @brief Constructor.
     * 
     */
    View();

    /**
     * @brief Sets the camera viewport size.
     * 
     * @param size Screen size in pixels.
     */
    void setSize(const float2_t &size);

    /**
     * @brief Sets the camera position.
     * 
     * @param position Camera position in pixels.
     */
    void setPosition(const float2_t &position);

    /**
     * @brief Sets the camera rotation.
     * 
     * @param rotation Camera rotation in degrees.
     */
    void setRotation(float rotation);

    /**
     * @brief Sets the camera zoom factor.
     * 
     * @param zoom_v Zoom factor.
     */
    void setZoomFactor(float zoom_v);

    /**
     * @brief Moves the camera.
     * 
     * @param velocity Delta.
     */
    void move(const float2_t &velocity);

    /**
     * @brief Rotates the camera.
     * 
     * @param angle Delta.
     */
    void rotate(float angle);

    /**
     * @brief Zooms the camera.
     * 
     * @param f Factor.
     */
    void zoom(float f);

    /**
     * @brief Gets the camera viewport size.
     * 
     * @return Viewport size in pixels.
     */
    const float2_t &getSize() const;

    /**
     * @brief Gets the camera position.
     * 
     * @return Camera position in pixels.
     */
    const float2_t &getPosition() const;

    /**
     * @brief Gets the camera rotation.
     * 
     * @return Camera rotation in degrees.
     */
    float getRotation() const;

    /**
     * @brief Gets the camera zoom factor.
     * 
     * @return Zoom factor.
     */
    float getZoomFactor() const;

    /**
     * @brief Updates the matrices.
     * 
     */
    void update();

    /**
     * @brief Generats a projection matrix of the camera.
     * 
     * @return Projection matrix.
     */
    const float4x4_t &getProjectionMatrix();

    /**
     * @brief Generates a view matrix of the camera.
     * 
     * @return View matrix.
     */
    const float4x4_t &getViewMatrix();

private:
    float2_t size;
    float2_t position;
    float rotation;
    float zoom_v;

    bool projection_update;
    float4x4_t projection;

    bool view_update;
    float4x4_t view;
};

inline View::View()
    : position(0.0f, 0.0f), rotation(0.0f), zoom_v(1.0f), projection_update(true), view_update(true)
{
}

inline void View::setSize(const float2_t &size)
{
    this->size = size;
    projection_update = true;
    view_update = true;
}

inline void View::setPosition(const float2_t &position)
{
    this->position = position;
    view_update = true;
}

inline void View::setRotation(float rotation)
{
    this->rotation = glm::mod(rotation, 360.0f);
    view_update = true;
}

inline void View::setZoomFactor(float zoom_v)
{
    this->zoom_v = zoom_v;
    view_update = true;
}

inline void View::move(const float2_t &velocity)
{
    position += velocity;
    view_update = true;
}

inline void View::rotate(float angle)
{
    rotation += angle;
    rotation = glm::mod(rotation, 360.0f);
    view_update = true;
}

inline void View::zoom(float f)
{
    zoom_v *= f;
    view_update = true;
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

inline const float4x4_t &View::getProjectionMatrix()
{
    if(projection_update) {
        projection = glm::ortho(0.0f, size.x, size.y, 0.0f, -1.0f, 1.0f);
        projection_update = false;
    }

    return projection;
}

inline const float4x4_t &View::getViewMatrix()
{
    if(view_update) {
        view = float4x4_t(1.0f);
        view = glm::translate(view, float3_t(size * 0.5f, 0.0f));
        view = glm::rotate(view, glm::radians(rotation), float3_t(0.0f, 0.0f, 1.0f));
        view = glm::scale(view, 1.0f / float3_t(zoom_v, zoom_v, 1.0f));
        view = glm::translate(view, float3_t(-size * 0.5f, 0.0f));
        view = glm::translate(view, float3_t(position, 0.0f));
        view_update = false;
    }

    return view;
}
} // namespace thorn::math
