/*
 * DAO.cpp
 *
 *  Created on: 12.04.2013
 *      Author: ddreval
 */

#include "DAO.h"

DAO::DAO() {
	String databaseName(L"/Home/stars.db");
	database = new Database();
	result r = database->Construct(databaseName, false);
	AppLogDebug("DB creation result is %S", GetErrorMessage(r));

}

DAO::~DAO() {

}

ICollectionT<String&>*
DAO::getCountries() {
	Osp::Io::DbEnumerator* dataSet;
	String countriesQuery(L"select name from countries");
	DbStatement* countriesStat = database->CreateStatementN(countriesQuery);
	dataSet = database->ExecuteStatementN(*countriesStat);
	ArrayListT<String&>* result = new ArrayListT<String&>();
	while (dataSet->MoveNext() == E_SUCCESS) {
		String name;
		dataSet->GetStringAt(1, name);
		result->Add(name);
	}
	return result;
}

ICollectionT<String&>*
DAO::getCities(String& countryName) {
	Osp::Io::DbEnumerator* dataSet;
	String citiesQuery(L"select name from cities where country like '");
	citiesQuery.Append(countryName);
	citiesQuery.Append("'");
	DbStatement* citiesStat = database->CreateStatementN(citiesQuery);
	dataSet = database->ExecuteStatementN(*citiesStat);
	ArrayListT<String&>* result = new ArrayListT<String&>();
	while (dataSet->MoveNext() == E_SUCCESS) {
		String name;
		dataSet->GetStringAt(1, name);
		result->Add(name);
	}
	return result;
}

