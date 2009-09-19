/* vim:ts=4 sts=4 et tw=80
 *
 *         fnordlicht firmware next generation
 *
 *    for additional information please
 *    see http://lochraster.org/fnordlicht
 *
 * (c) by Alexander Neumann <alexander@bumpern.de>
 *     Lars Noschinski <lars@public.noschinski.de>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RC5_H
#define RC5_H

#include "config.h"

#if RC5_DECODER

#include <inttypes.h>

/* warn, if F_CPU is not defined */
#ifndef F_CPU
#error F_CPU not defined
#endif


/* structs */
struct rc5_t {
    union {
        uint16_t raw;
        struct {
            uint8_t code:6;             /* first 6 bits: control code */
            uint8_t address:5;          /* next 5 bits: address */
            uint8_t toggle_bit:1;       /* next bit is the toggle bit */
            uint8_t spare:4;            /* spare bits */
        };
    };
};

struct global_rc5_t {
    struct rc5_t received_command;
    struct {
        uint8_t enabled:1;              /* if one, decoder is active */
        uint8_t new_data:1;             /* if one, new data is available */
    };
};

/* global variables */
extern volatile struct global_rc5_t global_rc5;

/* prototypes */
void init_rc5(void);

#endif

#endif
