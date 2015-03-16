/*
 * MainContent.h
 *
 *  Created on: Mar 13, 2015
 *      Author: vostanin
 */

#ifndef MAINCONTENT_H_
#define MAINCONTENT_H_

#include <Evas.h>

class MainContent
{
public:
	MainContent( Evas_Object *parent );
	~MainContent();

	Evas_Object * getLayout();
private:
	void createLayout();
	Evas_Object * m_Parent;
	Evas_Object * m_MainLayout;
};

#endif /* MAINCONTENT_H_ */
