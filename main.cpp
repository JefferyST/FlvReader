#include "parseapi.h"

int main(int argc, char *argv[])
{
    //char *inputFile = "d://testvideo//barsandtone.flv";
	char *inputFile = "d://testvideo//test1.flv";

    char *outVidoeFile = "video.h264";
    char *outAudioFile = "audio.aac";

    FILE *pInputFile = fopen(inputFile,"rb");
    FILE *pOutVideo = fopen(outVidoeFile,"wb");
    FILE *pOutAudio = fopen(outAudioFile,"wb");

   
    MediaInfo info;
    DEMUX_OpenFile(inputFile,info);
    DataPacket packet;
    int time =0;

	if (V_CODEC_ID_H264 == info.video_codec_id)
	{
		fwrite(info.SPS_PPS.SPSData, info.SPS_PPS.SPSDataSize, 1, pOutVideo);//sps
		fwrite(info.SPS_PPS.PPSData, info.SPS_PPS.PPSDataSize, 1, pOutVideo);//pps	
	}
	
    while(true)
    {
        if(DEMUX_ReadFrame(packet) == -1)
        {
             DEMUX_CloseFile();
             cout<<"Play over";
             break;
        }
        else
        {
			if (packet.stream_type == TYPE_VIDEO)
				fwrite(packet.data, packet.data_size, 1, pOutVideo); 
            else if (packet.stream_type == TYPE_AUDIO)
                fwrite(packet.data, packet.data_size,1,pOutAudio);
        }

    }

   fclose(pOutVideo);
   fclose(pOutAudio);

   return 0;
}

