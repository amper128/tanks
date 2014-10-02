#pragma once

class object_tree : public object_2d
{
public:
	object_tree(Tpoint pos);

	bool draw();

	void process() {};

	~object_tree() {};
};
