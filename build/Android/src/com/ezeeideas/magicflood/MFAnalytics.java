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
	public static final String ANALYTICS_CATEGORY_GAME = "game_play"; // Game Screen
	public static final String ANALYTICS_CATEGORY_IAP = "iap"; // IAP
	
	/**
	 * Actions
	 */
	public static final String ANALYTICS_ACTION_BUTTON_PRESS = "button_press";
	public static final String ANALYTICS_ACTION_GAME_ENDED= "game_ended";
	public static final String ANALYTICS_ACTION_GAME_ACTION = "game_action"; //game action other than the above two
	
	/**
	 * Actions - IAP Related
	 */
	public static final String ANALYTICS_ACTION_IAP_STARTED = "iap_purchase_started";
	public static final String ANALYTICS_ACTION_IAP_CANCELLED = "iap_purchase_cancelled";
	public static final String ANALYTICS_ACTION_IAP_COMPLETED = "iap_purchase_completed";
	public static final String ANALYTICS_ACTION_IAP_FAILED = "iap_purchase_failed"; //failed for some reason
	public static final String ANALYTICS_ACTION_IAP_NOT_CONNECTED = "iap_not_connected";
	public static final String ANALYTICS_ACTION_IAP_CONSUME_STARTED = "iap_consume_started";
	public static final String ANALYTICS_ACTION_IAP_CONSUME_FAILED = "iap_consume_failed";
	public static final String ANALYTICS_ACTION_IAP_CONSUME_COMPLETED = "iap_consume_completed";
	public static final String ANALYTICS_ACTION_IAP_QUERY_STARTED = "iap_query_started";
	public static final String ANALYTICS_ACTION_IAP_QUERY_FAILED = "iap_query_failed";
	public static final String ANALYTICS_ACTION_IAP_QUERY_COMPLETED = "iap_query_completed";
	
	/**
	 * Labels - Buttons - Main Screen
	 */
	public static final String ANALYTICS_LABEL_PLAY_BUTTON = "play_button";
	public static final String ANALYTICS_LABEL_ABOUT_BUTTON = "about_button";
	public static final String ANALYTICS_LABEL_HELP_BUTTON = "help_button";
	
	/**
	 * Labels - Buttons - Game Screen
	 */
	public static final String ANALYTICS_LABEL_SOUND_ON = "sound_on";
	public static final String ANALYTICS_LABEL_SOUND_OFF = "sound_off";
	public static final String ANALYTICS_LABEL_MENU_BUTTON = "menu_button";
	public static final String ANALYTICS_LABEL_BACK_BUTTON = "back_button";
	public static final String ANALYTICS_LABEL_COLOR_BUTTON = "color_button";
	public static final String ANALYTICS_LABEL_VIEW_LEVELS_BUTTON = "view_levels_button";
	public static final String ANALYTICS_LABEL_NEW_GAME_BUTTON = "new_game_button";
	public static final String ANALYTICS_LABEL_NEXT_GAME_BUTTON = "next_game_button";
	public static final String ANALYTICS_LABEL_REPLAY_GAME_BUTTON = "replay_game_button";
	public static final String ANALYTICS_LABEL_ADD_COINS_BUTTON = "add_coins_button";
	public static final String ANALYTICS_LABEL_ADD_MOVES_BUTTON = "add_moves_button";
	public static final String ANALYTICS_LABEL_ADD_STAR_BUTTON = "add_star_button";
	public static final String ANALYTICS_LABEL_ADD_HURDLE_SMASHER_BUTTON = "add_hurdle_smasher_button";
	public static final String ANALYTICS_LABEL_REMOVE_ADS_BUTTON = "remove_ads_button";
	public static final String ANALYTICS_LABEL_PLAY_ON_BUTTON = "play_on_button";
	public static final String ANALYTICS_LABEL_END_GAME_BUTTON = "end_game_button";
	public static final String ANALYTICS_LABEL_CANCEL_GAME_FAILED_DIALOG = "cancel_game_failed_dialog";
	public static final String ANALYTICS_LABEL_CANCEL_GAME_SUCCESS_DIALOG = "cancel_game_success_dialog";
	public static final String ANALYTICS_LABEL_CANCEL_GAME_MENU_DIALOG = "cancel_game_menu_dialog";
	public static final String ANALYTICS_LABEL_CANCEL_ADD_COINS_DIALOG = "cancel_add_coins_dialog";
	public static final String ANALYTICS_LABEL_CANCEL_ADD_MOVES_DIALOG = "cancel_add_moves_dialog";
	public static final String ANALYTICS_LABEL_CANCEL_ADD_STAR_DIALOG = "cancel_add_star_dialog";
	public static final String ANALYTICS_LABEL_CANCEL_ADD_HURDLE_SMASHER_DIALOG = "cancel_add_hurdle_smasher_dialog";
	public static final String ANALYTICS_LABEL_CANCEL_REMOVE_ADS_DIALOG = "cancel_remove_ads_dialog";
	public static final String ANALYTICS_LABEL_REDEEM_COINS_FOR_MOVES_BUTTON = "redeem_coins_for_moves";
	public static final String ANALYTICS_LABEL_REDEEM_COINS_FOR_STAR_BUTTON = "redeem_coins_for_star";
	public static final String ANALYTICS_LABEL_REDEEM_COINS_FOR_HURDLE_SMASHER = "redeem_coins_for_hurdle_smasher";
	
	/**
	 * Labels - Game Ended
	 */
	public static final String ANALYTICS_LABEL_GAME_ENDED_SUCCESS = "game_ended_success";
	public static final String ANALYTICS_LABEL_GAME_ENDED_FAILURE = "game_ended_failure";
	
	/**
	 * Labels - Game Action
	 */
	public static final String ANALYTICS_LABEL_GAME_ACTION_NEW_GAME_STARTED = "new_game_started";
	public static final String ANALYTICS_LABEL_GAME_ACTION_COINS_REDEEMED_FOR_MOVES = "coins_redeemed_for_moves";
	public static final String ANALYTICS_LABEL_GAME_ACTION_COINS_REDEEMED_FOR_STAR = "coins_redeemed_for_star";
	public static final String ANALYTICS_LABEL_GAME_ACTION_COINS_REDEEMED_FOR_HURDLE_SMASHER = "coins_redeemed_for_hurdle_smasher";
	
	/**
	 * Labels - Store Synchronization Status
	 */
	public static final String ANALYTICS_VALUE_STORE_NOT_CONNECTED_GENERAL = "iap_not_connected_general";
	public static final String ANALYTICS_VALUE_STORE_NOT_CONNECTED_WHILE_ADDING_COINS = "iap_not_connected_while_adding_coins";
	public static final String ANALYTICS_VALUE_STORE_NOT_CONNECTED_WHILE_ADDING_MOVES = "iap_not_connected_while_adding_moves";
	public static final String ANALYTICS_VALUE_STORE_NOT_CONNECTED_WHILE_ADDING_STAR = "iap_not_connected_while_adding_star";
	public static final String ANALYTICS_VALUE_STORE_NOT_CONNECTED_WHILE_ADDING_HURDLE_SMASHER = "iap_not_connected_while_adding_hurdle_smasher";
	public static final String ANALYTICS_VALUE_STORE_NOT_CONNECTED_WHILE_REMOVING_ADS = "iap_not_connected_while_removing_ads";
	
	/**
	 * Labels - IAP
	 */
	public static final String ANALYTICS_VALUE_IAP_QUERY_FAILED_RESULT_FAILURE = "iap_query_failed_result_failure";
	public static final String ANALYTICS_VALUE_IAP_QUERY_FAILED_SKU_NULL = "iap_query_failed_sku_null";
}
