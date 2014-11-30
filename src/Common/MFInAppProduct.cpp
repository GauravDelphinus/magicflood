//
//  MFInAppProduct.cpp
//  Magic Flood
//
//  Created by Anukrity Jain on 29/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#include "MFInAppProduct.h"

MFInAppProduct::MFInAppProduct(const char* id, const char *name, const char *description, const char *price, const char *priceCode, bool isProvisioned)
{
    mID = id;
    mName = name;
    mDescription = description;
    mPrice = price;
    mPriceCode = priceCode;
    mIsProvisioned = isProvisioned;
}

std::string MFInAppProduct::getID()
{
    return mID;
}

std::string MFInAppProduct::getName()
{
    return mName;
}

std::string MFInAppProduct::getDescription()
{
    return mDescription;
}

std::string MFInAppProduct::getPrice()
{
    return mPrice;
}

std::string MFInAppProduct::getPriceCode()
{
    return mPriceCode;
}

bool MFInAppProduct::isProvisioned()
{
    return mIsProvisioned;
}

void MFInAppProduct::setProvisioned(bool isProvisioned)
{
    mIsProvisioned = isProvisioned;
}