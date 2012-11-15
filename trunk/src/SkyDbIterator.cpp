/*
 * SkyDbIterator.cpp
 * Getting sky objects from SQLite table
 * create table stars (
 *		greek string,
 *		constellation string,
 *		magnitude float,
 *		ra float,
 *		dec float,
 *		northern int)
 *  Created on: 24.10.2012
 *      Author: ddreval
 */

#include "SkyDbIterator.h"

using namespace Osp::Base;
using namespace Osp::Io;

SkyDbIterator::SkyDbIterator(float magnitude) {
	result r = E_SUCCESS;
	nextObject = new SkyObject();
	AppLog("Building DB iterator");
	String databaseName(L"/Home/stars.db");
	database = new Database();
	r = database->Construct(databaseName, false);
	AppLogDebug("DB creation result is %S", GetErrorMessage(r));
	String query(L"select * from stars where magnitude < ");
	query.Append(magnitude);
	DbStatement* stat = database->CreateStatementN(query);
	dataSet = database->ExecuteStatementN(*stat);
}

SkyDbIterator::~SkyDbIterator() {
	delete database;
	delete dataSet;
}

bool
SkyDbIterator::hasNext() {
	result r = E_SUCCESS;
	r = dataSet->MoveNext();
	AppLog("Iteration result is %S", GetErrorMessage(r));
	return !IsFailed(r);
}

SkyObject*
SkyDbIterator::getNext() {
	String strHolder;
	double floatHolder;
	int intHolder;
	dataSet->GetStringAt(1, strHolder);
	nextObject->setName(strHolder);
	dataSet->GetDoubleAt(3, floatHolder);
	nextObject->setRAH(floatHolder);
	dataSet->GetDoubleAt(4, floatHolder);
	nextObject->setDED(floatHolder);
	dataSet->GetDoubleAt(2, floatHolder);
	nextObject->setMagnitude(floatHolder);
	dataSet->GetIntAt(5, intHolder);
	nextObject->setSign(intHolder == 1);
	return nextObject;
}
