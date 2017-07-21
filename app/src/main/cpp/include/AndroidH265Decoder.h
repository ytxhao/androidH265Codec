//
// Created by Administrator on 2017/7/21.
//

#include <jni.h>

#ifndef H265DECODE_ANDROIDH265DECODER_H
#define H265DECODE_ANDROIDH265DECODER_H


#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ican_ytx_com_h265decode_H265Decoder_nativeInit
(JNIEnv *, jclass);

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ican_ytx_com_h265decode_H265Decoder_init
(JNIEnv *, jobject);

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    release
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_ican_ytx_com_h265decode_H265Decoder_release
(JNIEnv *, jobject);

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    decode
 * Signature: ([BIJ)Z
 */
JNIEXPORT jboolean JNICALL Java_ican_ytx_com_h265decode_H265Decoder_decode
        (JNIEnv *, jobject, jbyteArray, jint, jlong);


JNIEXPORT jboolean JNICALL Java_ican_ytx_com_h265decode_H265Decoder_encode
        (JNIEnv *, jobject, jbyteArray, jint, jlong);
/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    decodeBuffer
 * Signature: (Ljava/nio/ByteBuffer;IJ)Z
 */
JNIEXPORT jboolean JNICALL Java_ican_ytx_com_h265decode_H265Decoder_decodeBuffer
        (JNIEnv *, jobject, jobject, jint, jlong);

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    getWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ican_ytx_com_h265decode_H265Decoder_getWidth
        (JNIEnv *, jobject);

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    getHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ican_ytx_com_h265decode_H265Decoder_getHeight
        (JNIEnv *, jobject);

/*
 * Class:     ican_ytx_com_h265decode_H265Decoder
 * Method:    toTexture
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_ican_ytx_com_h265decode_H265Decoder_toTexture
        (JNIEnv *, jobject, jint, jint, jint);

#ifdef __cplusplus
}
#endif

#endif //H265DECODE_ANDROIDH265DECODER_H
