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

/**
 Various IAP Test Product IDs.
 **/
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
