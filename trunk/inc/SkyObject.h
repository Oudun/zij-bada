/*
 * SkyObject.h
 *
 *  Created on: 17.02.2012
 *      Author: ddreval
 */

#ifndef SKYOBJECT_H_
#define SKYOBJECT_H_

class SkyObject
{

public:
	SkyObject(void);
	void setRA(String raH, String raM, String raS);

private:
	String name;
	String draperName;
	float RAH;
	float RAM;
	float RAS;
//    String name = str.substring(5, 14);
//    String draperName = str.substring(25, 31);
//    String rahStr = str.substring(75,77);
//    String ramStr = str.substring(77,79);
//    String rasStr = str.substring(79,83);
//    String dedStr = str.substring(84,86);
//    String demStr = str.substring(86,88);
//    String desStr = str.substring(88,90);
//    String sign = str.substring(83,84);

}

#endif /* SKYOBJECT_H_ */
