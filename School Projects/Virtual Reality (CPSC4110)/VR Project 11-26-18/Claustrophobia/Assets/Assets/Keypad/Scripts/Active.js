#pragma strict

var button : GUITexture; //this button.

var Hover : Color; //Hover button color.
var Original : Color; //Original button color.

var hover : GameObject; // Hover Sound
var press : GameObject; // Press Sound

var code : GUIText;

var scene : String;

function OnMouseEnter () 
{
	button.GetComponent.<GUITexture>().color = Hover;
	hover.GetComponent.<AudioSource>().Play();
}

function OnMouseExit () 
{
	button.GetComponent.<GUITexture>().color = Original;
	hover.GetComponent.<AudioSource>().Stop();
}

function OnMouseDown () 
{
	press.GetComponent.<AudioSource>().Play();
	if(code.text == "12556") //Checking if code is correct. //You can type any code you wish.
	{
		Debug.Log("Correct");
		Application.LoadLevel(scene);
	}
	else //If the code is incorrect.
	{
		code.text = "";
		KeypadSystem_.maxNumbers = 0; 
		Debug.Log("Incorrect");
	}
}