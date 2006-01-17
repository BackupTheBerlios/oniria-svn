/* $Id: dll.h 184 2005-07-26 20:05:20Z choman $ */
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
#ifndef __DLL_H
#define __DLL_H

#if defined(WIN32)
# if BUILDING_LIBONIR_DLL
#  define LIBONIR_API __declspec (dllexport)
# else /* Not BUILDING_LIBONIR_DLL */
#  define LIBONIR_API __declspec (dllimport)
# endif /* Not BUILDING_LIBONIR_DLL */
#else
# define LIBONIR_API
#endif

#endif /* __DLL_H_ */
