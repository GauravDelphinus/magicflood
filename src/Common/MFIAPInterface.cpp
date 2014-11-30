//
//  MFIAPInterface.cpp
//  Magic Flood
//
//  Created by Anukrity Jain on 29/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#include "MFObstacle.h"
#include "MFIAPInterface.h"
#include "MFInAppProduct.h"
#include "MFNativeLog.h"
#include <iostream>
#include <list>
#include <stdlib.h>
#include <vector>
#include <map>

static std::list<MFInAppProduct *> sInAppProductList;
static std::map<int, std::vector<int> * > sInAppProductToObstacleMap;

void initializeInAppInterface()
{
    std::vector<int> *obstacles = NULL;
    
    //A-la-carte items
    obstacles = new std::vector<int>();
    obstacles->push_back(4);
    sInAppProductToObstacleMap[IAP_ALACARTE_1] = obstacles;
    logPrint("magicflood", "initializeInAppInterface, added map for %d", IAP_ALACARTE_1);
    
    obstacles = new std::vector<int>();
    obstacles->push_back(5);
    sInAppProductToObstacleMap[IAP_ALACARTE_2] = obstacles;
    
    obstacles = new std::vector<int>();
    obstacles->push_back(6);
    sInAppProductToObstacleMap[IAP_ALACARTE_3] = obstacles;
    
    obstacles = new std::vector<int>();
    obstacles->push_back(7);
    sInAppProductToObstacleMap[IAP_ALACARTE_4] = obstacles;

    obstacles = new std::vector<int>();
    obstacles->push_back(8);
    sInAppProductToObstacleMap[IAP_ALACARTE_5] = obstacles;
    
    obstacles = new std::vector<int>();
    obstacles->push_back(9);
    sInAppProductToObstacleMap[IAP_ALACARTE_6] = obstacles;
    
    //combo items
    
    //combo of 5 hurdles
    obstacles = new std::vector<int>();
    for (int i = 10; i < 15; i++)
    {
        obstacles->push_back(i);
    }
    sInAppProductToObstacleMap[IAP_COMBO_1] = obstacles;
    
    //combo of 10 hurdles
    obstacles = new std::vector<int>();
    for (int i = 15; i < 25; i++)
    {
        obstacles->push_back(i);
    }
    sInAppProductToObstacleMap[IAP_COMBO_2] = obstacles;
    
    //combo of 25 hurdles
    obstacles = new std::vector<int>();
    for (int i = 25; i < 50; i++)
    {
        obstacles->push_back(i);
    }
    sInAppProductToObstacleMap[IAP_COMBO_3] = obstacles;
    
    //combo of 50 hurdles
    obstacles = new std::vector<int>();
    for (int i = 50; i < 100; i++)
    {
        obstacles->push_back(i);
    }
    sInAppProductToObstacleMap[IAP_COMBO_4] = obstacles;
}

void addInAppProduct(int id, const char *name, const char *description, bool isProvisioned)
{
    MFInAppProduct *iap = new MFInAppProduct(id, name, description, isProvisioned);
    sInAppProductList.push_back(iap);
}

int getNumObstaclesInInAppProduct(int productID)
{
    logPrint("magicflood", "getNumObstaclesInInAppProduct for productID = %d", productID);
    std::vector<int> *obstaclesVector = sInAppProductToObstacleMap[productID];
    logPrint("magicflood", "obtaclesVector = %p", obstaclesVector);
    return obstaclesVector->size();
}

/**
 Return the list of obstacles in this In-App Product.
 NOTE: The caller must free the returned pointer memory.
 **/
int *getObstaclesInInAppProduct(int productID)
{
    int *obstacles = NULL;
    std::vector<int> *obstaclesVector = sInAppProductToObstacleMap[productID];
    if (obstaclesVector != NULL)
    {
        obstacles = (int *) malloc (obstaclesVector->size() * sizeof(int));
        for (int i = 0; i < obstaclesVector->size(); i++)
        {
            obstacles[i] = (*obstaclesVector)[i];
        }
    }
    
    return obstacles;
}

int getNumInAppProducts()
{
    return sInAppProductList.size();
}

/**
 Return the list of all In-App Products.
 NOTE: The caller must free the pointer memory that is returned.
 **/
int *getAllInAppProducts()
{
    int *inAppProductsArray = NULL;
    if (sInAppProductList.size() > 0)
    {
        inAppProductsArray = (int *) malloc (sInAppProductList.size() * sizeof(int));
        std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
        int i = 0;
        while (iter != sInAppProductList.end())
        {
            MFInAppProduct *iap = (MFInAppProduct *) (*iter);
            inAppProductsArray[i++] = iap->getID();
            iter++;
        }
    }
    
    return inAppProductsArray;
}

int getNumProvisionedInAppProducts()
{
    int size = 0;
    if (sInAppProductList.size() > 0)
    {
        std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
        while (iter != sInAppProductList.end())
        {
            MFInAppProduct *iap = (MFInAppProduct *) (*iter);
            if (iap->isProvisioned())
            {
                size++;
            }
            iter++;
        }
    }
    
    return size;
}

/**
 Return the list of all Provisioned (bought) In-App Products.
 NOTE: The caller must free the pointer memory that is returned.
 **/
int *getProvisionedInAppProducts()
{
    int *inAppProductsArray = NULL;
    if (sInAppProductList.size() > 0)
    {
        inAppProductsArray = (int *) malloc (sInAppProductList.size() * sizeof(int));
        std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
        int i = 0;
        while (iter != sInAppProductList.end())
        {
            MFInAppProduct *iap = (MFInAppProduct *) (*iter);
            if (iap->isProvisioned())
            {
                inAppProductsArray[i++] = iap->getID();
            }
            iter++;
        }
    }
    
    return inAppProductsArray;
}

/**
 Return the list of all Non-Provisioned (not-bought) In-App Products.
 NOTE: The caller must free the pointer memory that is returned.
 **/
int *getNonProvisionedInAppProducts()
{
    int *inAppProductsArray = NULL;
    if (sInAppProductList.size() > 0)
    {
        inAppProductsArray = (int *) malloc (sInAppProductList.size() * sizeof(int));
        std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
        int i = 0;
        while (iter != sInAppProductList.end())
        {
            MFInAppProduct *iap = (MFInAppProduct *) (*iter);
            if (!iap->isProvisioned())
            {
                inAppProductsArray[i++] = iap->getID();
            }
            iter++;
        }
    }
    
    return inAppProductsArray;
}

/**
 Check if the given In-App Product has already been provisioned (bought)
 or not.
 **/
bool getIsInAppProductProvisioned(int productID)
{
    std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
    while (iter != sInAppProductList.end())
    {
        MFInAppProduct *iap = (MFInAppProduct *) (*iter);
        if (iap->getID() == productID)
        {
            if (iap->isProvisioned())
            {
                return true;
            }
            else
            {
                break;
            }
        }
    }
    
    return false;
}