package com.ezeeideas.magicflood;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageButton;

public class MFAboutActivity extends Activity implements OnClickListener
{
	@Override
    protected void onCreate(Bundle savedInstanceState) 
	{
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_about);
        
        ImageButton facebookButton = (ImageButton) findViewById(R.id.facebook_button);
        facebookButton.setOnClickListener(this);
        
        ImageButton feedbackButton = (ImageButton) findViewById(R.id.feedback_button);
        feedbackButton.setOnClickListener(this);
        
        ImageButton rateButton = (ImageButton) findViewById(R.id.rate_app_button);
        rateButton.setOnClickListener(this);
	}
	
    @Override
    public void onDestroy() 
    {
        super.onDestroy(); 
    }

	@Override
	public void onClick(View v) 
	{
		if (v.getId() == R.id.rate_app_button)
    	{    		
			try 
			{
			    startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("market://details?id=" + MFConstants.APP_PNAME)));
			} catch (android.content.ActivityNotFoundException anfe) {
			    startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("http://play.google.com/store/apps/details?id=" + MFConstants.APP_PNAME)));
			}
    	}
		else if (v.getId() == R.id.feedback_button)
		{    		
			Intent emailIntent = new Intent(Intent.ACTION_SENDTO, Uri.fromParts(
					"mailto",MFConstants.SUPPORT_EMAIL, null));
			emailIntent.putExtra(Intent.EXTRA_SUBJECT, getResources().getString(R.string.support_email_subject));
			startActivity(Intent.createChooser(emailIntent, getResources().getString(R.string.support_email_title)));
		}
		else if (v.getId() == R.id.facebook_button)
		{    		
			Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(MFConstants.FACEBOOK_PAGE_URL));
			startActivity(browserIntent);
		}		
	}
}