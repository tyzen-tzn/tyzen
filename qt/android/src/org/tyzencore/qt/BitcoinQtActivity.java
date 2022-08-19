package org.tyzencore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class TyzenQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File tyzenDir = new File(getFilesDir().getAbsolutePath() + "/.tyzen");
        if (!tyzenDir.exists()) {
            tyzenDir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}
