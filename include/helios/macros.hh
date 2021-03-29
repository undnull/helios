/*
 * macros.hh
 * Created: 2021-03-24, 09:22:20.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

/**
 * @brief Merges namespaces together.
 * 
 * @param target Namespace to merge with.
 * @param source Namespace to merge.
 */
#define MERGE_NAMESPACE(target, source) \
    namespace target                    \
    {                                   \
    using namespace source;             \
    }
