#include <game/IObjectStatic.h>

IObjectStatic::IObjectStatic()
{
	_pos = CVector(0.0f, 0.0f, 0.0f);
	_angle = 0.0f;
	_destroyed = false;
	_size = {0, 0};

	_fragility = 0.0f;
	_alpha = 1.0f;
}

IObjectStatic::IObjectStatic(CVector p, CBox b)
{
	_pos = p;
	_size = b;

	_destroyed = false;
}

void IObjectStatic::process(void)
{
	if (_angle > 360)	{
		_angle -= 360;
	}
	if (_angle < 0) {
		_angle += 360;
	}
}

void IObjectStatic::LoadConfig(std::string name)
{
	CXMLConfig& config = CXMLConfig::GetInstance();
	TextureManager& TexManager = TextureManager::GetInstance();

	if (!config.LoadXML(name)) {
		std::cout << "cannot load config for " << name << "\n";
	}

	solid = config.ReadBool(name, "class/solid");
	flat  = config.ReadBool(name, "class/flat");

	_size.w = config.ReadFloat(name, "class/size", "width", 64);
	_size.h = config.ReadFloat(name, "class/size", "height", 64);

	_health = config.ReadFloat(name, "class/max_health", "", 100);

	sprite = TexManager.load(
		config.ReadStr(name, "class/texture", "file", "notexture.tga"),
		point(
			config.ReadFloat(name, "class/texture/origin", "x"),
			config.ReadFloat(name, "class/texture/origin", "y")
		),
		config.ReadInt(name, "class/texture/frames", "x", 1),
		config.ReadInt(name, "class/texture/frames", "y", 1)
	);

	sprite->frame = config.ReadInt(name, "class/texture/frames", "default");

	_pos.z = config.ReadFloat(name, "class/zpos");
}

IObjectStatic::~IObjectStatic()
{

}
