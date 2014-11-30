//
//  MFInAppProduct.cpp
//  Magic Flood
//
//  Created by Anukrity Jain on 29/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#include "MFInAppProduct.h"

MFInAppProduct::MFInAppProduct(int id, const char *name, const char *description, bool isProvisioned)
{
    mID = id;
    mName = name;
    mDescription = description;
    mIsProvisioned = isProvisioned;
}

int MFInAppProduct::getID()
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

bool MFInAppProduct::isProvisioned()
{
    return mIsProvisioned;
}