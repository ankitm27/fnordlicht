/* vim:ts=4 sts=4 et tw=80
 *
 *         fnordlicht firmware
 *
 *    for additional information please
 *    see http://lochraster.org/fnordlichtmini
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

#include "../common/io.h"
#include <avr/interrupt.h>

#include "uart.h"

/* define uart mode (8N1) */
#if defined(__AVR_ATmega8__)
/* in atmega8, we need a special switching bit
 * for addressing UCSRC */
#define UART_UCSRC _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1)

#elif defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)
/* in atmega88, this isn't needed any more */
#define UART_UCSRC _BV(_UCSZ0_UART0) | _BV(_UCSZ1_UART0)
#endif

/** output one character */
void uart_putc(uint8_t data)
{
    while(!(_BV(_UDRE_UART0) & _UCSRA_UART0));
    UDR0 = data;
}

/** init the hardware uart */
void uart_init(void)
{
    #define BAUD 19200
    #include <util/setbaud.h>
    /* set baud rate */
    _UBRRH_UART0 = UBRRH_VALUE;
    _UBRRL_UART0 = UBRRL_VALUE;

    #if USE_2X
    _UCSRA_UART0 |= (1 << _U2X_UART0);
    #else
    _UCSRA_UART0 &= ~(1 << _U2X_UART0);
    #endif

    /* set mode */
    _UCSRC_UART0 = UART_UCSRC;

    /* enable transmitter and receiver */
    _UCSRB_UART0 = _BV(_TXEN_UART0) | _BV(_RXEN_UART0);
}