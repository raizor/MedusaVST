//#include "global.h"
#include "types.h"
#include <cmath>
#include <cassert>

GPoint::GPoint() :
	x(0),
	y(0)
{
}

GPoint::GPoint(const GPoint &other) :
	x(other.x),
	y(other.y)
{
}

GPoint::GPoint(const GCoord x, const GCoord y) :
	x(x),
	y(y)
{
}

GPoint GPoint::Plus(const GPoint& other)
{
	return GPoint(x + other.x, y + other.y);
}

GPoint GPoint::Plus(const GCoord otherX, const GCoord otherY)
{
	return GPoint(x + otherX, y + otherY);
}

GPoint GPoint::Minus(const GPoint& other)
{
	return GPoint(x - other.x, y - other.y);
}

GPoint GPoint::Minus(const GCoord otherX, const GCoord otherY)
{
	return GPoint(x - otherX, y - otherY);
}

void GPoint::Offset(const GPoint& other)
{
	x += other.x;
	y += other.y;
}

void GPoint::Offset(const GCoord otherX, const GCoord otherY)
{
	x += otherX;
	y += otherY;
}

GCoord GPoint::DistanceTo(const GPoint& other)
{
	return DistanceTo(other.x, other.y);
}

GCoord GPoint::DistanceTo(const GCoord otherX, const GCoord otherY)
{
	GCoord dx, dy;

	dx = x-otherX;
	dy = y-otherY;

	return sqrt(dx*dx + dy*dy);
}

GRect::GRect() :
	left(0),
	top(0),
	right(0),
	bottom(0)
{
}

GRect::GRect(const GRect& other) :
	left(other.left),
	top(other.top),
	right(other.right),
	bottom(other.bottom)
{
}

GRect::GRect(const GCoord left, const GCoord top, const GCoord right, const GCoord bottom) :
	left(left),
	top(top),
	right(right),
	bottom(bottom)
{
}

GRect::GRect(const GPoint &topLeft, const GPoint &bottomRight) :
	left(topLeft.x),
	top(topLeft.y),
	right(bottomRight.x),
	bottom(bottomRight.y)
{
}

GRect::GRect(const GPoint &topLeft, const GCoord width, const GCoord height) :
	left(topLeft.x),
	top(topLeft.y),
	right(topLeft.x + width),
	bottom(topLeft.y + height)
{
}

void GRect::Copy(const GRect& other)
{
	left = other.left;
	top = other.top;
	right = other.right;
	bottom = other.bottom;
}

bool GRect::IsEqual(const GRect& other)
{
	// Pointer comparison
	if (this==&other)
		return true;

	// Value comparison
	if (left==other.left && top==other.top && right==other.right && bottom==other.bottom)
		return true;

	return false;
}

GCoord GRect::GetWidth() const
{
	return right - left;
}

GCoord GRect::GetHeight() const
{
	return bottom - top;
}

void GRect::SetWidth(const GCoord width)
{
	right = left + width;
}

void GRect::SetHeight(const GCoord height)
{
	bottom = top + height;
}

GRect GRect::CloneWithOffset(const GCoord dx, const GCoord dy)
{
	GRect result(*this);
	result.Offset(dx, dy);
	return result;
}

GRect GRect::CloneWithOffset(const GPoint& offset)
{
	return CloneWithOffset(offset.x, offset.y);
}

GRect GRect::CloneWithPixelSnap() const
{
	return GRect(floor(left), floor(top), floor(right), floor(bottom));
}

GRect GRect::CloneWithInset(const GCoord inset)
{
	return GRect(left+inset, top+inset, right-inset, bottom-inset);
}

void GRect::Offset(const GCoord dx, const GCoord dy)
{
	left += dx;
	right += dx;
	top += dy;
	bottom += dy;
}

void GRect::Inset(const GCoord inset)
{
	left += inset;
	top += inset;
	right -= inset;
	bottom -= inset;
}

void GRect::MoveTo(const GCoord newX, const GCoord newY)
{
	GCoord dx = newX - left;
	GCoord dy = newY - top;

	Offset(dx, dy);
}

void GRect::MoveTo(const GPoint& point)
{
	GCoord dx = point.x - left;
	GCoord dy = point.y - top;

	Offset(dx, dy);
}

void GRect::SetSize(const GCoord width, const GCoord height)
{
	right = left + width;
	bottom = top + height;
}

void GRect::SetSize(const GPoint& size)
{
	SetSize(size.x, size.y);
}

GPoint GRect::GetTopLeft()
{
	return GPoint(left, top);
}

GPoint GRect::GetBottomRight()
{
	return GPoint(right, bottom);
}

GPoint GRect::GetTopRight()
{
	return GPoint(right, top);
}

GPoint GRect::GetBottomLeft()
{
	return GPoint(left, bottom);
}

bool GRect::IsPointInside(const GPoint& point)
{
	return IsPointInside(point.x, point.y);
}

bool GRect::IsPointInside(const GCoord x, const GCoord y)
{
	return x >= left && x<right && y>=top && y<bottom;
}

bool GRect::Contains(const GRect& rect) const
{
	return
		rect.left >= left &&
		rect.right <= right &&
		rect.top >= top &&
		rect.bottom <= bottom;
}

bool GRect::OverlapsWith(const GRect& rect) const
{
	// Try to find seperating axis
	bool foundSeperatingAxis =
		rect.left >= right && rect.right > right ||
		rect.left < left && rect.right <= left ||
		rect.top < top && rect.bottom <= top ||
		rect.top >= bottom && rect.bottom > bottom;

	return (foundSeperatingAxis==false);
}

void GRect::ExpandToCover(const GRect& otherRect)
{
	// ASSUMPTIONS: Origo in top left corner
	if (otherRect.left < left)
		left = otherRect.left;
	if (otherRect.top < top)
		top = otherRect.top;
	if (otherRect.right > right)
		right = otherRect.right;
	if (otherRect.bottom > bottom)
		bottom = otherRect.bottom;
}

GRect GRect::IntersectionWith(const GRect& otherRect)
{
	// ASSUMPTIONS: Origo in top left corner
	// ASSUMPTIONS: Rectangles overlap

	GRect intersection(*this);

	if (otherRect.left > left)
		intersection.left = otherRect.left;
	if (otherRect.top > top)
		intersection.top = otherRect.top;
	if (otherRect.right < right)
		intersection.right = otherRect.right;
	if (otherRect.bottom < bottom)
		intersection.bottom = otherRect.bottom;

	return intersection;
}

GColor::GColor() :
	r(0),
	g(0),
	b(0),
	a(0)
{
}

GColor::GColor(const GColor &other) :
	r(other.r),
	g(other.g),
	b(other.b),
	a(other.a)
{
}

GColor::GColor(double r, double g, double b) :
	r(r),
	g(g),
	b(b),
	a(255.0)
{
}

GColor::GColor(double r, double g, double b, double a) :
	r(r),
	g(g),
	b(b),
	a(a)
{
}

GColor GColor::BlendedWith(const GColor& other, double frac)
{
	return GColor(r + (other.r-r)*frac, g + (other.g-g)*frac, b + (other.b-b)*frac, a + (other.a-a)*frac);
}

GGradient::GGradient() :
	positions(),
	colors()
{
}

void GGradient::InsertColor(const double pos, const GColor& color)
{
	positions.push_back(pos);
	colors.push_back(color);
}

GColor GGradient::GetColorAt(const double pos)
{
	assert(positions.size()!=0);

	if (pos < (positions.front() + 0.0001))
		return colors.front();

	for (unsigned int i=0; i<colors.size()-1; i++)
	{
		if (pos < positions[i+1])
		{
			double frac = (pos - positions[i]) / (positions[i+1] - positions[i]);
			return colors[i].BlendedWith(colors[i+1], frac);
		}
	}

	return colors.back();
}

// sprite

GSprite::GSprite()
{

}

GSprite::GSprite(const GCoord x, const GCoord y, const GCoord width, const GCoord height, const int spriteId)
{
	this->posX = x;
	this->posY = y;
	this->height = height;
	this->width = width;
	this->spriteId = spriteId;
}

// sprite collection

GSpriteCollection::GSpriteCollection()
{

}

void GSpriteCollection::AddSprite(GSprite* sprite)
{
	sprite->spriteCollection = this;
	sprites.push_back(sprite);	
}

GSprite* GSpriteCollection::GetSprite(int spriteId)
{
	return sprites[spriteId];
}
