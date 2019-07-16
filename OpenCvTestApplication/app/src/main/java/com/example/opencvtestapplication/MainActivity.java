package com.example.opencvtestapplication;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private ImageView resultImageView;
    private final static int ER_ZHI_HUA=1;
    private final static int PENG_ZHANG=2;
    private final static int TI_QU_ID=3;
    public final static String TAG = "OpenCvTest";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        resultImageView = findViewById(R.id.id_img_result);
    }

    public void onClick(View view){
        int id = view.getId();
        int type = TI_QU_ID;
        if(id==R.id.er_zhi_hua){
            type = ER_ZHI_HUA;
        }else if (id == R.id.peng_zhang){
            type = PENG_ZHANG;
        }
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(),R.drawable.test_id_card);
        Bitmap resultBitmap = findIdNumber(bitmap, Bitmap.Config.ARGB_8888,type);
        bitmap.recycle();
        resultImageView.setImageBitmap(resultBitmap);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    private native Bitmap findIdNumber(Bitmap bitmap, Bitmap.Config config,int type);
}
