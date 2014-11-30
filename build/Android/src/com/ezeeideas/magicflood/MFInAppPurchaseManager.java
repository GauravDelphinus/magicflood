package com.ezeeideas.magicflood;

public class MFInAppPurchaseManager
{
	public MFInAppPurchaseManager()
	{
		
	}
	
	public static void initialize()
	{
		if (sIAPManager == null)
		{
			sIAPManager = new MFInAppPurchaseManager();
		}
		
		sIAPManager.initializeInAppInterface();
		
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_1, "First A-la-carte Item", "My very first IAP", true);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_2, "Second A-la-carte item", "My very second IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_3, "Third A-la-carte item", "My very third IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_4, "Fourth A-la-carte item", "My very fourth IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_5, "Fifth A-la-carte item", "My very fifth IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_ALACARTE_6, "Sixth A-la-carte item", "My very sixth IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_COMBO_1, "Combo: 5 Hurdles!", "My very seventh IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_COMBO_2, "Combo: 10 Hurdles!", "My very eighth IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_COMBO_3, "Combo: 25 Hurdles!", "My very ninth IAP", false);
		sIAPManager.addInAppProduct(MFGameConstants.IAP_COMBO_4, "Combo: 50 Hurdles!", "My very tenth IAP", false);
	}
	
	private static MFInAppPurchaseManager sIAPManager = null;
	private native void initializeInAppInterface();
	private native void addInAppProduct(int id, String name, String description, boolean isProvisioned); 
};