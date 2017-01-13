// g++ test.cpp `pkg-config --cflags --libs libavutil libavformat libavcodec`
//
// The `backticks` above indicate that we execute the pkg-config command, then
// use its results as inputs to the g++ command.  You can execute the
// pkg-config command separately to see what command line arguments it
// generates, but smart CS types will keep using it as shown above so that
// if libraries change, so does your build command.

#include <iostream>
#include <math.h>

// A few definitions to help this code compile.

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

// All ffmpeg headers refer to C functions and declarations.

extern "C"
{

// You can now include any .h files from ffmpeg, and call and use
// functions and declarations as needed.

#include "../ffmpeg/libavformat/avformat.h"
#include "../ffmpeg/libswscale/swscale.h"
#include "../ffmpeg/libavcodec/avcodec.h"

}

// Our code is C++, but it will work fine with ffmpeg's C code so
// long as the above strategy is used.

using namespace std;

// Draw a single pixel on image frame
void drawPixel(int x, int y, int r, int g, int b, AVFrame *f) {
  uint8_t *pix = f->data[0] + f->linesize[0] * y + x * 3;
  *(pix++) = r;
  *(pix++) = g;
  *(pix++) = b;
}
// Draw a circle and shade it
void drawCircle(int cx, int cy, int rad, AVFrame *f) {
  int x, y, cirX, cirY;
  int i;
  for(x = cx-rad; x < cx+rad; x++) {
    for(y = cy-rad; y < cy+rad; y++) {
      cirX = x - cx;
      cirY = y - cy;
      if (((cirX*cirX)+(cirY*cirY))<(rad*rad)) {
	drawPixel(x, y, 255-i, 255-i, 255-i, f);
      }
    }
    i += 1;
  }
}

int main (int argc, char *argv[])
{
  
  AVFormatContext *jpgFmtCtx;
  AVCodecContext  *jpgCodecCtx;
  AVCodec         *jpgCodec;
  AVCodec         *mpffCodec;
  AVFrame         *jpgFrame;
  AVFrame         *jpgFrameRGB;
  AVPacket         jpgPacket;
  AVPacket         mpffPacket;
  int              gotPacket = 0;
  int              frameFinished;
  int              numBytes;
  uint8_t         *buf;

  av_register_all();
  avcodec_register_all();

  // Open the file, allocate some space for the context
  if (avformat_open_input(&jpgFmtCtx, argv[1], NULL, NULL) != 0)
    {
      cout << "Error in opening input file " << argv[1] << endl;
      return -1;
    }
  
  // There is only one stream for a single jpg file, but let's make sure it's there 
  if(avformat_find_stream_info(jpgFmtCtx, NULL) < 0)
    {
      cout << "Error in finding video stream" << endl;
      avformat_close_input(&jpgFmtCtx);
      return -1;
    }

  // Get a pointer for the video stream
  jpgCodecCtx = jpgFmtCtx->streams[0]->codec;
  
  // Find the decoder for stream
  jpgCodec = avcodec_find_decoder(jpgCodecCtx->codec_id);

  // Codec was not found
  if(jpgCodec == NULL) 
    {
      cout << "No supported codec found" << endl;
      avformat_close_input(&jpgFmtCtx);
      return -1;
    }

  // Open codec
  if(avcodec_open2(jpgCodecCtx, jpgCodec, NULL) < 0)
    {
      cout << "Error in opening decoder" << endl;
      avformat_close_input(&jpgFmtCtx);
      return -1;
    }

  jpgFrame = avcodec_alloc_frame();
  jpgFrameRGB = avcodec_alloc_frame();

  return 0;
  
}

//https://github.com/CerebralStorm/CS3505/blob/master/SpringProject1/bouncer/test.cc
//http://random-stuff-mine.blogspot.com/2014/01/decoding-jpeg-image-file-using-libavcodec.html
