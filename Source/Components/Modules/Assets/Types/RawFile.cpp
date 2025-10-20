#include "RawFile.h"

namespace Assets
{
    RawFile* LoadRawFiles(const char* name)
    {
		char path[256];
		_snprintf(path, sizeof(path), "game:/nx1-data/raw/%s", name);
		path[sizeof(path) - 1] = '\0';

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
		// TODO: we should probably clean the file name so we don't get any garbage... buuuut that's not really needed, not right now atleast

		char path[256];
		_snprintf(path, sizeof(path), "game:/nx1-data/dump/%s", rawFile->name);
		path[sizeof(path) - 1] = '\0';

		FILE* f = fopen(path, "wb");
		if (!f)
		{
			Symbols::Com_Printf(0, "dumping error: unable to write to path '%s'\n", path);
			return;
		}

		int outSize = rawFile->len * 2 + 1024;
		char* buf = (char*)malloc(outSize);
		if (!buf)
		{
			fclose(f);
			Symbols::Com_Printf(0, "dumping error: ran out of memory to dump '%s'\n", rawFile->name);
			return;
		}

		memset(buf, 0, outSize);
		size_t bytesToWrite = 0;

		// decompress the file if it's compressed
		if (rawFile->compressedLen > 0)
		{
			z_stream strm;
			memset(&strm, 0, sizeof(z_stream));

			strm.next_in = (Bytef*)rawFile->buffer;
			strm.avail_in = rawFile->compressedLen;
			strm.next_out = (Bytef*)buf;
			strm.avail_out = outSize;

			if (inflateInit(&strm) == Z_OK)
			{
				int ret = inflate(&strm, Z_FINISH);
				bytesToWrite = strm.total_out;
				inflateEnd(&strm);
			}
			else
			{
				Symbols::Com_Printf(0, "dumping error: inflateInit failed with '%s'\n", rawFile->name);
			}

			//Util::Print::Printf("decompressed rawfile '%s'\n", rawFile->name);
		}
		else
		{
			memcpy(buf, rawFile->buffer, rawFile->len);
			bytesToWrite = rawFile->len;
		}

		fwrite(buf, 1, bytesToWrite, f);
		Symbols::Com_Printf(0, "dumped rawfile '%s'\n", rawFile->name);

		fclose(f);
		free(buf);
	}

	void FreeRawFiles(RawFile* raw)
	{
		if (!raw)
			return;
		free((void*)raw->buffer);
		free((void*)raw->name);
		free(raw);
	}
}
