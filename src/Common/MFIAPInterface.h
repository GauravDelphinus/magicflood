//
//  MFIAPInterface.h
//  Magic Flood
//
//  Created by Anukrity Jain on 29/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#ifndef __Magic_Flood__MFIAPInterface__
#define __Magic_Flood__MFIAPInterface__

#include "MFInAppProduct.h"
#include <stdio.h>
#include <vector>

void initializeInAppInterface();
void clearInAppProducts();
void addInAppProduct(const char *pid, const char *name, const char *description, const char *price, const char *priceCode, bool isProvisioned);
void updateInAppProduct(const char *pid, bool isProvisioned);
char **getInAppProductDetails(const char *pid);
bool getInAppProductProvisioned(const char *pid);
int getNumInAppProducts();
char **getAllInAppProducts();
int getNumProvisionedInAppProducts();
char **getProvisionedInAppProducts();
char **getNonProvisionedInAppProducts();
int getNumObstaclesInInAppProduct(const char* productID);
int *getObstaclesInInAppProduct(const char* productID);
bool getIsInAppProductProvisioned(const char * productID);

/**
 Various IAP IDs.
 **/
#define IAP_ALACARTE_1  1 //4th hurdle (I)
#define IAP_ALACARTE_2  2 //5th hurdle (L)
#define IAP_ALACARTE_3  3 //6th hurdle (M)
#define IAP_ALACARTE_4  4 //7th hurdle (P)
#define IAP_ALACARTE_5  5 //8th hurdle (S)
#define IAP_ALACARTE_6  6 //9th hurdle (Sathiya)
#define IAP_COMBO_1 7 //next 5 hurdles (10th - 14th)
#define IAP_COMBO_2 8 //next 10 hurdles (15th -24th)
#define IAP_COMBO_3 9 //next 25 hurdles (25th - 49th)
#define IAP_COMBO_4 10 //next 50 hurdles (50th - 99th)
//#define IAP_REMOVE_ADS  11 //remove ads

/**
 Various IAP Product IDs.
 **/
/*
#define IAP_ALACARTE_HURDLE_1   "iap_alacarte_hurdle_1"
#define IAP_ALACARTE_HURDLE_2   "iap_alacarte_hurdle_2"
#define IAP_ALACARTE_HURDLE_3   "iap_alacarte_hurdle_3"
#define IAP_ALACARTE_HURDLE_4   "iap_alacarte_hurdle_4"
#define IAP_ALACARTE_HURDLE_5   "iap_alacarte_hurdle_5"
#define IAP_ALACARTE_HURDLE_6   "iap_alacarte_hurdle_6"
#define IAP_COMBO_HURDLES_1 "iap_combo_hurdles_1"
#define IAP_COMBO_HURDLES_2 "iap_combo_hurdles_2"
#define IAP_COMBO_HURDLES_3 "iap_combo_hurdles_3"
#define IAP_COMBO_HURDLES_4 "iap_combo_hurdles_4"
#define IAP_REMOVE_ADS  "iap_remove_ads"
 */

#define IAP_ALACARTE_HURDLE_1   "test_iap_alacarte_hurdle_1"
#define IAP_ALACARTE_HURDLE_2   "test_iap_alacarte_hurdle_2"
#define IAP_ALACARTE_HURDLE_3   "test_iap_alacarte_hurdle_3"
#define IAP_ALACARTE_HURDLE_4   "test_iap_alacarte_hurdle_4"
#define IAP_ALACARTE_HURDLE_5   "test_iap_alacarte_hurdle_5"
#define IAP_ALACARTE_HURDLE_6   "test_iap_alacarte_hurdle_6"
#define IAP_COMBO_HURDLES_1 "test_iap_combo_hurdles_1"
#define IAP_COMBO_HURDLES_2 "test_iap_combo_hurdles_2"
#define IAP_COMBO_HURDLES_3 "test_iap_combo_hurdles_3"
#define IAP_COMBO_HURDLES_4 "test_iap_combo_hurdles_4"
#define IAP_REMOVE_ADS  "test_iap_remove_ads"

#endif /* defined(__Magic_Flood__MFIAPInterface__) */
