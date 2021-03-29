/*
 * framebuffer.hh
 * Created: 2021-03-02, 22:30:07.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <helios/gl/texture.hh>

namespace hx::gl
{
/**
 * @brief Render target.
 * 
 */
class Framebuffer {
public:
    /**
     * @brief Constructor
     * 
     */
    Framebuffer();
    
    /**
     * @brief Move constructor.
     * 
     * @param rhs Existing framebuffer.
     */
    Framebuffer(Framebuffer &&rhs);
    Framebuffer(const Framebuffer &rhs) = delete;

    /**
     * @brief Destructor
     * 
     */
    virtual ~Framebuffer();

    /**
     * @brief Assign operator.
     * 
     * @param rhs Existing framebuffer.
     * @return this
     */
    Framebuffer &operator=(Framebuffer &&rhs);
    Framebuffer &operator=(const Framebuffer &rhs) = delete;

    /**
     * @brief Attaches a texture to the framebuffer's attachment point.
     * 
     * @param attachment Texture attachment.
     * @param texture Texture to attachs.
     * @param level Texture level.
     */
    void attach(GLenum attachment, const Texture &texture, GLint level);

    /**
     * @brief Checks the buffer completion status.
     * 
     * @return true if the framebuffer is complete and false otherwise.
     */
    bool isComplete();

    /**
     * @brief Gets an OpenGL handle of the framebuffer.
     * 
     * @return An OpenGL handle.
     */
    constexpr GLuint get() const;

private:
    GLuint framebuffer;
};

inline Framebuffer::Framebuffer()
{
    glCreateFramebuffers(1, &framebuffer);
}

inline Framebuffer::Framebuffer(Framebuffer &&rhs)
{
    framebuffer = rhs.framebuffer;
    rhs.framebuffer = 0;
}

inline Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &framebuffer);
}

inline Framebuffer &Framebuffer::operator=(Framebuffer &&rhs)
{
    Framebuffer copy(std::move(rhs));
    std::swap(copy.framebuffer, framebuffer);
    return *this;
}

inline void Framebuffer::attach(GLenum attachment, const Texture &texture, GLint level)
{
    glNamedFramebufferTexture(framebuffer, attachment, texture.get(), level);
}

inline bool Framebuffer::isComplete()
{
    return glCheckNamedFramebufferStatus(framebuffer, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

inline constexpr GLuint Framebuffer::get() const
{
    return framebuffer;
}
} // namespace hx::gl
