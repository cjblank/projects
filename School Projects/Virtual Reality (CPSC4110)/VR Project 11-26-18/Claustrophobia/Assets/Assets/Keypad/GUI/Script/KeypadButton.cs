using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class KeypadButton : MonoBehaviour {
    private Vector3 initSize;
    private int buttonID;
    private string text;
    private string buttonName;
    private Text textBox;
    private Score score;
    private Text expression;
    private int qCount;
    public string answer;
    public string realAnswer;
    public Mathmatics math;
    public int count;
    public int finalScore;
    public bool finished;

	// Use this for initialization
	void Start () {
        initSize = gameObject.transform.localScale;
        buttonName = gameObject.name;
        math = new Mathmatics();
        score = new Score();
        qCount = 0;
        switch (buttonName)
        {
            case "BTN_0":
                buttonID = 0;
                break;
            case "BTN_1":
                buttonID = 1;
                break;
            case "BTN_2":
                buttonID = 2;
                break;
            case "BTN_3":
                buttonID = 3;
                break;
            case "BTN_4":
                buttonID = 4;
                break;
            case "BTN_5":
                buttonID = 5;
                break;
            case "BTN_6":
                buttonID = 6;
                break;
            case "BTN_7":
                buttonID = 7;
                break;
            case "BTN_8":
                buttonID = 8;
                break;
            case "BTN_9":
                buttonID = 9;
                break;
            case "BTN_D":
                buttonID = 10;
                break;
            case "BTN_A":
                buttonID = 11;
                break;

        }
        textBox = GameObject.FindGameObjectWithTag("KeypadText").GetComponent<UnityEngine.UI.Text>();
        textBox.text = "";
	}

	private void OnMouseEnter()
    {
        gameObject.transform.localScale = new Vector3(initSize.x + 0.5f, initSize.y + 0.5f, initSize.z);
	}
	private void OnMouseExit()
	{
        gameObject.transform.localScale = initSize;
	}
	private void OnMouseDown()
	{
        gameObject.transform.localScale = new Vector3(initSize.x, initSize.y, initSize.z);
        if (buttonID >= 0 && buttonID <= 9)
        {
            textBox.text = textBox.text + buttonID;
        }
        else if (buttonID == 10){
            textBox.text = "";
        }
        else if(buttonID == 11){
            math = GameObject.FindGameObjectWithTag("Equation").GetComponent<Mathmatics>();
            realAnswer = math.result.ToString();
            answer = textBox.text.ToString();

            if (answer == realAnswer)
                count++;
            textBox.text = "";
            math.display(false);
            qCount++;
        }
        if(qCount == 10)
        {
            math.aStopwatch.Stop();
            finished = true;
            score = GameObject.FindGameObjectWithTag("Score").GetComponent<Score>();
            string scrStr = "Your score is " + count + " out of 10.";
            score.score.text = scrStr;
            // expression = GameObject.FindWithTag("Equation").GetComponent<UnityEngine.UI.Text>();
            finalScore = count;
            math.display(finished);
        }

	}
	private void OnMouseUp()
	{
        gameObject.transform.localScale = new Vector3(initSize.x + 0.5f, initSize.y + 0.5f, initSize.z);
    }

  
	// Update is called once per frame
	void Update () {
		
	}
}
