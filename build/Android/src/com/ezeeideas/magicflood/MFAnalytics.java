package com.ezeeideas.magicflood;

import com.google.android.gms.analytics.HitBuilders;
import com.google.android.gms.analytics.Tracker;

import android.app.Activity;

public class MFAnalytics 
{
	public static void trackEvent(Activity activity, String category, String action, String label)
	{
		trackEvent(activity, category, action, label, 1); //set default value as 1, when not specified
	}
	
	public static void trackEvent(Activity activity, String category, String action, String label, int value)
	{
		MFApp app = (MFApp) activity.getApplication();
		Tracker t = app.getAnalyticsTracker();
		
		t.send(new HitBuilders.EventBuilder()
			.setCategory(category)
			.setAction(action)
			.setLabel(label)
			.setValue(value)
			.build());
	}
	
	/**
	 * CAUTION: Don't use Values as 0
	 */
	
	/**
	 * Categories
	 */
	public static final String ANALYTICS_CATEGORY_GAME_EASY = "easy_game"; // Game Screen
	public static final String ANALYTICS_CATEGORY_GAME_MEDIUM = "medium_game"; // Game Screen
	public static final String ANALYTICS_CATEGORY_GAME_HARD = "hard_game"; // Game Screen
	public static final String ANALYTICS_CATEGORY_MAIN_VIEW = "main_view"; // Main Screen
	public static final String ANALYTICS_CATEGORY_STORE = "store"; // Store / IAP
	
	/**
	 * Actions
	 */
	public static final String ANALYTICS_ACTION_BUTTON_PRESS = "button_press";
	public static final String ANALYTICS_ACTION_GAME_ENDED= "game_ended";
	
	/**
	 * Actions - IAP Related
	 */
	public static final String ANALYTICS_ACTION_IAP_STARTED = "iap_started";
	public static final String ANALYTICS_ACTION_IAP_CANCELLED = "iap_cancelled";
	public static final String ANALYTICS_ACTION_IAP_COMPLETED = "iap_completed";
	public static final String ANALYTICS_ACTION_IAP_FAILED = "iap_failed"; //failed for some reason
	
	/**
	 * Labels - Buttons - Main Screen
	 */
	public static final String ANALYTICS_LABEL_EASY_BUTTON = "easy_button";
	public static final String ANALYTICS_LABEL_MEDIUM_BUTTON = "medium_button";
	public static final String ANALYTICS_LABEL_HARD_BUTTON = "hard_button";
	public static final String ANALYTICS_LABEL_ABOUT_BUTTON = "about_button";
	public static final String ANALYTICS_LABEL_HELP_BUTTON = "help_button";
	public static final String ANALYTICS_LABEL_STORE_BUTTON = "store_button";
	
	/**
	 * Labels - Buttons - Game Screen
	 */
	public static final String ANALYTICS_LABEL_SOUND_ON = "sound_on";
	public static final String ANALYTICS_LABEL_SOUND_OFF = "sound_off";
	public static final String ANALYTICS_LABEL_MENU_BUTTON = "menu_button";
	public static final String ANALYTICS_LABEL_BACK_BUTTON = "back_button";
	public static final String ANALYTICS_LABEL_COLOR_BUTTON = "color_button";
	public static final String ANALYTICS_LABEL_MAIN_MENU_BUTTON = "main_menu_button";
	public static final String ANALYTICS_LABEL_NEW_GAME_BUTTON = "new_game_button";
	public static final String ANALYTICS_LABEL_NEXT_GAME_BUTTON = "next_game_button";
	public static final String ANALYTICS_LABEL_RESUME_GAME_BUTTON = "resume_game_button";
	
	/**
	 * Labels - Game Ended
	 */
	public static final String ANALYTICS_LABEL_GAME_ENDED_SUCCESS = "game_ended_success";
	public static final String ANALYTICS_LABEL_GAME_ENDED_FAILURE = "game_ended_failure";
	
	/**
	 * Values - Store Synchronization Status
	 */
	public static final int ANALYTICS_VALUE_STORE_SYNCHRONIZED = 1; //Store is synchronized
	public static final int ANALYTICS_VALUE_STORE_NOT_SYNCHRONIZED = 2; //Store not synchronized
}
