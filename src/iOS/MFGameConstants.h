//
//  MFConstants.h
//  Magic Flood
//
//  Created by Anukrity Jain on 4/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#ifndef Magic_Flood_MFConstants_h
#define Magic_Flood_MFConstants_h

/**
 * Preferences.  Synced with Android java version in MFGameConstants.java
 */

#define PREFERENCE_KEY "user_prefs"
#define PREFERENCE_SOUND "preference_sound"
#define PREFERENCE_TOTAL_COINS_EARNED "total_coins_earned"
#define PREFERENCE_ADS_REMOVED "ads_removed"
#define PREFERENCE_LAST_UNLOCKED_LEVEL "last_unlocked_level"
#define PREFERENCE_LAST_PLAYED_LEVEL "last_played_level"
#define PREFERENCE_LAST_COMPLETED_LEVEL "last_completed_level"
#define PREFERENCE_STARS_UNLOCKED "stars_unlocked"
#define PREFERENCE_HURDLE_SMASHERS_UNLOCKED "hurdle_smashers_unlocked"
#define PREFERENCE_BRIDGES_UNLOCKED "bridges_unlocked"
#define PREFERENCE_TOTAL_STARS_EARNED   "total_stars_earned"
#define PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED "total_hurdle_smashers_earned"
#define PREFERENCE_TOTAL_BRIDGES_EARNED "total_bridges_earned"
#define PREFERENCE_STAR_PLACEMENT_COUNT "star_placement_count"
#define PREFERENCE_HURDLE_SMASHER_PLACEMENT_COUNT "hurdle_smasher_placement_count"
#define PREFERENCE_BRIDGE_PLACEMENT_COUNT   "bridge_placement_count"

/** Default Preferences **/
#define DEFAULT_LAST_UNLOCKED_LEVEL 1
#define DEFAULT_LAST_PLAYED_LEVEL 1
#define DEFAULT_LAST_COMPLETED_LEVEL 0
#define INITIAL_COINS_ALLOCATED 100
#define INITIAL_STARS_ALLOCATED 2
#define INITIAL_HURDLE_SMASHERS_ALLOCATED 2
#define INITIAL_BRIDGES_ALLOCATED 2

/** Non-Standard Colors **/
#define HURDLE_GRADIENT_START_COLOR 0xFF666666
#define HURDLE_GRADIENT_END_COLOR   0xFF333333
#define BUTTON_HIGHLIGHT_COLOR  0x99FFCC00

/** Other Constants **/
#define NUM_HELP_SCREENS    8
#define FACEBOOK_APP_URL    "fb://profile/1410732689221094"
#define FACEBOOK_PAGE_URL   "http://facebook.com/magicfloodgame"
#define ITUNES_APP_URL  "itms://itunes.apple.com/us/app/apple-store/id967517904?mt=8f"
#define FEEDBACK_EMAIL  "ezeeideas@gmail.com"

/** Number of times to show the lifeline placement dialogs **/
#define MAX_STAR_PLACEMENT_DIALOG_COUNT 2
#define MAX_HURDLE_SMASHER_PLACEMENT_DIALOG_COUNT 2
#define MAX_BRIDGE_PLACEMENT_DIALOG_COUNT 2

#endif
