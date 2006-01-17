/* $Id$ */
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
#ifndef __ONIR_H
#define __ONIR_H

#include "dll.h"

#include <stdint.h>
#include <QString>

extern const uint32_t libonir_major_version;
extern const uint32_t libonir_minor_version;
extern const uint32_t libonir_micro_version;
extern const uint32_t libonir_interface_age;
extern const uint32_t libonir_binary_age;

extern QString _libonir_charset;

void LIBONIR_API libonir_init(const QString& charset = "ASCII");
//void libonir_init_log(wxLog * target, bool verbose);
//void LIBONIR_API libonir_init_resources(wxXmlResource * res);

/*!\namespace onir
 * \brief Main libonir namespace.
 *
 * All main interfaces, including oOniria, are located in this namespace.
 */

#endif
