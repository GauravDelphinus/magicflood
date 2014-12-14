package com.ezeeideas.magicflood;

import android.app.Dialog;
import android.content.Context;
import android.support.v4.app.DialogFragment;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.content.DialogInterface;
import android.content.DialogInterface.OnDismissListener;
import android.graphics.drawable.ColorDrawable;
import android.view.Window;

public abstract class GameDialog extends Dialog implements OnDismissListener, OnTouchListener
{
	public GameDialog(Context context)
	{
		super(context);
		mContext = context;
		
		mListener = (GameDialogListener) mContext;
		
		//don't show a title
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setBackgroundDrawable(new ColorDrawable(android.graphics.Color.TRANSPARENT));
	}

	/**
	 * Called AFTER the specific game dialog has completed
	 * setup of its views.
	 */
	protected void postSetupViews()
	{		
		/**
		 * Implemented by GameDialogType* class that implements a specific type of dialog.
		 * This will call the setupView* methods to set up the variosu required views
		 * for that given type.
		 */
		setupRequiredViews();
		
		/**
		 * Set up the listeners for all active views in the dialog
		 */
		setupListeners();
	}
	/**
	 * Set up the required views for this dialog type,
	 * such as root view, positive view 1, etc.
	 */
	protected abstract void setupRequiredViews();
	
	/**
	 * Called when the user selected one of the views
	 * on the dialog, such as mRootView, mPositiveAction1View,
	 * mPositiveAction2View, mNegativeAction1View.
	 * @param v The view that was tapped
	 */
	protected abstract void handleTouch(View v);
	
	/**
	 * Called when the dialog was dismissed by the user
	 * by using the hardware back button.  Not called
	 * if the dismissal was programmatically done after
	 * a tap on some other button or view.
	 */
	protected abstract void handleDismiss();
	
	/**
	 * Set up listeners on all active views in the dialog.
	 */
	protected void setupListeners()
	{
		//Listen to dismiss events
		this.setOnDismissListener(this);
			
		if (mRootView != null)
		{
			mRootView.setOnTouchListener(this);		
		}
		
		if (mPositiveAction1View != null)
		{
			mPositiveAction1View.setOnTouchListener(this);
		}
		
		if (mPositiveAction2View != null)
		{
			mPositiveAction2View.setOnTouchListener(this);
		}
		
		if (mPositiveAction3View != null)
		{
			mPositiveAction3View.setOnTouchListener(this);
		}
		
		if (mNegativeAction1View != null)
		{
			mNegativeAction1View.setOnTouchListener(this);
		}
	}
	
	public boolean onTouch(View v, MotionEvent event) 
	{
		if (!mHandled)
		{
			mHandled = true;
			
			handleTouch(v);
		}
		
		return false;
	}
	
	public void onDismiss(DialogInterface dialog) 
	{
		if (!mHandled)
		{
			handleDismiss();
		}
		
		this.dismiss();
	}

	/**
	 * The listener (typically the calling Activity) that needs to listen to
	 * events from the dialog, including button clicks, touches and dialog dismissal.
	 */
	public interface GameDialogListener
	{
		public void onDialogOptionSelected(Dialog dialog, int option); //One of GAME_DIALOG_ACTION_*
	}
	
	protected GameDialogListener mListener;
	
	//Resultant actions after user acts on the dialog to pass on to the calling activity
	protected static final int GAME_DIALOG_ACTION_POSITIVE_1 = 1;
	protected static final int GAME_DIALOG_ACTION_POSITIVE_2 = 2;
	protected static final int GAME_DIALOG_ACTION_POSITIVE_3 = 3;
	protected static final int GAME_DIALOG_ACTION_NEGATIVE_1 = 4;
	
	//The Views that all dialogs must implement
	protected View mRootView = null; //The root view (usually a layout) that listens to the "tap anywhere else" area
	protected View mPositiveAction1View = null; //View that corresponds to Positive Action 1
	protected View mPositiveAction2View = null; //View that corresponds to Positive Action 2
	protected View mPositiveAction3View = null; //View that corresponds to Positive Action 3
	protected View mNegativeAction1View = null; //View the corresponds to Negative Action 1
	
	private Context mContext; //the calling activity context
	private boolean mHandled; //whether we've already handled some user input (to avoid double-dismiss issue)
	
}