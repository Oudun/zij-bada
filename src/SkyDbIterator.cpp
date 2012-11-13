/*
 * SkyDbIterator.cpp
 *
 *  Created on: 24.10.2012
 *      Author: ddreval
 */

#include "SkyDbIterator.h"

using namespace Osp::Base;
using namespace Osp::Io;

SkyDbIterator::SkyDbIterator(float magnitude) {
	String databaseName(L"/Home/stars.db");
	Database database;
	database.Construct(databaseName, false);
	String query(L"select * from stars where magnitude > ");
	query.Append(magnitude);
	DbStatement* stat = database.CreateStatementN(query);
	dataSet = database.ExecuteStatementN(*stat);
	delete stat;
	database.~Database();
	databaseName.~String();
}

SkyDbIterator::~SkyDbIterator() {
	delete dataSet;
}

bool
SkyDbIterator::hasNext() {
	result r = E_SUCCESS;
	r = dataSet->MoveNext();
	return IsFailed(r);
}

SkyObject*
SkyDbIterator::getNext() {
	String greek;
	dataSet->GetStringAt(1, greek);
	AppLog("Greek name is %S", greek.GetPointer());
	return null;
}


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
