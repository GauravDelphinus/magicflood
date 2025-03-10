package com.ezeeideas.magicflood;

/**
 * Note: All constants in this class must match the constants in MFGridInterface.h
 * It needs to be in sync with MFGridInterface.h at all times
 * 
 * @author anukrity
 *
 */
public class MFGameConstants 
{	
	/**
	 * Game Levels
	 */
	public static final int GAME_LEVEL_EASY = 0;
	public static final int GAME_LEVEL_MEDIUM = 1;
	public static final int GAME_LEVEL_HARD = 2;
	
	/**
	 * Results of a Move
	 */
	public static final int RESULT_CONTINUE = 0;
	public static final int RESULT_SUCCESS = 1;
	public static final int RESULT_FAILED = 2;
	
	/**
	 * Color values stored in the Grid
	 */
	public static final int GRID_OBSTACLE = 0;
	public static final int GRID_SPACE = '.';
	
	public static final int GRID_COLOR_RED = 1;
	public static final int GRID_COLOR_GREEN = 2;
	public static final int GRID_COLOR_BLUE = 3;
	public static final int GRID_COLOR_YELLOW = 4;
	public static final int GRID_COLOR_ORANGE = 5;
	public static final int GRID_COLOR_CYAN = 6;
	
	public static final int GRID_NUM_COLORS = 6;
	
	/**
	 * In-App Purchase Product IDs
	 */
	public static final int IAP_ALACARTE_1 = 1;
	public static final int IAP_ALACARTE_2 = 2;
	public static final int IAP_ALACARTE_3 = 3;
	public static final int IAP_ALACARTE_4 = 4;
	public static final int IAP_ALACARTE_5 = 5;
	public static final int IAP_ALACARTE_6 = 6;
	public static final int IAP_COMBO_1 = 7;
	public static final int IAP_COMBO_2 = 8;
	public static final int IAP_COMBO_3 = 9;
	public static final int IAP_COMBO_4 = 10;
	//public static final int IAP_REMOVE_ADS = 11;
	
	/**
	 * In-App Purchase Product String IDs.
	 */
	public static final String IAP_REMOVE_ADS = "iap_remove_ads";
	public static final String IAP_COINS_FIRST = "iap_add_coins_first";
	public static final String IAP_COINS_SECOND = "iap_add_coins_second";
	public static final String IAP_COINS_THIRD = "iap_add_coins_third";
	public static final String IAP_COINS_FOURTH = "iap_add_coins_fourth";
	
	// Bundle Keys
	public static final String IAP_QUERY_SKUS_KEY = "DETAILS_LIST"; //key used to query the skus from the bundle
	public static final String IAP_QUERY_DETAILS_KEY = "DETAILS_LIST"; //key used to query details of sku from the bundle
	public static final String IAP_RESPONSE_CODE_KEY = "RESPONSE_CODE"; // key used to get response code from bundle
	public static final String IAP_PURCHASE_DATA_KEY = "INAPP_PURCHASE_DATA_LIST"; // key used to query the purchase related data
	
    // Billing response codes
    public static final int BILLING_RESPONSE_RESULT_OK = 0;
    public static final int BILLING_RESPONSE_RESULT_USER_CANCELED = 1;
    public static final int BILLING_RESPONSE_RESULT_BILLING_UNAVAILABLE = 3;
    public static final int BILLING_RESPONSE_RESULT_ITEM_UNAVAILABLE = 4;
    public static final int BILLING_RESPONSE_RESULT_DEVELOPER_ERROR = 5;
    public static final int BILLING_RESPONSE_RESULT_ERROR = 6;
    public static final int BILLING_RESPONSE_RESULT_ITEM_ALREADY_OWNED = 7;
    public static final int BILLING_RESPONSE_RESULT_ITEM_NOT_OWNED = 8;
    
    // SKU Keys
    public static final String IAP_PRODUCT_ID = "productId";
    public static final String IAP_PRODUCT_TYPE = "type";
    public static final String IAP_PRODUCT_PRICE = "price";
    public static final String IAP_PRODUCT_PRICE_CURRENCY_CODE = "price_currency_code"; // refer http://en.wikipedia.org/wiki/ISO_4217#Active_codes
    public static final String IAP_PRODUCT_TITLE = "title";
    public static final String IAP_PRODUCT_DESCRIPTION = "description";
    
    public static final String IAP_PURCHASE_STATE = "purchaseState";
    
	/* Android specific constants */
	/**
	 * Keys
	 */
	public static final String GAME_LEVEL_KEY = "level";
	public static final String PROMPT_USER_TO_STORE = "prompt_user_to_store";
	public static final String NUM_LEVELS_KEY = "num_levels";
	
	/**
	 * Names
	 */
	public static final String NATIVE_LIBRARY_NAME = "magicflood";
	
	/**
	 * Package name
	 */
	public static String PACKAGE_NAME;
	
	/**
	 * Preferences.
	 */
	public static final String PREFERENCE_KEY = "user_prefs";
	public static final String PREFERENCE_SOUND = "preference_sound";
	public static final String PREFERENCE_TOTAL_COINS_EARNED = "total_coins_earned";
	public static final String PREFERENCE_ADS_REMOVED = "ads_removed";
	public static final String PREFERENCE_LAST_UNLOCKED_LEVEL = "last_unlocked_level";
	public static final String PREFERENCE_LAST_PLAYED_LEVEL = "last_played_level";
	public static final String PREFERENCE_LAST_COMPLETED_LEVEL = "last_completed_level";
	public static final String PREFERENCE_STARS_UNLOCKED = "stars_unlocked";
	public static final String PREFERENCE_HURDLE_SMASHERS_UNLOCKED = "hurdle_smashers_unlocked";
	public static final String PREFERENCE_BRIDGES_UNLOCKED = "bridges_unlocked";
	public static final String PREFERENCE_TOTAL_STARS_EARNED = "total_stars_earned";
	public static final String PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED = "total_hurdle_smashers_earned";
	public static final String PREFERENCE_TOTAL_BRIDGES_EARNED = "total_bridges_earned";
	public static final String PREFERENCE_STAR_PLACEMENT_COUNT = "star_placement_count";
	public static final String PREFERENCE_HURDLE_SMASHER_PLACEMENT_COUNT = "hurdle_smasher_placement_count";
	public static final String PREFERENCE_BRIDGE_PLACEMENT_COUNT = "bridge_placement_count";
	
	/**
	 * Default Preferences
	 */
	public static final int DEFAULT_LAST_UNLOCKED_LEVEL = 1;
	public static final int DEFAULT_LAST_PLAYED_LEVEL = 1;
	public static final int DEFAULT_LAST_COMPLETED_LEVEL = 0;
	public static final int INITIAL_COINS_ALLOCATED = 100;
	public static final int INITIAL_STARS_ALLOCATED = 2;
	public static final int INITIAL_HURDLE_SMASHERS_ALLOCATED = 2;
	public static final int INITIAL_BRIDGES_ALLOCATED = 2;
	
	/**
	 * Game Constants
	 */
	public static final int MOVES_ADD_INCREMENT = 5;
	/** Number of times to show the lifeline placement dialogs **/
	public static final int MAX_STAR_PLACEMENT_DIALOG_COUNT = 2;
	public static final int MAX_HURDLE_SMASHER_PLACEMENT_DIALOG_COUNT = 2;
	public static final int MAX_BRIDGE_PLACEMENT_DIALOG_COUNT = 2;
}
