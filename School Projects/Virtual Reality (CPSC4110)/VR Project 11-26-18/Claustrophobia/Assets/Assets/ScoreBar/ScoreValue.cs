using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

[Serializable]
public class ScoreValue
{
    [SerializeField]
    private ScoreBarScript bar;
    [SerializeField]
    private float maxVal;
    [SerializeField]
    private float curVal;
    [SerializeField]
    private float highVal;

    public float CurVal
    {
        get
        {
            return curVal;
        }

        set
        {
            curVal = value;
            bar.Value = curVal;
        }
    }

    public float MaxVal
    {
        get
        {
            return maxVal;
        }

        set
        {
            maxVal = value;
            bar.MaxValue = maxVal;
        }
    }

    public float HighVal
    {
        get
        {
            return highVal;
        }

        set
        {
            highVal = value;
            bar.HighValue = highVal;
        }
    }

    public void initialize()
    {
        this.MaxVal = maxVal;
        this.CurVal = curVal;
        this.HighVal = highVal;
    }
}
