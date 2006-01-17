/* $Id: oObject.h 632 2006-01-02 14:56:49Z choman $ */
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
#ifndef __OOBJECT_H
#define __OOBJECT_H

#include <QObject>
#include <QString>
#include <QList>
#include "dll.h"

namespace onir {

#define DECLARE_OOBJECT
#define DEFINE_OOBJECT(__class, __base)
#define INIT_OOBJECT

/*!\class oObject
 * \brief Base class for almost all libonir classes.
 *
 * \deprecated This class is only for backward compatibility. It's just QObject.
 */
class LIBONIR_API oObject : public QObject {
		Q_OBJECT;
};



};

#endif
