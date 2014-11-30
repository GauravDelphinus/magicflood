//
//  MFInAppProduct.h
//  Magic Flood
//
//  Created by Anukrity Jain on 29/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#ifndef __Magic_Flood__MFInAppProduct__
#define __Magic_Flood__MFInAppProduct__

#include "string"

class MFInAppProduct
{
private:
    std::string mName;
    std::string mDescription;
    int mID;
    bool mIsProvisioned;
    
public:
    MFInAppProduct(int id, const char *name, const char *description, bool isProvisioned);
    std::string getName();
    std::string getDescription();
    int getID();
    bool isProvisioned();
};

#endif /* defined(__Magic_Flood__MFInAppProduct__) */
