#include "FogDef.h"

namespace Assets
{
	void Dump_FogDef(const FogDef* fogDef)
	{
		if (!fogDef)
			return;

		std::string assetName = fogDef->mp_name;
		std::replace(assetName.begin(), assetName.end(), '/', '\\');

		std::string outPath = "game:\\" BASE_FOLDER "\\dump\\fog\\" + assetName + ".fsi";
		std::ostringstream oss;

		oss << std::fixed << std::setprecision(6);

		oss << "basedist [" << fogDef->m_start_dist << "]\n";
		oss << "halfdist [" << fogDef->m_halfway_dist << "]\n";
		oss << "_fogcolor [" << fogDef->m_red << " " << fogDef->m_green << " " << fogDef->m_blue << "]\n";
		oss << "fogintensity [" << fogDef->m_multiplied_blend << "]\n";
		oss << "fogopacity [" << fogDef->m_max_opacity << "]\n";
		oss << "multipliedNearColor [" << fogDef->m_multiplied_near_red << " " << fogDef->m_multiplied_near_green << " " << fogDef->m_multiplied_near_blue << "]\n";
		oss << "multipliedFarColor [" << fogDef->m_multiplied_far_red << " " << fogDef->m_multiplied_far_green << " " << fogDef->m_multiplied_far_blue << "]\n";
		oss << "_sunfogcolor [" << fogDef->m_sun_red << " " << fogDef->m_sun_green << " " << fogDef->m_sun_blue << "]\n";
		oss << "sunfogopacity [" << fogDef->m_multiplied_blend << "]\n";
		oss << "sunDir [" << fogDef->m_sun_dir[0] << " " << fogDef->m_sun_dir[1] << " " << fogDef->m_sun_dir[2] << "]\n";
		oss << "sunfoginner [" << fogDef->m_sun_begin_fade_angle << "]\n";
		oss << "sunfogouter [" << fogDef->m_sun_end_fade_angle << "]\n";
		oss << "transitionTime [" << fogDef->m_transition_time << "]\n";
		oss << "sunFogScale [" << fogDef->m_sun_fog_scale << "]\n";

		std::string fsiData = oss.str();

		Util::FileSystem::WriteFileToDisk(outPath.c_str(), fsiData.c_str(), (int)fsiData.size());
	}
}
