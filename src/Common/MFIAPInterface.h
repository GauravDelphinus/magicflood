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
#define IAP_REMOVE_ADS  "test_iap_remove_ads2"
#define IAP_COINS_FIRST "test_iap_add_coins_first"
#define IAP_COINS_SECOND "test_iap_add_coins_second"
#define IAP_COINS_THIRD "test_iap_add_coins_third"
#define IAP_COINS_FOURTH "test_iap_add_coins_fourth"

#endif /* defined(__Magic_Flood__MFIAPInterface__) */
