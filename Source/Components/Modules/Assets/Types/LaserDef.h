#pragma once

namespace Assets
{
	enum ELaserUVLayout : int
	{
		LASER_UV_DEFAULT = 0x0,
		LASER_UV_BILLBOARD = 0x1,
		LASER_UV_COUNT = 0x2,
	};

	enum ELaserShape : int
	{
		LASER_SHAPE_DEFAULT = 0x0,
		LASER_SHAPE_BILLBOARD = 0x1,
		LASER_SHAPE_COUNT = 0x2,
	};

	struct LaserDef
	{
		const char *mp_name;
		Material *m_material;
		float m_src_width;
		float m_segment;
		float m_texture_animation;
		float m_src_red;
		float m_src_green;
		float m_src_blue;
		float m_src_alpha;
		float m_dst_red;
		float m_dst_green;
		float m_dst_blue;
		float m_dst_alpha;
		ELaserUVLayout m_uv;
		ELaserShape m_shape;
	};

	//void Dump_LaserDef(const LaserDef* laserDef);
}
