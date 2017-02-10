package com.teameight.vhud;

import android.app.Activity;
import android.content.Context;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.view.Menu;
import android.widget.TextView;

public class Dashboard extends Activity {

	public float speed;
	public TextView speedometer;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.dashboard);
		
		LocationManager lm = (LocationManager)getSystemService(Context.LOCATION_SERVICE); 
        //Location location = lm.getLastKnownLocation(LocationManager.GPS_PROVIDER);
		
		speedometer = (TextView) findViewById(R.id.textView1);

        final LocationListener locationListener = new LocationListener() {
            public void onLocationChanged(Location location) {
            	speed = location.getSpeed();
            	speedometer.setText(speed + " m/s");
            	if (speed < 10.0 ){
            		speedometer.setTextColor(Color.GREEN);
            	}
            	else if ( speed < 40.0 ) {
            		speedometer.setTextColor(Color.YELLOW);
            	}
            	else if ( speed < 100.0 ) {
            		speedometer.setTextColor(Color.RED);
            	}
            }

            public void onProviderDisabled(String arg0) {

            }

            public void onProviderEnabled(String arg0) {

            }

            public void onStatusChanged(String arg0, int arg1, Bundle arg2) {

            }
        };

        lm.requestLocationUpdates(LocationManager.GPS_PROVIDER, 500, 1, locationListener);
	}
	
	@Override
    protected void onStart() {
        super.onStart();
        // The activity is about to become visible.
    }
    @Override
    protected void onResume() {
        super.onResume();
        // The activity has become visible (it is now "resumed").
    }
    @Override
    protected void onPause() {
        super.onPause();
        // Another activity is taking focus (this activity is about to be "paused").
    }
    @Override
    protected void onStop() {
        super.onStop();
        // The activity is no longer visible (it is now "stopped")
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        // The activity is about to be destroyed.
    }

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

}
