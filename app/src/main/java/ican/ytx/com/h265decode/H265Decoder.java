/*
 *  H264Decoder.java
 *  JNI H.264 video decoder module 
 *
 *  Copyright (c) 2012, Dropcam
 *  All rights reserved.
 *  
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met: 
 *  
 *  1. Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer. 
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution. 
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  
 */

package ican.ytx.com.h265decode;

//import android.graphics.Bitmap;

import java.nio.ByteBuffer;

public class H265Decoder {
    private int nativeId = 0;

    private static native void nativeInit();

    static {
        System.loadLibrary("x265");
        System.loadLibrary("h265decoder");


        System.loadLibrary("avutil-55");
        System.loadLibrary("swresample-2");
        System.loadLibrary("swscale-4");
        System.loadLibrary("avcodec-57");
        System.loadLibrary("avformat-57");
        System.loadLibrary("avfilter-6");

        nativeInit();
    }
    public H265Decoder(){
        init();
    }

    private native void init();

    public native void release();

    public native boolean decode(byte[] data, int numBytes, long packetPTS);

    public native boolean encode(byte[] data, int numBytes, long packetPTS);

    public native boolean decodeBuffer(ByteBuffer data, int numBytes, long packetPTS);

    public native int getWidth();

    public native int getHeight();

    //public native int toBitmap(Bitmap bitmap);

    public native int toTexture(int textureY, int textureU, int textureV);
    
    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        release();
    }

}
