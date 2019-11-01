using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Keypad : MonoBehaviour {
    private GameObject[] buttons;
	// Use this for initialization
	void Start () {
        buttons = GameObject.FindGameObjectsWithTag("KeypadButtons");
	}
	


	// Update is called once per frame
	void Update () {
		
	}
}
