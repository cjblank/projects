using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreBarScript : MonoBehaviour {

    [SerializeField]
    private float fill_amount;
    [SerializeField]
    private float high_score;
    [SerializeField]
    private float current_score;

    [SerializeField]
    private Image content;

    public float MaxValue { get; set; }

    public float HighValue { get; set; }

    public float Value
    {
        set
        {
            fill_amount = Map(value, 0, MaxValue, 0, 1);
        }
    }

	// Use this for initialization
	void Start () {
        //high_score = 0f;
        //current_score = 0;

        //content.fillAmount = fill_amount;
        // content.fillAmount = current_score;
        // content = GameObject.Find("Fill").GetComponent<Image>();
	}
	
	// Update is called once per frame
	void Update () {

        doSomething();
	}

    void doSomething()
    {
        if(fill_amount != content.fillAmount)
            content.fillAmount = fill_amount;
    }

    float Map(float value, float inMin, float inMax, float outMin, float outMax)
    {
        return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    }
}
