/*
 * clock.hh
 * Created: 2021-03-02, 22:55:43.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

namespace util
{
class Clock {
public:
    Clock();

    float getTime() const;
    float reset();

private:
    float start;
};
} // namespace util
