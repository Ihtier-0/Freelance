#include "utils.h"

#include "body.h"
#include "bracket.h"
#include "cuff.h"
#include "flange.h"
#include "nut.h"
#include "panel.h"
#include "part.h"
#include "screw.h"
#include "sleeve.h"
#include "stock.h"
#include "stock.h"

part partTypeToPart(const partType& type)
{
	part result;

	switch (type)
	{
	case partType::body:
	{
		result = body();
		break;
	}
	case partType::bracket:
	{
		result = bracket();
		break;
	}
	case partType::cuff:
	{
		result = cuff();
		break;
	}
	case partType::flange:
	{
		result = flange();
		break;
	}
	case partType::nut:
	{
		result = nut();
		break;
	}
	case partType::panel:
	{
		result = panel();
		break;
	}
	case partType::screw:
	{
		result = screw();
		break;
	}
	case partType::sleeve:
	{
		result = sleeve();
		break;
	}
	case partType::stock:
	{
		result = stock();
		break;
	}
	}

	return result;
}
