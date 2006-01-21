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
#ifndef _SASLDIGESTMD5_H
#define _SASLDIGESTMD5_H

#include <QString>
#include <stdint.h>
#include "osasl_dll.h"
#include "saslMechanism.h"

namespace onirSASL {

/*!\class saslDIGESTMD5
 * \brief DIGEST-MD5 mechanism.
 */
class LIBOSASL_API saslDIGESTMD5 : public saslMechanism {

	Q_OBJECT

	public:
		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn saslDIGESTMD5()
		 * \brief Constructor.
		 */
		saslDIGESTMD5();

		/*!\fn virtual ~saslDIGESTMD5()
		 * \brief Destructor.
		 */
		virtual ~saslDIGESTMD5();
		//@}

		virtual bool response(QByteArray * challenge, QByteArray * response);

	protected:
		bool step1(QByteArray * challenge, QByteArray * response);
		bool step2(QByteArray * challenge, QByteArray * response);

	private:
		int _step;
};

};

#endif
