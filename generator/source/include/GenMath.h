/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//or by playing it in its actual state.												//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef _GENMATH_H_
#define _GENMATH_H_

#include <vector>
#include <math.h>

static const float PI = 3.1415926535f;

using namespace std;

//---- Point -----
struct GPoint{
	int x, y;
};

bool samePoint (GPoint p1, GPoint p2);

//---- Point List -----
typedef vector<GPoint> GPointList;

bool containsPoint(GPoint p, GPointList pts);

//---- Line -----
struct GLine{
	GPoint a;
	GPoint b;
};

bool sameLine (GLine l1, GLine l2);
bool containsLine(GLine l, vector<GLine> vl);
float getDistance(GLine l);

//--- GPolygon ----
class GPolygon{
private:
	vector<GLine> p;

public:
	GPolygon();
	~GPolygon();
	void addLine (GLine l);
	bool removeLine (GLine l);
	bool contains (GLine l);
	bool equals (GPolygon p);
	inline void clearLines() {p.clear();};
	inline vector<GLine> getLines() {return p;};
};

//--- GPolygon List ----
typedef vector<GPolygon> GPolygonList;

// Get ponts of mapTileMatrix space -- Bresenham's Algorithm
vector<GPoint> getMatrixLine(float x1, float y1, float x2, float y2);

// Generates n points with a given spacing inside height/width bounds
GPointList genPoints(int n, int height, int width, int numZones);

// pasa de vector de puntos a float[], c = 0 son X, c = 1 las Y
float* getPoints(GPointList pl, int c);

//--- From here on: Vector2D ----
class Vector2D{
public:
	float x;
	float y;

	inline Vector2D(){x = 0.0f; y = 0.0f;};
	inline Vector2D(float valX, float valY){x = valX; y = valY;};

	void setAngle(float value);
	float getAngle();
	void setLength(float value);
	inline float getLength(){return sqrt((x*x) + (y*y));};
	void truncate(float value);
	Vector2D getNormalized();
	inline void add(Vector2D vect){x += vect.x; y += vect.y;};
	inline void subtract(Vector2D vect){x -= vect.x; y -= vect.y;};
	inline void multiply(float value){x *= value; y *= value;};
	float dotProduct(Vector2D vect);
	Vector2D getPerpendicular();
	int sign(Vector2D vect);

	//Basic arithmetic (+, -, *, /)
	inline Vector2D operator +(const Vector2D& v) const
    {
        return (Vector2D(x + v.x, y + v.y));
    }
        
    inline Vector2D operator -(const Vector2D& v) const
    {
        return (Vector2D(x - v.x, y - v.y));
    }
        
    inline Vector2D operator *(float t) const
    {
        return (Vector2D(x * t, y * t));
    }
        
    inline Vector2D operator /(float t) const
    {
        float f = 1.0F / t;
        return (Vector2D(x * f, y * f));
    }
        
    inline float operator *(const Vector2D& v) const
    {
        return (x * v.x + y * v.y);
    }

	inline Vector2D& operator +=(const Vector2D& v)
    {
        x += v.x;
        y += v.y;
        return (*this);
    }
        
    inline Vector2D& operator -=(const Vector2D& v)
    {
        x -= v.x;
        y -= v.y;
        return (*this);
    }
        
    inline Vector2D& operator *=(float t)
    {
        x *= t;
        y *= t;
        return (*this);
    }
        
    inline Vector2D& operator /=(float t)
    {
        float f = 1.0F / t;
        x *= f;
        y *= f;
        return (*this);
    }

	bool operator ==(const Vector2D& v) const
    {
        return ((x == v.x) && (y == v.y));
    }

	bool operator !=(const Vector2D& v) const
    {
        return ((x != v.x) || (y != v.y));
    }

	float distance(Vector2D vector2);
};

#endif