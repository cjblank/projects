using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Diagnostics;

public class Mathmatics : MonoBehaviour {
    private Text equation;
    private int count;
    public KeypadButton answer;
    public int result;
    bool completed;
    public Stopwatch aStopwatch;

	// Use this for initialization
	void Start () {

        aStopwatch = new Stopwatch();
        aStopwatch.Start();
        display(false);
	}
	
	// Update is called once per frame
	void Update () {
        // if "submit" key is pressed, then: 
        //   compare the correct answer with the user input and keep  score
        //   increment number of questions by 1
        //   if question count is <= 10 then display new problem
        //   

        // string x = answer.answerStr();
    }

    public void display(bool finished)
    {
        if (finished)
            equation.text = " ";
        else
        {
            equation = GameObject.FindWithTag("Equation").GetComponent<UnityEngine.UI.Text>();
            string test = toString(generateExpression());
            equation.text = test;
        }
    }

    int[] generateExpression()
    {
        
        int fac1, fac2, fac3, op1, op2;
        int[] expressionInfo = new int[6];
        do
        {
            fac1 = Random.Range(1, 11);
            fac2 = Random.Range(1, 11);
            fac3 = Random.Range(1, 11);
            op1 = Random.Range(1, 3);
            op2 = Random.Range(1, 3);
            result = fac1;

            expressionInfo[0] = fac1;
            expressionInfo[1] = fac2;
            expressionInfo[2] = fac3;
            expressionInfo[3] = op1;
            expressionInfo[4] = op2;

            if (op1 == 1)
                result += fac2;
            else if (op1 == 2)
                result -= fac2;

            if (op2 == 1)
                result += fac3;
            else if (op2 == 2)
                result -= fac3;

            expressionInfo[5] = result;
        } while (result <= 0);

        return expressionInfo;
    }

    string toString(int[] expression)
    {
        string temp;
        string[] eqStr = new string[6];
        int [] equation = new int[6];
        equation = expression;
        for (int i = 0; i < equation.Length; i++)
        {
            temp = equation[i].ToString();
            eqStr[i] = temp;

            if (i == 3)
                if (eqStr[i] == "1")
                    eqStr[i] = "+";
                else if (eqStr[i] == "2")
                    eqStr[i] = "-";
            if (i == 4)
                if (eqStr[i] == "1")
                    eqStr[i] = "+";
                else if (eqStr[i] == "2")
                    eqStr[i] = "-";
        }
        return string.Concat(eqStr[0], ' ', eqStr[3], ' ', eqStr[1], ' ', eqStr[4], ' ', eqStr[2]);
    }
}
