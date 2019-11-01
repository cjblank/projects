#pragma strict

var button : GUITexture; //this button.

var Hover : Color; //Hover button color.
var Original : Color; //Original button color.

var hover : GameObject; // Hover Sound
var press : GameObject; // Press Sound

var code : GUIText;

var addNumber : String;

function OnMouseEnter () 
{
	button.GetComponent.<GUITexture>().color = Hover;
	hover.GetComponent.<AudioSource>().Play();
}

function OnMouseExit () 
{
	button.GetComponent.<GUITexture>().color = Original;
	hover.GetComponent.<AudioSource>().Stop(); //Stop playing if mouse exits the button.
}

function OnMouseDown () 
{
	press.GetComponent.<AudioSource>().Play();
	if(KeypadSystem_.maxNumbers < 5) //Checking if typing count number is less than maximum.
	{
		code.text += addNumber; //Adding Number
		KeypadSystem_.maxNumbers ++; 
	}
}