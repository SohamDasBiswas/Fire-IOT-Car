package com.example.iotcar;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatDelegate;
import androidx.appcompat.widget.SwitchCompat;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.SeekBar;

import com.google.android.material.slider.Slider;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class MainActivity extends AppCompatActivity {
    DatabaseReference RootRef;
    Button left1, left2, left3, forward, Stop, Reverse, FwRight, Right, ReRight;
    SwitchCompat lightSw;
    Slider slider;
    SharedPreferences SharedPreferences=null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        RootRef = FirebaseDatabase.getInstance().getReference();

        lightSw = findViewById(R.id.lightSw);

        slider = (Slider) findViewById(R.id.slider);

        left1 =(Button) findViewById(R.id.left1);
        left2 =(Button) findViewById(R.id.left2);
        left3 =(Button) findViewById(R.id.left3);

        forward =(Button) findViewById(R.id.forward);
        Stop =(Button) findViewById(R.id.Stop);
        Reverse =(Button) findViewById(R.id.Reverse);

        FwRight =(Button) findViewById(R.id.FwRight);
        Right =(Button) findViewById(R.id.Right);
        ReRight =(Button) findViewById(R.id.ReRight);

        SharedPreferences =getSharedPreferences( "night", 0);
        Boolean booleanValue = SharedPreferences.getBoolean("night_mode",true);
        if (booleanValue) {
            AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_YES);
            lightSw.setChecked(true);
        }
        lightSw.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener(){
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked){
                if(isChecked){
                    AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_YES);
                    lightSw.setChecked(true);
                    SharedPreferences.Editor editor = SharedPreferences.edit();
                    editor.putBoolean("night_mode", true);
                    editor.commit();
                }else {
                    AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_NO);
                    lightSw.setChecked(false);
                    SharedPreferences.Editor editor = SharedPreferences.edit();
                    editor.putBoolean("night_mode", false);
                    editor.commit();
                }
            }
        });
        left1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RootRef.child("car").child("move").setValue(11);

            }
        });
        left2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RootRef.child("car").child("move").setValue(21);

            }
        });
        left3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RootRef.child("car").child("move").setValue(31);

            }
        });
        forward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RootRef.child("car").child("move").setValue(12);

            }
        });
        Stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RootRef.child("car").child("move").setValue(0);

            }
        });
        Reverse.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RootRef.child("car").child("move").setValue(32);

            }
        });
        FwRight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RootRef.child("car").child("move").setValue(13);

            }
        });
        Right.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RootRef.child("car").child("move").setValue(23);

            }
        });
        ReRight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RootRef.child("car").child("move").setValue(33);

            }
        });
        slider.addOnSliderTouchListener(new Slider.OnSliderTouchListener(){

            @Override
            public void onStartTrackingTouch(Slider slider){

            }
            @Override
            public void onStopTrackingTouch(Slider slider){
                float value= slider.getValue();
                int a = (int)value;
                RootRef.child("car").child("speed").setValue(a*100);
            }
        });

    }
}