package com.example.hthieu.final_project;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

public class Main3Activity extends AppCompatActivity {
    int match_number;
    ImageView img1, img2, img3, img4, img5, img6, img7;
    Button button_back;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main3);

        Bundle b = getIntent().getExtras();
        match_number = b.getInt("id");


        button_back = (Button) findViewById(R.id.button5);
        button_back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent new_act = new Intent(getApplicationContext(), Main2Activity.class);
                new_act.putExtra("id", match_number);
                startActivity(new_act);
            }
        });
        img1 = (ImageView) findViewById(R.id.image1);
        img2 = (ImageView) findViewById(R.id.image2);
        img3 = (ImageView) findViewById(R.id.image3);
        img4 = (ImageView) findViewById(R.id.image4);
        img5 = (ImageView) findViewById(R.id.image5);
        img6 = (ImageView) findViewById(R.id.image6);
        img7 = (ImageView) findViewById(R.id.image7);
       loadImage();


    }


    private void loadImage(){

        switch (match_number){
            case 0:
                break;
            case 1:
                break;
            case 2:

                img1.setImageDrawable(getDrawable(R.drawable.union_1));
                img2.setImageDrawable(getDrawable(R.drawable.union_2));
                img3.setImageDrawable(getDrawable(R.drawable.union_3));
                img4.setImageDrawable(getDrawable(R.drawable.union_4));
                img5.setImageDrawable(getDrawable(R.drawable.union_5));
                img6.setImageDrawable(getDrawable(R.drawable.union_6));
                img7.setImageDrawable(getDrawable(R.drawable.union_7));
                break;
            case 3:
                img1.setImageDrawable(getDrawable(R.drawable.beckman_1));
                img2.setImageDrawable(getDrawable(R.drawable.beckman_2));
                img3.setImageDrawable(getDrawable(R.drawable.beckman_3));
                img4.setImageDrawable(getDrawable(R.drawable.beckman_4));
                img5.setImageDrawable(getDrawable(R.drawable.beckman_5));
                img6.setImageDrawable(getDrawable(R.drawable.beckman_6));
                img7.setImageDrawable(getDrawable(R.drawable.beckman_7));
                break;
            case 4:
                img1.setImageDrawable(getDrawable(R.drawable.eng_lib_1));
                img2.setImageDrawable(getDrawable(R.drawable.eng_lib_2));
                img3.setImageDrawable(getDrawable(R.drawable.eng_lib_3));
                img4.setImageDrawable(getDrawable(R.drawable.eng_lib_4));
                img5.setImageDrawable(getDrawable(R.drawable.eng_lib_5));
                img6.setImageDrawable(getDrawable(R.drawable.eng_lib_6));
                img7.setImageDrawable(getDrawable(R.drawable.eng_lib_7));
                break;
            case 5:
                img1.setImageDrawable(getDrawable(R.drawable.panda_1));
                img2.setImageDrawable(getDrawable(R.drawable.panda_2));
                img3.setImageDrawable(getDrawable(R.drawable.panda_3));
                img4.setImageDrawable(getDrawable(R.drawable.panda_4));
                img5.setImageDrawable(getDrawable(R.drawable.panda_5));
                img6.setImageDrawable(getDrawable(R.drawable.panda_6));
                img7.setImageDrawable(getDrawable(R.drawable.panda_7));
                break;
            case 6:
//rsz_ece_2
                break;
            case 7:
//                img1.setImageDrawable(getDrawable(R.drawable.rsz_ece_2));
//                img2.setImageDrawable(getDrawable(R.drawable.rsz_ece_2));
//                img3.setImageDrawable(getDrawable(R.drawable.rsz_ece_2));
//                img4.setImageDrawable(getDrawable(R.drawable.rsz_ece_2));
//                img5.setImageDrawable(getDrawable(R.drawable.rsz_ece_2));
//                img6.setImageDrawable(getDrawable(R.drawable.rsz_ece_2));
//                img7.setImageDrawable(getDrawable(R.drawable.rsz_ece_2));

                img1.setImageDrawable(getDrawable(R.drawable.ece_1));
                img2.setImageDrawable(getDrawable(R.drawable.ece_2));
                img3.setImageDrawable(getDrawable(R.drawable.ece_3));
                img4.setImageDrawable(getDrawable(R.drawable.ece_4));
                img5.setImageDrawable(getDrawable(R.drawable.ece_5));
                img6.setImageDrawable(getDrawable(R.drawable.ece_6));
                img7.setImageDrawable(getDrawable(R.drawable.ece_7));
                break;
            default:
        }

    }


}
