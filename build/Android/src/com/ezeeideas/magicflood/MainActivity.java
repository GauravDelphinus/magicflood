package com.ezeeideas.magicflood;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button easyButton = (Button)findViewById(R.id.eazy_game_button);
        easyButton.setOnClickListener(this);
        Button mediumButton = (Button)findViewById(R.id.medium_game_button);
        mediumButton.setOnClickListener(this);
        Button hardButton = (Button)findViewById(R.id.hard_game_button);
        hardButton.setOnClickListener(this);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }


	@Override
	public void onClick(View arg0) {
		// TODO Auto-generated method stub
		Intent i;
		switch (arg0.getId())
		{
		case R.id.eazy_game_button:		
	    	i = new Intent(this, MFGameActivity.class); 	
	    	i.putExtra(MFGameConstants.GAME_LEVEL_KEY, MFGameConstants.GAME_LEVEL_EASY);
	    	startActivity(i);
			break;
		case R.id.medium_game_button:
	    	i = new Intent(this, MFGameActivity.class); 	
	    	i.putExtra(MFGameConstants.GAME_LEVEL_KEY, MFGameConstants.GAME_LEVEL_MEDIUM);
	    	startActivity(i);
			break;
		case R.id.hard_game_button:
	    	i = new Intent(this, MFGameActivity.class); 	
	    	i.putExtra(MFGameConstants.GAME_LEVEL_KEY, MFGameConstants.GAME_LEVEL_HARD);
	    	startActivity(i);
			break;
		}
	}
}
