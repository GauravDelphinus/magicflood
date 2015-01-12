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
#include <string.h>
#include <stdio.h>

/**
 String comparator used by the map for comparing the in-app product string keys.
 **/
struct char_cmp
{
    bool operator () (const char *a,const char *b) const
    {
        return strcmp(a,b) < 0;
    }
};

/**
 The locally cached In-App Products List.
 **/
static std::list<MFInAppProduct *> sInAppProductList;

/**
 Add the given In-App product to the local cache.
 **/
void addInAppProduct(const char *id, const char *name, const char *description, const char *price, const char *priceCode, bool isProvisioned)
{
    bool found = false;
    std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
    while (iter != sInAppProductList.end())
    {
        MFInAppProduct *iap = (MFInAppProduct *) *iter;
        if (strcmp(iap->getID().c_str(), id) == 0)
        {
            iap->updateData(name, description, price, priceCode, isProvisioned);
            found = true;
            break;
        }
        iter++;
    }
    
    if (!found)
    {
        MFInAppProduct *iap = new MFInAppProduct(id, name, description, price, priceCode, isProvisioned);
        sInAppProductList.push_back(iap);
    }
}

/**
 Update the Provisioning Status for the given In-App Product.
 **/
void updateInAppProduct(const char *id, bool isProvisioned)
{
    std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
    while (iter != sInAppProductList.end())
    {
        MFInAppProduct *iap = (MFInAppProduct *) *iter;
        if (strcmp(iap->getID().c_str(), id) == 0)
        {
            iap->setProvisioned(isProvisioned);
            break;
        }
        iter++;
    }
}

/**
 Clear the list of cached In-App Products.  This is usually done
 if fetching the in-app products from the Google/Apple servers failed
 mid-way due to some reason, and we want to clear and start afresh.
 **/
void clearInAppProducts()
{
    std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
    while (iter != sInAppProductList.end())
    {
        MFInAppProduct *iap = (MFInAppProduct *) *iter;
        if (iap != NULL)
        {
            delete iap;
        }
        iter++;
    }
    
    sInAppProductList.clear();
}

/**
 Return an array of 4 char pointers, that contain these strings:
 0 -> In-App Product Name/Title
 1 -> In-App Product Description
 2 -> In-App Product Price
 3 -> In-App Product Currency Code
 
 NOTE: The caller must free the array, as well as the individual char arrays.
 **/
char **getInAppProductDetails(const char *pid)
{
    logPrint("magicflood", "getInAppProductDetails, pid = [%s]", pid);
    std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
    while (iter != sInAppProductList.end())
    {
        MFInAppProduct *iap = (MFInAppProduct *) *iter;
        if (strcmp(iap->getID().c_str(), pid) == 0)
        {
            logPrint("magicflood", "inside the if check");
            char **retArray = (char **) malloc (4 * sizeof(char *));
            
            retArray[0] = (char *) malloc (iap->getName().length() * sizeof(char) + 1);
            strcpy(retArray[0], iap->getName().c_str());
            logPrint("magicflood", "0: %s", retArray[0]);
            
            retArray[1] = (char *) malloc (iap->getDescription().length() * sizeof(char) + 1);
            strcpy(retArray[1], iap->getDescription().c_str());
            logPrint("magicflood", "1: %s", retArray[1]);
            
            retArray[2] = (char *) malloc (iap->getPrice().length() * sizeof(char) + 1);
            strcpy(retArray[2], iap->getPrice().c_str());
            logPrint("magicflood", "2: %s", retArray[2]);
            
            retArray[3] = (char *) malloc (iap->getPriceCode().length() * sizeof(char) + 1);
            strcpy(retArray[3], iap->getPriceCode().c_str());
            logPrint("magicflood", "3: %s", retArray[3]);
            
            logPrint("magicflood", "allocated the char pointer array, returning %p", retArray);
            
            return retArray;
        }
        iter++;
    }
    
    return NULL;
}

/**
 Return whether the given in-app product has already been
 provisioned.
 **/
bool getInAppProductProvisioned(const char *pid)
{
    logPrint("magicflood", "getInAppProductProvisioned, pid = [%s]", pid);
    std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
    while (iter != sInAppProductList.end())
    {
        MFInAppProduct *iap = (MFInAppProduct *) *iter;
        if (strcmp(iap->getID().c_str(), pid) == 0)
        {
            return iap->isProvisioned();
        }
        iter++;
    }
    
    return false;
}

int getNumInAppProducts()
{
    return sInAppProductList.size();
}

/**
 Return the list of all In-App Products.
 NOTE: The caller must free the pointer memory that is returned.
 **/
char **getAllInAppProducts()
{
    char **inAppProductsArray = NULL;
    if (sInAppProductList.size() > 0)
    {
        inAppProductsArray = (char **) malloc (sInAppProductList.size() * sizeof(char *));
        std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
        int i = 0;
        while (iter != sInAppProductList.end())
        {
            MFInAppProduct *iap = (MFInAppProduct *) (*iter);
            inAppProductsArray[i] = (char *) malloc (strlen(iap->getID().c_str()) * sizeof(char));
            strcpy(inAppProductsArray[i++], iap->getID().c_str());
            iter++;
        }
    }
    
    return inAppProductsArray;
}

/**
 Return the number of provisioned in-app products.
 **/
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
char **getProvisionedInAppProducts()
{
    char **inAppProductsArray = NULL;
    if (sInAppProductList.size() > 0)
    {
        inAppProductsArray = (char **) malloc (sInAppProductList.size() * sizeof(char *));
        std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
        int i = 0;
        while (iter != sInAppProductList.end())
        {
            MFInAppProduct *iap = (MFInAppProduct *) (*iter);
            if (iap->isProvisioned())
            {
                inAppProductsArray[i] = (char *) malloc (strlen(iap->getID().c_str()) * sizeof(char));
                strcpy(inAppProductsArray[i++], iap->getID().c_str());
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
char **getNonProvisionedInAppProducts()
{
    char **inAppProductsArray = NULL;
    if (sInAppProductList.size() > 0)
    {
        inAppProductsArray = (char **) malloc (sInAppProductList.size() * sizeof(char *));
        std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
        int i = 0;
        while (iter != sInAppProductList.end())
        {
            MFInAppProduct *iap = (MFInAppProduct *) (*iter);
            if (!iap->isProvisioned())
            {
                inAppProductsArray[i] = (char *) malloc (strlen(iap->getID().c_str()) * sizeof(char));
                strcpy(inAppProductsArray[i++], iap->getID().c_str());
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
bool getIsInAppProductProvisioned(const char * productID)
{
    std::list<MFInAppProduct *>::iterator iter = sInAppProductList.begin();
    while (iter != sInAppProductList.end())
    {
        MFInAppProduct *iap = (MFInAppProduct *) (*iter);
        if (strcmp(iap->getID().c_str(), productID) == 0)
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
        iter++;
    }
    
    return false;
}