#include "bird.h"

bird::bird(const std::string& identifier, const bool& sleep)
	:m_identifier(identifier), m_sleep(sleep) {}

bird::bird(const bird& Bird)
	: m_identifier(Bird.m_identifier), m_sleep(Bird.m_sleep) {}

bird& bird::operator=(const bird& Bird)
{
	m_identifier = Bird.m_identifier;
	m_sleep = Bird.m_sleep;

	return *this;
}

std::string bird::sing() const
{
	return std::string();
}

std::ostream& operator<<(std::ostream& out, const bird& Bird)
{
	out << Bird.m_identifier << ' ' << (Bird.m_sleep ? "sleep" : "awake") << ' ' << Bird.sing();

	return out;
}

std::istream& operator>>(std::istream& is, bird& Bird)
{
	std::string sleep;

	is >> Bird.m_identifier >> sleep;

	Bird.m_sleep = sleep == "sleep";

	// чтобы пропустить sing потому что он нигде не хранится
	is >> sleep;

	return is;
}

bool operator==(const bird& bird1, const bird& bird2)
{
	return bird1.m_sleep == bird2.m_sleep &&
		bird1.m_identifier == bird2.m_identifier &&
		bird1.sing() == bird2.sing();
}

