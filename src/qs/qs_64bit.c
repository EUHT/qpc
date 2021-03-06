/**
* @file
* @brief QS long-long (64-bit) output
* @ingroup qs
* @cond
******************************************************************************
* Last updated for version 6.6.0
* Last updated on  2019-07-30
*
*                    Q u a n t u m  L e a P s
*                    ------------------------
*                    Modern Embedded Software
*
* Copyright (C) 2005-2019 Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <www.gnu.org/licenses>.
*
* Contact information:
* <www.state-machine.com>
* <info@state-machine.com>
******************************************************************************
* @endcond
*/
#define QP_IMPL           /* this is QP implementation */
#include "qs_port.h"      /* QS port */

#if (QS_OBJ_PTR_SIZE == 8) || (QS_FUN_PTR_SIZE == 8)

#include "qs_pkg.h"

/****************************************************************************/
/** @note This function is only to be used through macros, never in the
* client code directly.
*/
void QS_u64_(uint64_t d) {
    uint8_t chksum = QS_priv_.chksum;
    uint8_t *buf   = QS_priv_.buf;
    QSCtr   head   = QS_priv_.head;
    QSCtr   end    = QS_priv_.end;
    int_fast8_t   i;

    QS_priv_.used += (QSCtr)8; /* 8 bytes are about to be added */
    for (i = (int_fast8_t)8; i != (int_fast8_t)0; --i) {
        uint8_t b = (uint8_t)d;
        QS_INSERT_ESC_BYTE(b)
        d >>= 8;
    }

    QS_priv_.head   = head;   /* save the head */
    QS_priv_.chksum = chksum; /* save the checksum */
}

/****************************************************************************/
/** @note This function is only to be used through macros, never in the
* client code directly.
*/
void QS_u64(uint8_t format, uint64_t d) {
    uint8_t chksum = QS_priv_.chksum;
    uint8_t *buf   = QS_priv_.buf;
    QSCtr   head   = QS_priv_.head;
    QSCtr   end    = QS_priv_.end;
    int_fast8_t   i;

    QS_priv_.used += (QSCtr)9; /* 9 bytes are about to be added */
    QS_INSERT_ESC_BYTE(format) /* insert the format byte */

    /* output 8 bytes of data... */
    for (i = (int_fast8_t)8; i != (int_fast8_t)0; --i) {
        format = (uint8_t)d;
        QS_INSERT_ESC_BYTE(format)
        d >>= 8;
    }

    QS_priv_.head   = head;   /* save the head */
    QS_priv_.chksum = chksum; /* save the checksum */
}

#endif /* (QS_OBJ_PTR_SIZE == 8) || (QS_FUN_PTR_SIZE == 8) */

