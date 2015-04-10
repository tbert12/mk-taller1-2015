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
		float Alto;
		float Ancho;
		float X;
		float Y;
		Frame(float x,float y,float alto,float ancho);
		~Frame();

		//Accede a Frame.x, Frame.y, Frame.Alto, Frame.Ancho
};

#endif /* SRC_VIEW_FRAME_H_ */
