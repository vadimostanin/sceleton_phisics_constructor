/*
 * GraphicLinkDynamic.h
 *
 *  Created on: Apr 3, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICLINKDYNAMIC_H_
#define GRAPHICLINKDYNAMIC_H_

#include "GraphicLink.h"
#include "GeometryLinkDynamic.h"

class GraphicLinkDynamic: public GraphicLink
{
public:
	GraphicLinkDynamic( GeometryLinkDynamic * dynamicObject, Evas_Object * glview );
	virtual ~GraphicLinkDynamic();

	void draw();

private:

	GeometryLinkDynamic * m_DynamicLink;
};

#endif /* GRAPHICLINKDYNAMIC_H_ */
