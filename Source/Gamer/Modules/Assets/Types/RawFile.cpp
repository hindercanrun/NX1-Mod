namespace RawFile
{
    RawFile* LoadRawFiles(const char* name)
    {
        char path[256];
        sprintf(path, "game:/nx1-data/raw/%s", name);

        FILE* f = fopen(path, "rb");
        if (!f)
        {
            return NULL;
        }

        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fseek(f, 0, SEEK_SET);

        if (size <= 0)
        {
            fclose(f);
            return NULL;
        }

        RawFile* raw = (RawFile*)malloc(sizeof(RawFile));
        if (!raw)
        {
            fclose(f);
            return NULL;
        }

        memset(raw, 0, sizeof(RawFile));

        raw->name = strdup(name);

        char* buffer = (char*)malloc(size);
        if (!buffer)
        {
            fclose(f);
            free((void*)raw->name);
            free(raw);
            return NULL;
        }

        fread(buffer, 1, size, f);
        fclose(f);

        raw->buffer = buffer;
        raw->len = (int)size;
        raw->compressedLen = 0; // TODO: support compressed files

		Util::Print::Printf("Loaded raw file '%s' from disk\n", name);
        return raw;
    }

	void DumpRawFiles(const RawFile* rawFile, char* buffer, int size)
	{
		if (rawFile && rawFile->buffer && rawFile->len > 0)
		{
			char dumpPath[256];
			sprintf(dumpPath, "game:/nx1-data/dump/%s", rawFile->name);

			FILE* f = fopen(dumpPath, "wb");
			if (f)
			{
				int size = rawFile->len + 1;
				char* buf = (char*)malloc(size);
				if (!buf)
				{
					fclose(f);
				}

				memset(buf, 0, size);

				if (rawFile->compressedLen > 0)
				{
					z_stream strm;
					memset(&strm, 0, sizeof(z_stream));

					strm.next_in = (Bytef*)rawFile->buffer;
					strm.avail_in = rawFile->compressedLen;
					strm.next_out = (Bytef*)buf;
					strm.avail_out = size - 1;

					if (inflateInit(&strm) == Z_OK)
					{
						int ret = inflate(&strm, Z_FINISH);
						inflateEnd(&strm);

						if (ret != Z_STREAM_END)
							printf("Warning: Failed to fully decompress %s (err %d)\n", rawFile->name, ret);
					}
					else
					{
						printf("Error: inflateInit failed for %s\n", rawFile->name);
					}
				}
				else
				{
					memcpy(buf, rawFile->buffer, rawFile->len);
				}

				fwrite(buf, 1, rawFile->len, f);
				fclose(f);
				free(buf);
			}
		}
	}
}
