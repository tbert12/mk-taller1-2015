/*
 * Frame.h
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#ifndef SRC_VIEW_FRAME_H_
#define SRC_VIEW_FRAME_H_

class Frame{
	public:
		int Alto;
		int Ancho;
		int X;
		int Y;
		Frame(int x,int y,int alto,int ancho);
		~Frame();

		//Accede a Frame.x, Frame.y, Frame.Alto, Frame.Ancho
};

#endif /* SRC_VIEW_FRAME_H_ */
