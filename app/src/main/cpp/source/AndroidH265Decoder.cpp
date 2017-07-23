//
// Created by Administrator on 2017/7/21.
//

#include "AndroidH265Decoder.h"
#include <android/log.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "x265.h"
#include "x265_config.h"
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



/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ican_ytx_com_h265decode_H265Decoder_nativeInit(JNIEnv *env, jclass clazz)
{

}

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ican_ytx_com_h265decode_H265Decoder_init(JNIEnv *env, jobject obj)
{

}

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    release
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ican_ytx_com_h265decode_H265Decoder_release(JNIEnv *env, jobject obj)
{

}

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    decode
 * Signature: ([BIJ)Z
 */
JNIEXPORT jboolean JNICALL Java_ican_ytx_com_h265decode_H265Decoder_decode(JNIEnv *env,
                                                                            jobject obj,
                                                                            jbyteArray data,
                                                                            jint numBytes,
                                                                            jlong packetPTS)
{




    return 0;
}


JNIEXPORT jboolean JNICALL Java_ican_ytx_com_h265decode_H265Decoder_encode(JNIEnv *env,
                                                                           jobject obj,
                                                                           jbyteArray data,
                                                                           jint numBytes,
                                                                           jlong packetPTS)
{


    int i,j;
    FILE *fp_src=NULL;
    FILE *fp_dst=NULL;
    int y_size;
    int buff_size;
    char *buff=NULL;
    int ret;
    x265_nal *pNals=NULL;
    uint32_t iNal=0;

    x265_param* pParam=NULL;
    x265_encoder* pHandle=NULL;
    x265_picture *pPic_in=NULL;

    //Encode 50 frame
    //if set 0, encode all frame
    int frame_num=50;
    int csp=X265_CSP_I420;
    int width=640,height=360;

    fp_src=fopen("/storage/emulated/0/cuc_ieschool_640x360_yuv420p.yuv","rb");
    //fp_src=fopen("../cuc_ieschool_640x360_yuv444p.yuv","rb");

    fp_dst=fopen("/storage/emulated/0/cuc_ieschool.h265","wb");
    //Check
    if(fp_src==NULL||fp_dst==NULL){
        return -1;
    }

    pParam=x265_param_alloc();
    x265_param_default(pParam);
    pParam->bRepeatHeaders=1;//write sps,pps before keyframe
    pParam->internalCsp=csp;
    pParam->sourceWidth=width;
    pParam->sourceHeight=height;
    pParam->fpsNum=25;
    pParam->fpsDenom=1;
    //Init
    pHandle=x265_encoder_open(pParam);
    if(pHandle==NULL){
        J4A_ALOGD("x265_encoder_open err\n");
        return 0;
    }
    y_size = pParam->sourceWidth * pParam->sourceHeight;

    pPic_in = x265_picture_alloc();
    x265_picture_init(pParam,pPic_in);
    switch(csp){
        case X265_CSP_I444:{
            buff=(char *)malloc(y_size*3);
            pPic_in->planes[0]=buff;
            pPic_in->planes[1]=buff+y_size;
            pPic_in->planes[2]=buff+y_size*2;
            pPic_in->stride[0]=width;
            pPic_in->stride[1]=width;
            pPic_in->stride[2]=width;
            break;
        }
        case X265_CSP_I420:{
            buff=(char *)malloc(y_size*3/2);
            pPic_in->planes[0]=buff;
            pPic_in->planes[1]=buff+y_size;
            pPic_in->planes[2]=buff+y_size*5/4;
            pPic_in->stride[0]=width;
            pPic_in->stride[1]=width/2;
            pPic_in->stride[2]=width/2;
            break;
        }
        default:{
            J4A_ALOGD("Colorspace Not Support.\n");
            return -1;
        }
    }

    //detect frame number
    if(frame_num==0){
        fseek(fp_src,0,SEEK_END);
        switch(csp){
            case X265_CSP_I444:frame_num=ftell(fp_src)/(y_size*3);break;
            case X265_CSP_I420:frame_num=ftell(fp_src)/(y_size*3/2);break;
            default:printf("Colorspace Not Support.\n");return -1;
        }
        fseek(fp_src,0,SEEK_SET);
    }

    //Loop to Encode
    for( i=0;i<frame_num;i++){
        switch(csp){
            case X265_CSP_I444:{
                fread(pPic_in->planes[0],1,y_size,fp_src);       //Y
                fread(pPic_in->planes[1],1,y_size,fp_src);       //U
                fread(pPic_in->planes[2],1,y_size,fp_src);       //V
                break;}
            case X265_CSP_I420:{
                fread(pPic_in->planes[0],1,y_size,fp_src);       //Y
                fread(pPic_in->planes[1],1,y_size/4,fp_src); //U
                fread(pPic_in->planes[2],1,y_size/4,fp_src); //V
                break;}
            default:{
                J4A_ALOGD("Colorspace Not Support.\n");
                return -1;}
        }

        ret=x265_encoder_encode(pHandle,&pNals,&iNal,pPic_in,NULL);
        J4A_ALOGD("Succeed encode %5d frames\n",i);

        for(j=0;j<iNal;j++){
            fwrite(pNals[j].payload,1,pNals[j].sizeBytes,fp_dst);
        }
    }
    //Flush Decoder
    while(1){
        ret=x265_encoder_encode(pHandle,&pNals,&iNal,NULL,NULL);
        if(ret==0){
            break;
        }
        J4A_ALOGD("Flush 1 frame.");

        for(j=0;j<iNal;j++){
            fwrite(pNals[j].payload,1,pNals[j].sizeBytes,fp_dst);
        }
    }

    x265_encoder_close(pHandle);
    x265_picture_free(pPic_in);
    x265_param_free(pParam);
    free(buff);
    fclose(fp_src);
    fclose(fp_dst);
    J4A_ALOGD("encode end.");
    return 0;
}
/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    decodeBuffer
 * Signature: (Ljava/nio/ByteBuffer;IJ)Z
 */
JNIEXPORT jboolean JNICALL Java_ican_ytx_com_h265decode_H265Decoder_decodeBuffer(JNIEnv *env,
                                                                                 jobject obj,
                                                                                 jobject data,
                                                                                 jint numBytes,
                                                                                 jlong packetPTS)
{


    return 0;
}

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    getWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ican_ytx_com_h265decode_H265Decoder_getWidth(JNIEnv * env, jobject obj)
{

    return 0;
}

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    getHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ican_ytx_com_h265decode_H265Decoder_getHeight(JNIEnv *env, jobject obj)
{

    return 0;
}

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    toTexture
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_ican_ytx_com_h265decode_H265Decoder_toTexture(JNIEnv *env,
                                                                          jobject obj,
                                                                          jint textureY,
                                                                          jint textureU,
                                                                          jint textureV)
{

    return 0;
}