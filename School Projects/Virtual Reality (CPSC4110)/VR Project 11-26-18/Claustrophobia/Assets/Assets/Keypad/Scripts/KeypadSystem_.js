#pragma strict

static var maxNumbers : int = 0; //Maximum count of number you can type

var keypad : GameObject;
var code : GUIText;

private var showing : boolean = false; //Checking if keypad is showing.

function Update () 
{
	if(Input.GetKeyDown(KeyCode.K) && showing == false) //If Not
	{
		showing = true;
		if(keypad != null) //Checking if keypad exists.
		{
			keypad.active = true;
		}
	}
	else if(Input.GetKeyDown(KeyCode.Escape) && showing == true) //If Yes
	{
		showing = false;
		if(keypad != null && code != null) //Checking if keypad exists.
		{
			code.text = "";
			KeypadSystem_.maxNumbers = 0;
			keypad.active = false;
		}
	}
}