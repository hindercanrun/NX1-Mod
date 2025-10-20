namespace Assets
{
	void Dump_TracerDef(const TracerDef* tracerDef)
	{
		if (!tracerDef)
			return;

		std::string assetName = tracerDef->name;
		std::replace(assetName.begin(), assetName.end(), '/', '\\');

		std::string outPath = "game:\\" BASE_FOLDER "\\dump\\tracer\\" + assetName;
		std::ostringstream oss;

		oss << "TRACER"
			<< "\\material\\" << tracerDef->material->info.name
			<< "\\drawInterval\\" << tracerDef->drawInterval
			<< "\\speed\\" << tracerDef->speed
			<< "\\beamLength\\" << tracerDef->beamLength
			<< "\\beamWidth\\" << tracerDef->beamWidth
			<< "\\screwRadius\\" << tracerDef->screwRadius
			<< "\\screwDist\\" << tracerDef->screwDist
			<< "\\screwRadius_top_begin_expanding_overtime\\" << tracerDef->m_screwRadius_top_begin_expanding_overtime
			<< "\\screwRadius_bottom_begin_expanding_overtime\\" << tracerDef->m_screwRadius_bottom_begin_expanding_overtime
			<< "\\screwRadius_top_expanding_overtime\\" << tracerDef->m_screwRadius_top_expanding_overtime
			<< "\\screwRadius_bottom_expanding_overtime\\" << tracerDef->m_screwRadius_bottom_expanding_overtime
			<< "\\fadeout_top_begin\\" << tracerDef->m_fadeout_top_begin
			<< "\\fadeout_top_duration\\" << tracerDef->m_fadeout_top_duration
			<< "\\fadeout_bottom_begin\\" << tracerDef->m_fadeout_bottom_begin
			<< "\\fadeout_bottom_duration\\" << tracerDef->m_fadeout_bottom_duration;

		for (int i = 0; i < 5; ++i)
		{
			oss << "\\color" << i << "_r\\" << tracerDef->colors[i][0]
				<< "\\color" << i << "_g\\" << tracerDef->colors[i][1]
				<< "\\color" << i << "_b\\" << tracerDef->colors[i][2]
				<< "\\color" << i << "_a\\" << tracerDef->colors[i][3];
		}

		oss << "\n";

		std::string data = oss.str();
		Util::FileSystem::WriteFileToDisk(outPath.c_str(), data.c_str(), data.size());
	}
}
