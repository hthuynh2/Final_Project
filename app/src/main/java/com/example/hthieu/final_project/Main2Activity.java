package com.example.hthieu.final_project;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class Main2Activity extends AppCompatActivity {

    Button button_back;
    TextView tv, tv1;
    int match_number;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        Bundle b = getIntent().getExtras();
        match_number = b.getInt("id");

        tv = (TextView) findViewById(R.id.textView);
        tv1 = (TextView) findViewById(R.id.textView2);
        button_back = (Button) findViewById(R.id.button2);
        button_back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(getApplicationContext(), MainActivity.class));
            }
        });
        loadText();
    }

    private void loadText(){
        String s ;

        switch (match_number){
            case 0:
                s = getString(R.string.elephant);
                tv1.setText("ELEPHANT");
                break;
            case 1:
                s = getString(R.string.eng_hall );
                tv1.setText("ENGINEERING HALL");
                break;
            case 2:
                s = getString(R.string.union);
                tv1.setText("ILLINOIS UNION");
                break;
            case 3:
                s = getString(R.string.beckman);
                tv1.setText("BECKMAN INSTITUTE");
                break;
            case 4:
                s = getString(R.string.eng_lib);
                tv1.setText("ENGINEERING LIBRARY");
                break;
            case 5:
                s = getString(R.string.panda_express);
                tv1.setText("PANDA EXPRESS");
                break;
            case 6:
                s = getString(R.string.csl);
                tv1.setText("COORDINATED SCIENCE LAB");
                break;
            case 7:
                s = getString(R.string.eceb);
                tv1.setText("ECE BUILDING");
                break;
            default:
                tv1.setText("");
                s = "";
        }

        tv.setMovementMethod(new ScrollingMovementMethod());
        tv.setText(s);
    }


}


