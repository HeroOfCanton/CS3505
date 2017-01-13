/*
 * James Lundgren and Ryan Welling
 * Checkpoint 3
 * March 25, 2014
 */

#include <iostream>

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

#include "../ffmpeg/libavutil/imgutils.h"
#include "../ffmpeg/libavcodec/avcodec.h"
#include "../ffmpeg/libavformat/avformat.h"
#include "../ffmpeg/libswscale/swscale.h"

}

// Our code is C++, but it will work fine with ffmpeg's C code so
// long as the above strategy is used.

using namespace std;
void draw_circle(AVFrame *frame, int x, int y, int delta);
void make_copy(AVFrame *frame, AVPixelFormat allowed);

/**
 * 
 */
int main (int argc, char *argv[])
{

  // Make sure there is a file to use
  if (argc < 2)
  {
    cout << "Error: Please provide image file" << endl;
    return -1;
  }

  // Check the file entered for the .jpg file extension
  string file = argv[1];
  string extension = file.substr(file.size()-4, file.size());

  if (extension != ".jpg")
  {
    cout << "Extension doesn't equal .jpg: " << extension << endl;
    return -1; 
  }

  /*   
   * BEGIN CITE
   *
   * Code taken from 
   * https://github.com/chelyaev/ffmpeg-tutorial/blob/master/tutorial01.c
   * https://github.com/FFmpeg/FFmpeg/blob/master/doc/examples/decoding_encoding.c
   * 
   */

  AVFormatContext    *iFormatContext = NULL;
  int                i, videoStream;
  AVCodecContext     *pCodecCtx = NULL;
  AVCodecContext     *mpffCodecCtx = NULL;
  AVCodec            *pCodec = NULL;
  AVCodec            *mpffCodec = NULL;
  AVFrame            *pFrame = NULL;
  AVFrame            *pFrameRGB = NULL;
  AVPacket           packet;
  AVPacket           mpffPacket;
  int                frameFinished;
  int                numBytes, out_size;
  int                gotPacket = 0;
  uint8_t            *buffer = NULL;
  char               *filename;
  FILE               *f;
  AVDictionary       *optionsDict = NULL;
  struct SwsContext  *sws_ctx = NULL;
 
  // Register all muxers and demuxers...
  av_register_all();

  // Try and open the file, read the header
  if(avformat_open_input(&iFormatContext, argv[1], NULL, NULL) != 0)
      return -1; 

  // Read packets of the file to get the stream information 
  if(avformat_find_stream_info(iFormatContext,NULL) < 0)
    return -1; 
  
  // Prints detailed information about input or output format...
  av_dump_format(iFormatContext, 0, argv[1], 0);

  // nb_streams = number of elements in AvFormatContext.streams, loop through the streams and
  // find first video stream
  videoStream = -1;
  for(i = 0; i < iFormatContext->nb_streams; i++)
    if (iFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
    {
      videoStream = i;
      break;
    }

  // Make sure the video stream was found
  if(videoStream == -1)
    return -1;
 
  // We need a pointer to the codecs context so we can 
  // use the information when decoding
  pCodecCtx = iFormatContext->streams[videoStream]->codec;

  // Gets the decoder for the image, if there is one
  // if not, the format is unsupported
  pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
  if(pCodec == NULL)
      return -1;

  // Gets the stream information
  if(avcodec_open2(pCodecCtx, pCodec, &optionsDict) < 0)
    return -1;

  // Allocate the frame for the image
  pFrame = av_frame_alloc();

  // Allocate an AVFrame structure and check to see that it was 
  // allocated
  pFrameRGB = av_frame_alloc();
  if(pFrameRGB == NULL)
    return -1;

  // Need the buffer size, allocate memory for the buffer given RGB24 format
  numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

  // What will hold the pixel information
  buffer = (uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

  // Need this in order to perform conversion operations (to RGB24)
  sws_ctx = sws_getContext(
         pCodecCtx->width,
	 pCodecCtx->height,
	 pCodecCtx->pix_fmt,
	 pCodecCtx->width,
	 pCodecCtx->height,
	 PIX_FMT_RGB24,
	 SWS_BILINEAR,
	 NULL,
	 NULL,
	 NULL
     );

  // Sets up the picture fields based on the parameters provided
  avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
  
  // Returns the image frame
  av_read_frame(iFormatContext, &packet);
  
  /* We can just do this in the loop since we are not doing a memcopy*/
  if (packet.stream_index == videoStream)
    {
      // Decodes the image and fills the buffer
      avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

      // Scale the image, puts the resulting scaled 'slice' in image pFrameRGB->data
      sws_scale(
		sws_ctx,
		(uint8_t const * const *)pFrame->data,
		pFrame->linesize,
		0,
		pCodecCtx->height,
		pFrameRGB->data,
		pFrameRGB->linesize
		);
    }

  /*
   * END CITE
   */

  // Get width and height of image, to pass into drawCircle()
  int height = pCodecCtx->height;
  int width = pCodecCtx->width;
  
  // Pick an arbitrary circle radius size
  int radius = width / 25;
  
  // Pick an arbitrary starting point within the image
  int cirStartX = pCodecCtx->width / 2 + radius;
  int cirStartY = pCodecCtx->height / 2;

  // Direction will tell if the ball is moving up or down
  // This will be 1 (above initial y point) or -1 (below initial y point)
  int direction = -1;

  // speed will give the illusion of ball movement
  int speed = 5;
  
  /* 
   * This for loop calls the drawCircle() method to draw a ball on the image i number of times.
   * Creates a temporary frame each time to draw on and then saves it.
   * Should take into account passed in image size to draw a proportional sized circle on the image
   * with the circle appearing to 'bounce' up and down'.
   */
 
 for (i = 0; i < 300; i++)
    {
      // Need temp frame, and component parts, to draw to each time through
      AVFrame *drawFrame;
      drawFrame = av_frame_alloc();
      numBytes = avpicture_get_size(PIX_FMT_RGB24, width, height);
      buffer = (uint8_t *) av_malloc(numBytes*sizeof(uint8_t));
      
      // Assign appropriate parts of buffer to image planes in drawFrame
      avpicture_fill(
		     (AVPicture *)drawFrame, 
		     buffer, 
		     PIX_FMT_RGB24, 
		     width, 
		     height
		     );
      
      // Decodes the image and fills the buffer
      avcodec_decode_video2(pCodecCtx, pFrameRGB, &frameFinished, &packet);
      
      sws_ctx = sws_getContext
	(
	 width,
	 height,
	 PIX_FMT_RGB24,
	 width,
	 height,
	 PIX_FMT_RGB24,
	 SWS_BILINEAR,
	 NULL,
	 NULL,
	 NULL
	 );

      sws_scale(
	       sws_ctx,
	       (uint8_t const * const *)pFrameRGB->data,
	       pFrameRGB->linesize,
	       0,
	       height,
	       drawFrame->data,
	       drawFrame->linesize
	       );
     
      // Draw it
      draw_circle(drawFrame, cirStartX, cirStartY, radius);

      // find the mff video encoder 
      mpffCodec = avcodec_find_encoder(AV_CODEC_ID_MPFF);
      if (!mpffCodec) 
	{
	  cout << "codec not found 1a" << endl;;
	  return -1;
	}
      
      // allocate space for the encoder using the mpffcodec
      mpffCodecCtx = avcodec_alloc_context3(mpffCodec);
      
      // Set the fields we need (width, height, and codec to MPFF)
      mpffCodecCtx->width = width;
      mpffCodecCtx->height = height;
      mpffCodecCtx->codec = mpffCodec;
      mpffCodecCtx->pix_fmt = mpffCodecCtx->codec->pix_fmts[0];

      sws_ctx = sws_getContext(
			       width,
			       height,
			       PIX_FMT_RGB24,
			       width,
			       height,
			       mpffCodecCtx->codec->pix_fmts[0],
			       SWS_BILINEAR,
			       NULL,
			       NULL,
			       NULL
			       );
      sws_scale(
		sws_ctx,
		(uint8_t const * const *)drawFrame->data,
		drawFrame->linesize,
		0,
		height,
		drawFrame->data,
		drawFrame->linesize
		);

      // Check direction and alter speed accordingly
      if(direction == 1) 
	cirStartY += speed;
      if(direction == -1)
	cirStartY -= speed;
      
      /*
       * Check location of last drawn ball and adjust direction, up or down
       */
      
      // If new y coord plus radius plus potention speed increase
      //  would be greater than height, reverse direction
      if(cirStartY + radius + speed + 1 > height)
	direction = -1;
      
      // If new y coord, minus the radius, minus the potential speed decrease
      // would be less than 0, reverse direction
      if(cirStartY - radius - speed - 1 < 0)
	direction = 1;
            
      // -------------------------- encode to mpff and write to file ------------------;

      // Open the codec
      if(avcodec_open2(mpffCodecCtx, mpffCodec, NULL) < 0)
	{
	  cout << "could not open codec" << endl;
	  return -1; 
	}

      drawFrame->format = mpffCodecCtx->codec->pix_fmts[0];
      drawFrame->width = width;
      drawFrame->height = height; 

      // make sure the packet is empty and ready to use
      av_init_packet(&mpffPacket);
 
      mpffPacket.data = NULL;
      mpffPacket.size = 0; 
      fflush(stdout);

      // encode the image
      out_size = avcodec_encode_video2(mpffCodecCtx, &mpffPacket, drawFrame, &gotPacket);

      char filename[32];
      FILE *mpffFile;
      snprintf(filename, sizeof(filename), "frame%03d.mpff", i);

      // open the file 
      mpffFile = fopen(filename, "wb");
      // write to the file
      fwrite(mpffPacket.data, 1, mpffPacket.size, mpffFile);
      // close the file and free resources we used
      fclose(mpffFile);

      avcodec_close(mpffCodecCtx);
      av_free(drawFrame);
      av_free_packet(&mpffPacket);
      //-------------------- end encoding and file writing ----------------------------
      
    }
  
  // Release all resources we have used
  av_free_packet(&packet);
  sws_freeContext(sws_ctx);  

  // Free RGB image, YUV frame
  av_free(buffer);
  av_free(pFrameRGB);
  av_free(pFrame);
  
  // close codec and video file
  avcodec_close(pCodecCtx);
  avformat_close_input(&iFormatContext);
  
  return 0;
  
}

/**
 * This method draws a circle on the image given an x and y coordinate, 
 * as well as a radius, which will be used to determine how big the cirlce 
 * will be (calcuated based off of image size)
 */
void draw_circle(AVFrame *frame, int x, int y, int radius)
{
  int delta_x, y1, y2, x1; 

  // Use pythagorean theorem to draw circle
  // Start at the top of the circle ingdraw each row going down
  for(y1 = y + radius; y1 >= (y - radius); y1--)
    {
      // If we have point (6,5) and radius = 4, then starting y coordinate y1 = 9. Using pythagorean theorem, 
      // r^2 = x^2 + y^2. we can get the y value by subtracting y1 from y. Since starting y1 = 9, y2 = 9-5 = 4, 
      // so starting x = 0 since x = sqrt(4^2-4^2) for next row, we have y1 = 8, y2 = 8-5 = 3, x = sqrt(4^2 - 3^2) 
      y2 = y-y1;
      delta_x = sqrt(radius*radius - y2*y2);    

      // Loop through the range and change the pixels in that range
      for (x1 = x - delta_x; x1 <= (x + delta_x); x1++)
	{
	  // Moves the pointer to the correct position
	  uint8_t * tmp = frame->data[0]+y1*frame->linesize[0]+x1 * 3;

	  *(tmp++) = 25;   //red
	  *(tmp++) = 255;  //green
	  *(tmp++) = 25;   //blue
	  memset(tmp, 0, 3); 

	}
    }
}
