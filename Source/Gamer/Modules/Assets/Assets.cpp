namespace Assets
{
	Util::Hook::Detour DB_GetRawBuffer_Hook;
	void DB_GetRawBuffer(const RawFile* rawFile, char* buffer, int size)
	{
		auto Invoke = DB_GetRawBuffer_Hook.Invoke<void(*)(const RawFile*, char*, int)>();

		// TODO: put this behind a dvar
		// override the file if it exists
		RawFile* loaded = LoadRawFiles(rawFile->name);
		if (loaded)
		{
			int copySize = (size < loaded->len) ? size : loaded->len;
			memcpy(buffer, loaded->buffer, copySize);

			FreeRawFiles(loaded);
			return;
		}

		// TODO: put this behind a dvar
		//DumpRawFiles(rawFile, buffer, size);

		Invoke(rawFile, buffer, size);
	}

	void Hooks()
	{
		DB_GetRawBuffer_Hook.Create(0x822140E0, DB_GetRawBuffer);
	}

	void Load()
	{
		Hooks();
	}

	void Unload()
	{
	}
}
