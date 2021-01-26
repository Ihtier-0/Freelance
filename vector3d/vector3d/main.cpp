#include <iostream>

using namespace std;

class vector3d
{
public:
	vector3d() :m_x(0), m_y(0), m_z(0) {}
	vector3d(const double& a_x, const double& a_y, const double& a_z) : m_x(a_x), m_y(a_y), m_z(a_z) {}
	vector3d(const vector3d& v) : m_x(v.m_x), m_y(v.m_y), m_z(v.m_z) {}

	double length()
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	double x() const
	{
		return m_x;
	}

	double y() const
	{
		return m_y;
	}

	double z() const
	{
		return m_z;
	}

private:
	double m_x, m_y, m_z;

	friend vector3d operator+(const vector3d& v1, const vector3d& v2)
	{
		return vector3d(v1.m_x + v2.m_x, v1.m_y + v2.m_y, v1.m_z + v2.m_z);
	}
	friend vector3d operator-(const vector3d& v1, const vector3d& v2)
	{
		return vector3d(v1.m_x - v2.m_x, v1.m_y - v2.m_y, v1.m_z - v2.m_z);
	}
	friend ostream& operator<< (ostream& out, const vector3d& v1)
	{
		out << v1.m_x << ' ' << v1.m_y << ' ' << v1.m_z;

		return out;
	}
};

double scalarProduct(const vector3d& v1, const vector3d& v2)
{
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

int main()
{
	vector3d v1(1, 1, 1), v2(1, -2, 3);

	cout << "v1 " << v1 << "\nv2 " << v2 << "\nv1 + v2 " << v1 + v2 << "\nv1 - v2 " << v1 - v2 << '\n';
	cout << "v1.length " << v1.length() << "\nv2.length " << v2.length() << '\n';


}