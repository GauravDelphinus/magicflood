package com.ezeeideas.magicflood;

import android.app.Activity;
import android.os.Bundle;

public class MFGameActivity extends Activity {
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
    }

	private long gridHandle;
	private native long createNewGrid(int level);
	private native void deleteGrid(long handle);
	private native int getGridSize(long handle);
	private native int[] getStartPos(long handle);
	private native int getMaxMoves(long handle);
	private native int getCurrMove(long handle);
	private native int playMove(long handle, int color);
	private native int[] getGridData(long handle);
}