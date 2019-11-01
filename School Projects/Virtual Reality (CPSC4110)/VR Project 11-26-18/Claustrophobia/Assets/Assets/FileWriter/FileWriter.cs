using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System;
using UnityEngine.SceneManagement;

public class FileWriter : MonoBehaviour {
    public KeypadButton keypadObjScript;
    public Mathmatics mathScript;
    public ScoreBarScript anxietyScript;

	// Use this for initialization
	void Start () {
        GameObject keypadGO = GameObject.Find("BTN_A");
        GameObject mathTextGO = GameObject.FindWithTag("Equation");
        GameObject ScoreBarGO = GameObject.FindWithTag("ScoreBar");

        if ((keypadGO != null) && (mathTextGO != null) && (ScoreBarGO != null))
        {
            keypadObjScript = keypadGO.GetComponent<KeypadButton>();
            mathScript = mathTextGO.GetComponent<Mathmatics>();
            anxietyScript = ScoreBarGO.GetComponent<ScoreBarScript>();
        }
    }
	
	//// Update is called once per frame
	//void Update () {
    //
    //    if (GameObject.Find("FileWriter"))
    //        writeFile();
	//	
	//}

    void OnDestroy()
    {
        String filenamebase = "Test";
        String filename;
        int i = 1;

        filename = filenamebase + i + ".txt";
        while (System.IO.File.Exists(filename))
        {
            i++;
            filename = filenamebase + i + ".txt";
        }

        StreamWriter File = new StreamWriter(filename);
        File.Write("Final Score: " + keypadObjScript.finalScore);
        File.Write(Environment.NewLine);
        File.Write("Highest Anxiety Level Reached: " + (anxietyScript.HighValue * 5));
        File.Write(Environment.NewLine);
        File.Write("Time Elapsed: " + mathScript.aStopwatch.Elapsed.TotalSeconds);
        File.Write(Environment.NewLine);
        File.Close();

    }
}
