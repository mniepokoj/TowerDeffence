#include "VertexTriangle.h"

constexpr size_t lbPkt = 3;

float wysokosc(float promien)
{
	return promien * sqrt3 / 2;
}

sf::Vector2f gora(float rozmiar)
{
	return sf::Vector2f(rozmiar / 2, 0);
}

sf::Vector2f lDol(float rozmiar)
{
	return sf::Vector2f(0, wysokosc(rozmiar));
}

sf::Vector2f pDol(float rozmiar)
{
	return sf::Vector2f(rozmiar, wysokosc(rozmiar));
}

VertexTriangle::VertexTriangle()
{ 
	; 
}
VertexTriangle::VertexTriangle(float size, const sf::Vector2f& Position, float outlineThickness, const sf::Color& fillColor, const sf::Color& outlineColor)
{
	Create(size, Position, outlineThickness, fillColor, outlineColor);
}
void VertexTriangle::Create(float size, const sf::Vector2f& Position, float outlineThickness, const sf::Color& fillColor, const sf::Color& outlineColor)
{
	position = Position;
	angle = 0;
	data.setPrimitiveType(sf::Triangles);

	float a = outlineThickness + size;
	outOrigin = sf::Vector2f(a / 2, wysokosc(a) * 2 / 3);
	vertexs[0] = gora(a) - outOrigin;
	vertexs[1] = lDol(a) - outOrigin;
	vertexs[2] = pDol(a) - outOrigin;

	inOrigin = sf::Vector2f(size / 2, wysokosc(size) * 2 / 3);
	vertexs[3] = gora(size) - inOrigin;
	vertexs[4] = lDol(size) - inOrigin;
	vertexs[5] = pDol(size) - inOrigin;

	for (size_t i = 0; i < lbPkt; i++)
	{
		data.append(sf::Vertex(vertexs[i] + position, outlineColor));
	}
	for (size_t i = lbPkt; i < lbPkt * 2; i++)
	{
		data.append(sf::Vertex(vertexs[i] + position, fillColor));
	}
}



void VertexTriangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(data);
}
void VertexTriangle::rotate(float Angle)
{
	angle += Angle;
	while (angle > 360) angle -= 360;
	float radian = to_rad(angle), x, y;
	float sinus = Matematyka::sin(radian), cosinus = Matematyka::cos(radian);
	for (int i = 0; i < lbPkt; i++)
	{
		x = vertexs[i].x * cosinus - vertexs[i].y * sinus;
		y = vertexs[i].x * sinus + vertexs[i].y * cosinus;
		data[i].position = sf::Vector2f(x, y) + position;
	}

	for (int i = lbPkt; i < lbPkt * 2; i++)
	{
		x = vertexs[i].x * cosinus - vertexs[i].y * sinus;
		y = vertexs[i].x * sinus + vertexs[i].y * cosinus;
		data[i].position = sf::Vector2f(x, y) + position;
	}
}
void VertexTriangle::setFillColor(const Color &color)
{
	for (int i = lbPkt; i < lbPkt * 2; i++)
	{
		data[i].color = color;
	}
}
void VertexTriangle::setOutlineColor(const Color &color)
{
	for (int i = 0; i < lbPkt; i++)
	{
		data[i].color = color;
	}
}
void VertexTriangle::setOutlineThickness(float thickness)
{
	float a = vertexs[5].x * 2 + thickness;
	outOrigin = sf::Vector2f(a / 2, wysokosc(a) * 2 / 3);
	vertexs[0] = gora(a) - outOrigin;
	vertexs[1] = lDol(a) - outOrigin;
	vertexs[2] = pDol(a) - outOrigin;

	float radian = to_rad(angle), x, y;
	float sinus = Matematyka::sin(radian), cosinus = Matematyka::cos(radian);
	for (int i = lbPkt; i < lbPkt * 2; i++)
	{
		x = vertexs[i].x * cosinus - vertexs[i].y * sinus;
		y = vertexs[i].x * sinus + vertexs[i].y * cosinus;
		data[i].position = sf::Vector2f(x, y) + position;
	}

}
void VertexTriangle::setSize(float size)
{
	float a = getOutlineThickness() + size;
	outOrigin = sf::Vector2f(a / 2, wysokosc(a) * 2 / 3);
	vertexs[0] = gora(a) - outOrigin;
	vertexs[1] = lDol(a) - outOrigin;
	vertexs[2] = pDol(a) - outOrigin;

	inOrigin = sf::Vector2f(size / 2, wysokosc(size) * 2 / 3);
	vertexs[3] = gora(size) - inOrigin;
	vertexs[4] = lDol(size) - inOrigin;
	vertexs[5] = pDol(size) - inOrigin;

	rotate(0);
}
const Color& VertexTriangle::getFillColor() const
{
	return data[lbPkt].color;
}
const Color & VertexTriangle::getOutlineColor() const
{
	return data[0].color;
}
float VertexTriangle::getOutlineThickness() const
{
	return -(vertexs[0].y - vertexs[lbPkt].y) * sqrt3;
}
float VertexTriangle::getSize() const
{
	return vertexs[5].x * 2;
}
std::size_t VertexTriangle::getPointCount() const
{
	return lbPkt;
}
const Vector2f& VertexTriangle::VertexTriangle::getPoint(std::size_t index) const
{	
#ifdef _DEBUG
	if(index >= lbPkt * 2) std::cout << "Error File: " << __FILE__ << " Line: " << __LINE__ << " Out of vertexArray range " << std::endl;
#endif // _DEBUG
	return data[index].position;
}
FloatRect VertexTriangle::getGlobalBounds() const
{
	return data.getBounds();
}
void VertexTriangle::setPosition(float x, float y)
{
	for (int i = 0; i < lbPkt * 2; i++)
	{
		data[i].position -= position;
		data[i].position.x += x;
		data[i].position.y += y;
	}
	position.x = x;
	position.y = y;
}
void VertexTriangle::setPosition(const Vector2f &Position)
{
	for (int i = 0; i < lbPkt * 2; i++)
	{
		data[i].position -= position;
		data[i].position += Position;
	}
	position = Position;
}
void VertexTriangle::setRotation(float Angle)
{
	angle = Angle;
	while (angle > 360) angle -= 360;
	float radian = to_rad(angle), x, y;
	float sinus = Matematyka::sin(radian), cosinus = Matematyka::cos(radian);
	for (int i = 0; i < lbPkt; i++)
	{
		x = vertexs[i].x * cosinus - vertexs[i].y * sinus;
		y = vertexs[i].x * sinus + vertexs[i].y * cosinus;
		data[i].position = sf::Vector2f(x, y) + position;
	}

	for (int i = lbPkt; i < lbPkt * 2; i++)
	{
		x = vertexs[i].x * cosinus - vertexs[i].y * sinus;
		y = vertexs[i].x * sinus + vertexs[i].y * cosinus;
		data[i].position = sf::Vector2f(x, y) + position;
	}
}
const Vector2f& VertexTriangle::getPosition() const
{
	return position;
}
float VertexTriangle::getRotation() const
{
	return angle;
}
const Vector2f& VertexTriangle::getOrigin() const
{
	return outOrigin;
}
void VertexTriangle::move(float offsetX, float offsetY)
{
	position.x += offsetX;
	position.y += offsetY;
	for (int i = 0; i < lbPkt * 2; i++)
	{
		data[i].position.x += offsetX;
		data[i].position.y += offsetY;
	}
}
void VertexTriangle::move(const Vector2f &offset)
{
	position += offset;
	for (int i = 0; i < lbPkt * 2; i++)
	{
		data[i].position += offset;
	}
}

VertexTriangle::~VertexTriangle()
{
}
