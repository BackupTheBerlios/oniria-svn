/* $Id: onir.cc 620 2005-12-30 15:24:23Z choman $ */
/*
 * Copyright (C) 2005
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#if defined(HAVE_CONFIG_H)
# include <config.h>
#endif
#include <stdint.h>
#if defined(WIN32)
# include "win32/onir_config.h"
#else
# include "onir_config.h"
#endif
#include "dll.h"
#include "onir.h"

const uint32_t libonir_major_version = ONIR_MAJOR_VERSION;
const uint32_t libonir_minor_version = ONIR_MINOR_VERSION;
const uint32_t libonir_micro_version = ONIR_MICRO_VERSION;
const uint32_t libonir_interface_age = ONIR_INTERFACE_AGE;
const uint32_t libonir_binary_age = ONIR_BINARY_AGE;

QString _libonir_charset;

void LIBONIR_API libonir_init(const QString& cset)
{
	_libonir_charset = cset;
}

