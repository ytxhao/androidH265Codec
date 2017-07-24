package com.decoder.xiaomi;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private int mYUVTextures[];


    private Button btEncode;
    private Button btDecode;

    private H265Decoder mH265Decoder;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btEncode = (Button) findViewById(R.id.bt_encode);
        btDecode = (Button) findViewById(R.id.bt_decode);

        btEncode.setOnClickListener(this);
        btDecode.setOnClickListener(this);

        mYUVTextures = new int[3];
        mH265Decoder = new H265Decoder();

    }

    @Override
    public void onClick(View v) {

        int id = v.getId();

        switch (id){
            case R.id.bt_decode:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        mH265Decoder.decode(null,0,0);
                    }
                }).start();

                break;

            case R.id.bt_encode:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
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
                break;
        }
    }
}
