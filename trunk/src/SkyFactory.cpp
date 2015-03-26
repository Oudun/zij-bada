/*
 * SkyFactory.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Denis
 */

#include "SkyFactory.h"
#include "SkyDbIterator.h"

using namespace Osp::Io;

SkyFactory::SkyFactory() {
	// TODO Auto-generated constructor stub

}

SkyFactory::~SkyFactory() {
	// TODO Auto-generated destructor stub
}

SkyIterator*
SkyFactory::getStars(float magnitude) {
	AppLog("Getting stars with magnitude < %f", magnitude);
	SkyDbIterator* iterator = new SkyDbIterator(magnitude);
	return iterator;
}

SkyIterator*
SkyFactory::getStars() {
	return getStars(5);
}

SkyObject*
SkyFactory::getStar(String* starName, String* constName) {
	String databaseName(L"/Home/stars.db");
	Database* database = new Database();
	result r = database->Construct(databaseName, false);

	String query;
	query.Append("select * from stars where greek like '");
	query.Append(starName->GetPointer());
	query.Append("' and constellation like '");
	query.Append(constName->GetPointer());
	query.Append("'");
	AppLog("Query is %S", query.GetPointer());

	DbStatement* getStarStat = database->CreateStatementN(query);
	DbEnumerator* dataSet = database->ExecuteStatementN(*getStarStat);

	r = dataSet -> MoveNext();
	if (r != E_SUCCESS) {
		return null;
	}

	SkyObject* nextObject = new SkyObject();
	String strHolder;
	double floatHolder;
	int intHolder;
	dataSet->GetStringAt(0, strHolder);
	nextObject->setName(strHolder);
	dataSet->GetStringAt(1, strHolder);
	nextObject->setConstellation(strHolder);
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




