/*
 * MouseCoordinatesHolder.h
 *
 *  Created on: 17 апр. 2015
 *      Author: vadim
 */

#ifndef MANAGERS_MOUSECOORDINATESHOLDER_H_
#define MANAGERS_MOUSECOORDINATESHOLDER_H_

class MouseCoordinatesHolder
{
public:
	MouseCoordinatesHolder();
	virtual ~MouseCoordinatesHolder();

	void setX( int x );
	void setY( int y );

	int getX() const;
	int getY() const;

	static MouseCoordinatesHolder & getInstance();

private:

	int m_X;
	int m_Y;

};

#endif /* MANAGERS_MOUSECOORDINATESHOLDER_H_ */
