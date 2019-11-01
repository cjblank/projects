using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour {
    public Text score;

	// Use this for initialization
	void Start () {
        score = GameObject.FindWithTag("Score").GetComponent<UnityEngine.UI.Text>();
        string test = " ";
        score.text = test;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
