//
// Created by Administrator on 2017/7/21.
//

#include "AndroidH265DecoderJni.h"
#include <android/log.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <libavcodec/avcodec.h>
#include <stdio.h>
#include <string.h>


#define J4A_LOG_TAG "J4A"
//#define J4A_VLOGV(...)  __android_log_vprint(ANDROID_LOG_VERBOSE,   J4A_LOG_TAG, __VA_ARGS__)
//#define J4A_VLOGD(...)  __android_log_vprint(ANDROID_LOG_DEBUG,     J4A_LOG_TAG, __VA_ARGS__)
//#define J4A_VLOGI(...)  __android_log_vprint(ANDROID_LOG_INFO,      J4A_LOG_TAG, __VA_ARGS__)
//#define J4A_VLOGW(...)  __android_log_vprint(ANDROID_LOG_WARN,      J4A_LOG_TAG, __VA_ARGS__)
//#define J4A_VLOGE(...)  __android_log_vprint(ANDROID_LOG_ERROR,     J4A_LOG_TAG, __VA_ARGS__)

#define J4A_ALOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,    J4A_LOG_TAG, __VA_ARGS__)
#define J4A_ALOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,      J4A_LOG_TAG, __VA_ARGS__)
#define J4A_ALOGI(...)  __android_log_print(ANDROID_LOG_INFO,       J4A_LOG_TAG, __VA_ARGS__)
#define J4A_ALOGW(...)  __android_log_print(ANDROID_LOG_WARN,       J4A_LOG_TAG, __VA_ARGS__)
#define J4A_ALOGE(...)  __android_log_print(ANDROID_LOG_ERROR,      J4A_LOG_TAG, __VA_ARGS__)

#ifdef __cplusplus
}
#endif



int vHeight=0;
int vWidth=0;

/*
 * Class:     com_decoder_xiaomi_H265Decoder
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_decoder_xiaomi_H265Decoder_nativeInit
  (JNIEnv *env, jclass clazz)
{

}

/*
 * Class:     com_decoder_xiaomi_H265Decoder
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_decoder_xiaomi_H265Decoder_init
  (JNIEnv *env, jobject obj)
{

}

/*
 * Class:     com_decoder_xiaomi_H265Decoder
 * Method:    release
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_decoder_xiaomi_H265Decoder_release
  (JNIEnv *env, jobject obj)
{

}

/*
 * Class:     com_decoder_xiaomi_H265Decoder
 * Method:    decode
 * Signature: ([BIJ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_decoder_xiaomi_H265Decoder_decode
  (JNIEnv *env, jobject obj, jbyteArray data, jint numBytes, jlong packetPTS)
{
    AVCodec *pCodec;
    AVCodecContext *pCodecCtx= NULL;
    AVCodecParserContext *pCodecParserCtx=NULL;

    FILE *fp_out;
    AVFrame *pFrame;

    const int in_buffer_size = numBytes;
    //uint8_t in_buffer[in_buffer_size + FF_INPUT_BUFFER_PADDING_SIZE]={0};
    uint8_t *in_buffer;
    uint8_t *cur_ptr;
    int cur_size;
    AVPacket packet;
    int ret, got_picture;
    int y_size;

    //enum AVCodecID codec_id=AV_CODEC_ID_HEVC;
    enum AVCodecID codec_id = AV_CODEC_ID_H264;

    char filepath_in[]="/storage/emulated/0/bigbuckbunny_480x272.h264";


    char filepath_out[]="/storage/emulated/0/bigbuckbunnyh264_480x272_out.yuv";
    //char filepath_out[]="/storage/emulated/0/cuc_ieschool_h264_640x360_out.yuv";
    int first_time=1;

    if(data == NULL){
        J4A_ALOGD("data == null\n");
        return JNI_FALSE;
    }
    char* input_buffer = (char*)env->GetByteArrayElements(data, 0);

    in_buffer = (uint8_t *) calloc((size_t) (in_buffer_size + FF_INPUT_BUFFER_PADDING_SIZE), sizeof(uint8_t));

    memcpy(in_buffer, input_buffer, (size_t) (in_buffer_size));
    avcodec_register_all();

    pCodec = avcodec_find_decoder(codec_id);
    if (!pCodec) {
        J4A_ALOGD("Codec not found\n");
        return -1;
    }
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if (!pCodecCtx){
        J4A_ALOGD("Could not allocate video codec context\n");
        return -1;
    }

    pCodecParserCtx=av_parser_init(codec_id);
    if (!pCodecParserCtx){
        J4A_ALOGD("Could not allocate video parser context\n");
        return -1;
    }

    //if(pCodec->capabilities&CODEC_CAP_TRUNCATED)
    //    pCodecCtx->flags|= CODEC_FLAG_TRUNCATED;

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        J4A_ALOGD("Could not open codec\n");
        return -1;
    }

    //Output File
    fp_out = fopen(filepath_out, "wb");
    if (!fp_out) {
        J4A_ALOGD("Could not open output YUV file\n");
        return -1;
    }

    pFrame = av_frame_alloc();
    av_init_packet(&packet);


    cur_ptr = in_buffer;
    cur_size = in_buffer_size + FF_INPUT_BUFFER_PADDING_SIZE;


    int len = av_parser_parse2(
            pCodecParserCtx, pCodecCtx,
            &packet.data, &packet.size,
            cur_ptr , cur_size ,
            AV_NOPTS_VALUE, AV_NOPTS_VALUE, AV_NOPTS_VALUE);

//    cur_ptr += len;
//    cur_size -= len;

//    if(packet.size==0)
//        continue;

    //Some Info from AVCodecParserContext
    J4A_ALOGD("[Packet]Size:%6d\t",packet.size);
    switch(pCodecParserCtx->pict_type){
        case AV_PICTURE_TYPE_I: printf("Type:I\t");break;
        case AV_PICTURE_TYPE_P: printf("Type:P\t");break;
        case AV_PICTURE_TYPE_B: printf("Type:B\t");break;
        default: printf("Type:Other\t");break;
    }
    J4A_ALOGD("Number:%4d\n",pCodecParserCtx->output_picture_number);

    ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
    if (ret < 0) {
        J4A_ALOGD("Decode Error.\n");
        return ret;
    }
    if (got_picture) {
        J4A_ALOGD("\nCodec Full Name:%s\n",pCodecCtx->codec->long_name);
        J4A_ALOGD("width:%d\nheight:%d\n\n",pCodecCtx->width,pCodecCtx->height);

        vHeight = pCodecCtx->height;
        vWidth = pCodecCtx->width;
        //Y, U, V
        for(int i=0;i<pFrame->height;i++){
            fwrite(pFrame->data[0]+pFrame->linesize[0]*i,1,pFrame->width,fp_out);
        }
        for(int i=0;i<pFrame->height/2;i++){
            fwrite(pFrame->data[1]+pFrame->linesize[1]*i,1,pFrame->width/2,fp_out);
        }
        for(int i=0;i<pFrame->height/2;i++){
            fwrite(pFrame->data[2]+pFrame->linesize[2]*i,1,pFrame->width/2,fp_out);
        }

        J4A_ALOGD("Succeed to decode 1 frame!\n");
    }

    fclose(fp_out);


    av_parser_close(pCodecParserCtx);

    av_frame_free(&pFrame);
    avcodec_close(pCodecCtx);
    av_free(pCodecCtx);

    return 0;
}

/*
 * Class:     com_decoder_xiaomi_H265Decoder
 * Method:    encode
 * Signature: ([BIJ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_decoder_xiaomi_H265Decoder_encode
  (JNIEnv *env, jobject obj, jbyteArray data, jint numBytes, jlong packetPTS)
{

    return 0;
}

/*
 * Class:     com_decoder_xiaomi_H265Decoder
 * Method:    decodeBuffer
 * Signature: (Ljava/nio/ByteBuffer;IJ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_decoder_xiaomi_H265Decoder_decodeBuffer
  (JNIEnv *env, jobject obj, jobject data, jint numBytes, jlong packetPTS)
{

    return 0;
}

/*
 * Class:     com_decoder_xiaomi_H265Decoder
 * Method:    getWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_decoder_xiaomi_H265Decoder_getWidth
  (JNIEnv *env, jobject obj)
{

    return vWidth;
}

/*
 * Class:     com_decoder_xiaomi_H265Decoder
 * Method:    getHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_decoder_xiaomi_H265Decoder_getHeight
  (JNIEnv *env, jobject obj)
{
    return vHeight;
}

/*
 * Class:     com_decoder_xiaomi_H265Decoder
 * Method:    toTexture
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_com_decoder_xiaomi_H265Decoder_toTexture
  (JNIEnv *env, jobject obj, jint textureY, jint textureU, jint textureV)
{

    return 0;
}

