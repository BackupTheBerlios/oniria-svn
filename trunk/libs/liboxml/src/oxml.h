/* $Id: oxml.h 639 2006-01-03 14:22:18Z choman $ */
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
#ifndef __OXML_H
#define __OXML_H

#include "dll.h"

#include <stdint.h>
#include <QString>

extern const uint32_t liboxml_major_version;
extern const uint32_t liboxml_minor_version;
extern const uint32_t liboxml_micro_version;
extern const uint32_t liboxml_interface_age;
extern const uint32_t liboxml_binary_age;

extern QString _liboxml_charset;

void LIBOXML_API liboxml_init(const QString& charset = "ASCII");

#endif
