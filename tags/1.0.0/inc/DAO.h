/*
 * DAO.h
 *
 *  Created on: 12.04.2013
 *      Author: ddreval
 */

#ifndef DAO_H_
#define DAO_H_

#include<FBase.h>
#include<FIo.h>

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Io;

class DAO {

	public:
		DAO();
		virtual ~DAO();
		static ICollectionT<String&>* getCountries();
		static ICollectionT<String&>* getCities(String& countryName);

};

static Osp::Io::Database* database;

#endif /* DAO_H_ */
