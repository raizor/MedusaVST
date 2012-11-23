#pragma once
#include <vector>

typedef double GCoord;

struct GPoint
{
	GPoint();
	GPoint(const GCoord x, const GCoord y);
	GPoint(const GPoint& other);

	GPoint Plus(const GPoint& other);
	GPoint Plus(const GCoord otherX, const GCoord otherY);
	GPoint Minus(const GPoint& other);
	GPoint Minus(const GCoord otherX, const GCoord otherY);

	void Offset(const GPoint& other);
	void Offset(const GCoord otherX, const GCoord otherY);

	GCoord DistanceTo(const GPoint& other);
	GCoord DistanceTo(const GCoord otherX, const GCoord otherY);

	GCoord x, y;
};

struct GRect
{
	GRect();
	GRect(const GRect& other);
	GRect(const GCoord left, const GCoord top, const GCoord right, const GCoord bottom);
	GRect(const GPoint &topLeft, const GPoint &bottomRight);
	GRect(const GPoint &topLeft, const GCoord width, const GCoord height);

	void Copy(const GRect& other);
	bool IsEqual(const GRect& other);

	GCoord GetWidth() const;
	GCoord GetHeight() const;
	void SetWidth(const GCoord width);
	void SetHeight(const GCoord height);

	GRect CloneWithOffset(const GCoord dx, const GCoord dy);
	GRect CloneWithOffset(const GPoint& offset);
	GRect CloneWithInset(const GCoord inset);
	GRect CloneWithPixelSnap() const;
	void Inset(const GCoord inset);
	void Offset(const GCoord dx, const GCoord dy);
	void MoveTo(const GCoord newX, const GCoord newY);
	void MoveTo(const GPoint& point);
	void SetSize(const GCoord x, const GCoord y);
	void SetSize(const GPoint& size);

	GPoint GetTopLeft();
	GPoint GetTopRight();
	GPoint GetBottomLeft();
	GPoint GetBottomRight();

	bool IsPointInside(const GPoint& point);
	bool IsPointInside(const GCoord x, const GCoord y);

	bool Contains(const GRect& rect) const;
	bool OverlapsWith(const GRect& rect) const;

	void ExpandToCover(const GRect& otherRect);

	GRect IntersectionWith(const GRect& otherRect);

	GCoord left, top, right, bottom;
};

struct GColor
{
	GColor();
	GColor(const GColor &other);
	GColor(double r, double g, double b);
	GColor(double r, double g, double b, double a);

	GColor BlendedWith(const GColor& other, double frac);

	double r, g, b, a;
};

class GGradient
{
public:
	GGradient();
	void InsertColor(const double pos, const GColor& color);
	GColor GetColorAt(const double pos);

private:
	std::vector<double> positions;
	std::vector<GColor> colors;
};

class GSpriteCollection;

class GSprite
{
public:
	GSprite();
	GSprite(const GCoord x, const GCoord y, const GCoord width, const GCoord height, const int spriteId);
	GCoord posX, posY, width, height;
	GSpriteCollection* spriteCollection;
	int spriteId;
};

class GSpriteCollection
{
public:
	std::vector<GSprite*> sprites;
	int imageWidth, imageHeight;
	GCoord pixelSizeX, pixelSizeY;
	GSpriteCollection();
	void GSpriteCollection::AddSprite(GSprite* sprite);
	GSprite* GetSprite(int spriteId);
};

