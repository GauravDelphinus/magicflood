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
    std::string mID;
    std::string mPrice;
    std::string mPriceCode;
    bool mIsProvisioned;
    
public:
    MFInAppProduct(const char * id, const char *name, const char *description, const char *price, const char *priceCode, bool isProvisioned);
    std::string getName();
    std::string getDescription();
    std::string getID();
    std::string getPrice();
    std::string getPriceCode();
    bool isProvisioned();
    void setProvisioned(bool isProvisioned);
    void updateData(const char *name, const char *description, const char *price, const char *priceCode, bool isProvisioned);
};

#endif /* defined(__Magic_Flood__MFInAppProduct__) */
