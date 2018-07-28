/* ISO7816-3 state machine for the card side
 *
 * (C) 2010-2017 by Harald Welte <hwelte@hmw-consulting.de>
 * (C) 2018 by sysmocom -s.f.m.c. GmbH, Author: Kevin Redon <kredon@sysmocom.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA
 */
#pragma once

#include <stdint.h>

struct card_handle;

enum card_io {
	CARD_IO_VCC,
	CARD_IO_RST,
	CARD_IO_CLK,
};

struct card_handle *card_emu_init(uint8_t slot_num, uint8_t tc_chan, uint8_t uart_chan,
				  uint8_t in_ep, uint8_t irq_ep);

/* process a single byte received from the reader */
void card_emu_process_rx_byte(struct card_handle *ch, uint8_t byte);

/* transmit a single byte to the reader */
int card_emu_tx_byte(struct card_handle *ch);

/* hardware driver informs us that a card I/O signal has changed */
void card_emu_io_statechg(struct card_handle *ch, enum card_io io, int active);

/* User sets a new ATR to be returned during next card reset */
int card_emu_set_atr(struct card_handle *ch, const uint8_t *atr, uint8_t len);

struct llist_head *card_emu_get_uart_tx_queue(struct card_handle *ch);
void card_emu_have_new_uart_tx(struct card_handle *ch);
void card_emu_report_status(struct card_handle *ch);

#define ENABLE_TX	0x01
#define ENABLE_RX	0x02

int card_emu_uart_update_fidi(uint8_t uart_chan, unsigned int fidi);
int card_emu_uart_tx(uint8_t uart_chan, uint8_t byte);
void card_emu_uart_enable(uint8_t uart_chan, uint8_t rxtx);
void card_emu_uart_wait_tx_idle(uint8_t uart_chan);
void card_emu_uart_interrupt(uint8_t uart_chan);
