/* $Id: config.h 562 2005-09-11 09:23:14Z choman $ */
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
#ifndef __CONFIG_H
#define __CONFIG_H

#if !defined(WIN32)
# error Use this file only on Windows
#endif 

#define PACKAGE "oniria"

/* Define to the full name of this package. */
#define PACKAGE_NAME "oniria"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "oniria 0.1.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "oniria"

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.1.0"

#include <wx/wxprec.h>
#if defined(wxUSE_STD_STRING)
# undef wxUSE_STD_STRING
#endif
#define wxUSE_STD_STRING 1
#ifndef WX_PRECOMP
# include <wx/wx.h>
#endif
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/xrc/xmlres.h>

#define PLUGINDIR "plugins"
#define DATADIR "data"

#endif
