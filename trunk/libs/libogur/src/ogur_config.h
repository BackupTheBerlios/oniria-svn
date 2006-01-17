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
#ifndef __OGUR_CONFIG_H
#define __OGUR_CONFIG_H

#if !defined(WIN32)
# error Use this file only on Windows
#endif

#define OGUR_MAJOR_VERSION	0
#define OGUR_MINOR_VERSION	1
#define OGUR_MICRO_VERSION	0
#define OGUR_INTERFACE_AGE	0
#define OGUR_BINARY_AGE		0

#define PACKAGE		"libogur"
#define LOCALEDIR	"locales"
#define DATADIR 	"data"

#endif
