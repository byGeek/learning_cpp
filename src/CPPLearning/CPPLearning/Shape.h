#ifndef _SHAPE_H_
#define _SHAPE_H_

class Shape
{
public:
	typedef enum _Shape_t
	{
		CIRCLE = 0,
		REGTANGLE
	} Shape_t;

	virtual double area() const = 0;
	virtual Shape_t get_shape() const = 0;

};

#define PI (3.1415926)

class SCircle : public Shape
{
public:
	SCircle() = default;
	SCircle(double r) :radius(r){}

	double area() const override { return 2 * PI*radius; }
	Shape_t get_shape() const{ return CIRCLE; }

private:
	double radius;
};

class SRegtangel : public Shape
{
public:
	SRegtangel() = default;
	SRegtangel(double width, double height) :
		m_width(width), m_height(height){}

	double area() const override{ return m_width*m_height; }
	Shape_t get_shape() const { return REGTANGLE; }
private:
	double m_width;
	double m_height;
	
};
#endif // !_SHAPE_H_

