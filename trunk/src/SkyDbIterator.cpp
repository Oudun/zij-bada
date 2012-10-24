/*
 * SkyDbIterator.cpp
 *
 *  Created on: 24.10.2012
 *      Author: ddreval
 */

#include "SkyDbIterator.h"

SkyDbIterator::SkyDbIterator() {
	// TODO Auto-generated constructor stub

}

SkyDbIterator::~SkyDbIterator() {
	// TODO Auto-generated destructor stub
}

bool
SkyDbIterator::hasNext() {

}

SkyObject* getNext() {
	return null;
}

//AppLog("App initialized");
//String pDatabaseName(L"/Home/test.db");
//Database myDatabase;
//String sql;
//result r = E_SUCCESS;
//AppLog("1");
//r = myDatabase.Construct(pDatabaseName, false);
//AppLog("DB creation result is %S", GetErrorMessage(r));
//sql.Append(L"select * from tbl1");
//DbStatement* stat = myDatabase.CreateStatementN(sql);
//AppLog("2");
//DbEnumerator* res = myDatabase.ExecuteStatementN(*stat);
//while (res->MoveNext() == E_SUCCESS) {
//	String str;
//	res->GetStringAt(0, str);
//	AppLog("String %S", str.GetPointer());
//}
//
//AppLog("3");
//return true;
