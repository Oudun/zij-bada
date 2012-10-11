/*
 * SkyFileIterator.cpp
 *
 *  Created on: 02.05.2012
 *      Author: ddreval
 */

#include "SkyFileIterator.h"

SkyFileIterator::SkyFileIterator(Osp::Base::String &path) {
	AppLog(">>SkyIterator");
	nextObject = new SkyObject();
	r = file.Construct(path, L"r+");
	Osp::Io::FileAttributes fileAttributes;
	file.GetAttributes(path, fileAttributes);
	fileSize = fileAttributes.GetFileSize();
	AppLog("<<SkyIterator");
}

SkyFileIterator::SkyFileIterator() {
	// TODO Auto-generated constructor stub

}

SkyFileIterator::~SkyFileIterator() {
	// TODO Auto-generated destructor stub
}

bool
SkyFileIterator::hasNext() {
//	AppLog("%d < %d", file.Tell(), fileSize);
	return file.Tell() < fileSize;
}

SkyObject*
SkyFileIterator::getNext() {
	counter++;
	AppLog(">>SkyFileIterator.getNext #%d", counter);
	//AppLog("Getting next star %d cursor position is %d", counter, file.Tell());
	line.Clear();
	while (line.GetLength()<108) {
		//AppLog("Getting next star1");
		do {
			file.Read(buffer, 1);
			line.Append(buffer[0]);
		} while (buffer[0]!='\n'&&(file.Tell() < fileSize));
//		AppLog("Line is: %s position is %d", line.GetPointer(), file.Tell());
	}
	AppLog("Getting next star2%d", counter);
	line.SubString(5, 9, substr1);
	substr1.Trim();
	nextObject->setName(substr1);
	line.SubString(25, 6, substr1);
	substr1.Trim();
	nextObject->setDraperName(substr1);
	line.SubString(102, 5, substr1);
	substr1.Trim();
	nextObject->setMagnitude(substr1);
	line.SubString(83, 1, substr1);
	nextObject->setSign(substr1.Equals("+", false));
	nextObject->setDraperName(substr1);
	line.SubString(75, 2, substr1);
	line.SubString(77, 2, substr2);
	line.SubString(79, 4, substr3);
	nextObject->setRA(substr1, substr2, substr3);
	line.SubString(84, 2, substr1 );
	line.SubString(86, 2, substr2 );
	line.SubString(88, 2, substr3 );
	nextObject->setDE(substr1, substr2, substr3);
	AppLog("<<SkyFileIterator.getNext");
	return nextObject;
}
