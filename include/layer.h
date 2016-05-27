/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
#include <sccsid.h>
HVERSION(layer,@(#)layer.h	2.3);
*/
#ifndef LAYER_H
#define	LAYER_H	LAYER_H
typedef struct Obscured{
	Rectangle rect;	/* obscured rectangle, screen coords */
	Bitmap *bmap;	/* where the obscured data resides */
	struct Layer *lobs;	/* layer currently in rect on screen */
	struct Obscured *next;	/* chaining */
	struct Obscured *prev;
}Obscured;

typedef struct Layer{
	/* The first part looks like (is) a Bitmap */
	Word *base;
	unsigned width;
	Rectangle rect;	/* bounding box of layer */
	struct Obscured *obs;	/* linked list of obscured rectangles */
	struct Layer *front;	/* adjacent layer in front */
	struct Layer *back;	/* adjacent layer behind */
}Layer;

#endif
