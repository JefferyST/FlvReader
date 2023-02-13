#include "parseapi.h"

CFlvParser gFlv;
FILE* gFile = NULL;
int gVideoType = 0;

int DEMUX_OpenFile(const char *name, MediaInfo &info)
{
	gFile = fopen(name, "rb");
	char szFileHeader[8] = { 0 };
	fread(szFileHeader, 1, 8, gFile);
	fseek(gFile, 0, SEEK_SET);

	if ('F' == szFileHeader[0] && 'L' == szFileHeader[1] && 'V' == szFileHeader[2])
	{
		gVideoType = TYPE_FLV;
		if (gFlv.OpenFlv(gFile))
			gFlv.GetMediaInfo(info);
		else
			return 0;
	}
	else
	{   
		return -1;
	}

	return 1;
}


int DEMUX_ReadFrame(DataPacket &packet)
{
	DataPacket tmpPacket;
	int iRet = 0;
	if (TYPE_FLV == gVideoType)
	{
		iRet = gFlv.ReadAvFrame(tmpPacket, -1);
		packet = tmpPacket;
	}
	
	if (iRet == -1)
		return -1;

	return packet.data_size;
    
}

int DEMUX_CloseFile()
{
	if (gFile != NULL)
	{
		fclose(gFile);
	}
	return 1;
}
