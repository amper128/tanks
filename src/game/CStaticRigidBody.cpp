#include <game/CStaticRigidBody.h>

CStaticRigidBody::CStaticRigidBody(CVector pos, float angle, bool solid, bool flat)
{
	this->_pos = pos;
	this->_angle = angle;
	this->_solid = solid;
	this->_flat = flat;

	this->bounds = NULL;
}

void CStaticRigidBody::set_poly(CPoly* poly)
{
	this->bounds = poly;
	this->bounds->move(this->_pos);
	this->bounds->rotate(this->_angle);
}

bool CStaticRigidBody::collide(const CStaticRigidBody& coll)
{
	if (this->bounds && coll.bounds)
	{
		for (uint8_t i = 0; i < this->bounds->vertex_count; i++)
		{
			for (uint8_t j = 0; j < coll.bounds->vertex_count; j++)
			{
				if (IsLinesCross(this->bounds->vertex_arr_t[i],
					this->bounds->vertex_arr_t[((i+1) % this->bounds->vertex_count)],
					coll.bounds->vertex_arr_t[j],
					coll.bounds->vertex_arr_t[((j+1) % coll.bounds->vertex_count)])) {
						return true;
				}
			}
		}
	}

	return false;
}

void CStaticRigidBody::setpos(const CVector &pos)
{
	this->bounds->move(pos);
}

CVector CStaticRigidBody::pos()
{
	return this->bounds->pos();
}

void CStaticRigidBody::rotate(float angle)
{
	this->bounds->rotate(angle);
}

float CStaticRigidBody::angle(void)
{
	return this->bounds->angle();
}
