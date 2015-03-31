/*
 * ConstellationDbIterator.cpp
 *
 *  Created on: 11.03.2013
 *      Author: ddreval
 */

#include "ConstellationDbIterator.h"

using namespace Osp::Base;
using namespace Osp::Io;
using namespace Osp::Base::Collection;

ConstellationDbIterator::ConstellationDbIterator(String* name) {
	result r = E_SUCCESS;
	nextObject = new SkyObject();
	AppLog("Building DB iterator");
	String databaseName(L"/Home/stars.db");
	database = new Database();
	r = database->Construct(databaseName, false);
	AppLogDebug("DB creation result is %S", GetErrorMessage(r));

	String borderQuery(L"select * from boundaries where constellation like '%");
	borderQuery.Append(*name);
	borderQuery.Append("%'");

//	mchar* borderQueryTemplate = L"select * from boundaries where constellation not like '%%S%'";


//	String borderQuery(L"select * from boundaries where constellation not like '%%S%'");
//	borderQuery.Format(3, L"FORMAT %d %ls", value, testStr);

	AppLog("Running query %S", borderQuery.GetPointer());
	DbStatement* counterStat = database->CreateStatementN(borderQuery);
	AppLog("1");
	dataSet = database->ExecuteStatementN(*counterStat);
	AppLog("2");
}

ConstellationDbIterator::~ConstellationDbIterator() {
	delete database;
	delete dataSet;
}

bool
ConstellationDbIterator::HasNext() {
	AppLog("HasNext");
	result r = E_SUCCESS;
	r = dataSet->MoveNext();
	AppLog("Move next %S", GetErrorMessage(r));
	return !IsFailed(r);
}

SkyObject*
ConstellationDbIterator::GetNext() {
	AppLog("GetNext");
	String strHolder;
	double floatHolder;
	int intHolder;
	dataSet->GetStringAt(0, strHolder);
	AppLog("GetNext 0");
	nextObject->setConstellation(strHolder);
	dataSet->GetDoubleAt(1, floatHolder);
	AppLog("GetNext 1");
	nextObject->setRAH(floatHolder);
	dataSet->GetDoubleAt(2, floatHolder);
	AppLog("GetNext 2");
	nextObject->setDED(floatHolder);
	dataSet->GetIntAt(3, intHolder);
	AppLog("GetNext 3");
	nextObject->setSign(intHolder == 1);
	return nextObject;

	//    statement.executeUpdate("create table boundaries (" +
	//            "constellation string, " +
	//            "ra float, " +
	//            "dec float, " +
	//            "northern int)");


}

Osp::Base::Collection::IListT<SkyObject*>*
ConstellationDbIterator::GetVertexes (void) {

	IListT<SkyObject*>* vertexes;
	vertexes = new LinkedListT<SkyObject*>();

	String strHolder;
	double floatHolder;
	int intHolder;
	while (dataSet->MoveNext() == E_SUCCESS) {
		SkyObject* vertex = new SkyObject();
		dataSet->GetStringAt(0, strHolder);
		vertex->setConstellation(strHolder);
		dataSet->GetDoubleAt(1, floatHolder);
		vertex->setRAH(floatHolder);
		dataSet->GetDoubleAt(2, floatHolder);
		vertex->setDED(floatHolder);
		dataSet->GetIntAt(3, intHolder);
		vertex->setSign(intHolder == 1);
		vertexes -> Add(vertex);
	}

	return vertexes;

}

