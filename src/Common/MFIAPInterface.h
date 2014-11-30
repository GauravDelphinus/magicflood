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
void addInAppProduct(int id, const char *name, const char *description, bool isProvisioned);
int getNumInAppProducts();
int *getAllInAppProducts();
int getNumProvisionedInAppProducts();
int *getProvisionedInAppProducts();
int *getNonProvisionedInAppProducts();
int getNumObstaclesInInAppProduct(int productID);
int *getObstaclesInInAppProduct(int productID);
bool getIsInAppProductProvisioned(int productID);

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
#define IAP_REMOVE_ADS  11 //remove ads

#endif /* defined(__Magic_Flood__MFIAPInterface__) */
