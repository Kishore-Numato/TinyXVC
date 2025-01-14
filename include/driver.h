/*
 * Copyright 2020 Sergey Guralnik
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "txvc_defs.h"

#include <stdbool.h>
#include <stdint.h>

struct txvc_driver {
    const char *name;
    const char *help;

    bool (*activate)(const char **argNames, const char **argValues);
    bool (*deactivate)(void);

    int (*max_vector_bits)(void);
    int (*set_tck_period)(int tckPeriodNs);
    bool (*shift_bits)(int numBits,
            const uint8_t *tmsVector,
            const uint8_t *tdiVector,
            uint8_t *tdoVector
            );
} TXVC_ALIGNED(16);

#define TXVC_DRIVER(name) \
    static const struct txvc_driver txvc_driver_ ## name \
        TXVC_SECTION(.txvc_driver) TXVC_USED TXVC_ALIGNED(16)

extern const struct txvc_driver* txvc_enumerate_drivers(
        bool (*fn)(const struct txvc_driver *d, const void *extra), const void *extra);

