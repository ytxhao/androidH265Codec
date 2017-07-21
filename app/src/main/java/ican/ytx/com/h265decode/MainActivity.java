package ican.ytx.com.h265decode;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    int mYUVTextures[];


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mYUVTextures = new int[3];

        new Thread(new Runnable() {
            @Override
            public void run() {
                H265Decoder mH265Decoder = new H265Decoder();
                mH265Decoder.encode(null,0,0);
//                if(mH265Decoder.decode()){
//                    int ret = mH265Decoder.toTexture(mYUVTextures[0], mYUVTextures[1], mYUVTextures[2]);
//                    if (ret < 0) {
//                        return;
//                    }
//
//                }

            }
        }).start();
    }
}
