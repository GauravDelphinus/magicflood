package com.ezeeideas.magicflood;

import com.google.android.gms.analytics.GoogleAnalytics;
import com.google.android.gms.analytics.Tracker;

import android.app.Application;

public class MFApp extends Application 
{
	public synchronized Tracker getAnalyticsTracker()
	{
		GoogleAnalytics analytics = GoogleAnalytics.getInstance(this);
		if (mGoogleAnalyticsTracker == null)
		{
			mGoogleAnalyticsTracker = analytics.newTracker(MFConstants.APP_ANALYTICS_TRACKING_ID);
		}
		
		return mGoogleAnalyticsTracker;
	}

	private Tracker mGoogleAnalyticsTracker;

}
